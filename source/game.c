#include <grrlib.h>
#include <wiiuse/wpad.h>

#include "game.h"
#include "main.h"
#include "custom_mp3player.h"
#include "level.h"
#include "math.h"

#include "oggplayer.h"
#include "endStart_02_ogg.h"

bool fixed_dt = FALSE;
bool enable_info = FALSE;
float amplitude = 0.0f;
float dt = 0;
u64 start_frame = 0;

float death_timer = 0.0f;

char *current_song_pointer = NULL;

int game_loop() {
    u64 prevTicks = gettime();
    double accumulator = 0.0f;

    size_t size;
    current_song_pointer = load_song(songs[level_info.song_id].song_name, &size);

    if (current_song_pointer) {
        MP3Player_PlayBuffer(current_song_pointer, size, NULL);
    }

    while (1) {
        start_frame = gettime();
        update_input();
        float frameTime = ticks_to_secs_float(start_frame - prevTicks);
        dt = frameTime;

        if (frameTime > 1) frameTime = 1; // Avoid spiral of death
        if (fixed_dt) {
            frameTime = STEPS_DT;
            fixed_dt = FALSE;
        }
        prevTicks = start_frame;

        accumulator += frameTime;

        if (state.input.pressed1orX) state.noclip ^= 1;
        
        u64 t0 = gettime();
        while (accumulator >= STEPS_DT) {
            state.old_player = state.player;
            amplitude = (beat_pulse ? 0.8f : 0.1f);
            if (death_timer <= 0) handle_player();
            
            u64 t2 = gettime();
            handle_objects();
            u64 t3 = gettime();
            triggers_time = ticks_to_microsecs(t3 - t2) / 1000.f * 4;

            t2 = gettime();
            update_particles();
            t3 = gettime();
            particles_time = ticks_to_microsecs(t3 - t2) / 1000.f * 4;

            update_beat();
            frame_counter++;

            if (state.player.dead) break;

            accumulator -= STEPS_DT;
        }
        u64 t1 = gettime();
        physics_time = ticks_to_microsecs(t1 - t0) / 1000.f;
        
        if (level_info.completing) {
            PlayOgg(endStart_02_ogg, endStart_02_ogg_size, 0, OGG_ONE_TIME);
            handle_completion();
            MP3Player_Stop();
            if (current_song_pointer) free(current_song_pointer);
            gameRoutine = ROUTINE_MENU;
            break;
        }

        if (state.player.dead && death_timer <= 0.f) {
            death_timer = 1.f;
            handle_death();
            state.player.dead = FALSE;
        }

        if (death_timer > 0.f) {
            death_timer -= dt;

            if (death_timer <= 0.f) {
                init_variables();
                reload_level(); 
                if (current_song_pointer) {
                    MP3Player_PlayBuffer(current_song_pointer, size, NULL);
                }
                update_input();
                fixed_dt = TRUE;
            }
        }

        if (state.input.pressedHome) {
            unload_level();
            return TRUE;
        }

        if (state.input.pressedMinusOrR) {
            MP3Player_Stop();
            gameRoutine = ROUTINE_MENU;
            break;
        }
        
        if (state.input.pressedPlusOrL) {
            enable_info ^= 1;
        }

        draw_game();
    }

    unload_level();

    return FALSE;
}