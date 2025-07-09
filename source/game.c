#include <grrlib.h>
#include <wiiuse/wpad.h>

#include "game.h"
#include "main.h"
#include "custom_mp3player.h"
#include "level.h"
#include "math.h"

bool fixed_dt = FALSE;
bool enable_info = FALSE;
float amplitude = 0.0f;

int game_loop() {
    u64 prevTicks = gettime();
    double accumulator = 0.0f;

    load_level();

    MP3Player_PlayBuffer(levels[level_id].song_ptr, levels[level_id].song_size, NULL);

    while (1) {
        WPAD_ScanPads();
        u64 currentTicks = gettime();
        float frameTime = ticks_to_secs_float(currentTicks - prevTicks);
        if (frameTime > STEPS_DT * 16) frameTime = STEPS_DT * 16; // Avoid spiral of death
        if (fixed_dt) {
            frameTime = STEPS_DT;
            fixed_dt = FALSE;
        }
        prevTicks = currentTicks;

        accumulator += frameTime;
        
        while (accumulator >= STEPS_DT) {
            state.old_player = state.player;
            amplitude = MP3Player_GetAmplitude();
            handle_player();
            handle_objects();
            update_particles();
            frame_counter++;

            if (state.player.dead) break;

            accumulator -= STEPS_DT;
        }
                      
        if (state.player.dead) {
            draw_game();
            handle_death();
            MP3Player_PlayBuffer(levels[level_id].song_ptr, levels[level_id].song_size, NULL);
            WPAD_ScanPads();
            fixed_dt = TRUE;
        }

        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) {
            unload_level();
            return TRUE;
        }

        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_MINUS) {
            MP3Player_Stop();
            gameRoutine = ROUTINE_MENU;
            break;
        }
        
        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_PLUS) {
            enable_info ^= 1;
        }

        draw_game();
    }

    unload_level();

    return FALSE;
}