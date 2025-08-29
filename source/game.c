#include <grrlib.h>
#include <wiiuse/wpad.h>

#include "game.h"
#include "main.h"
#include "custom_mp3player.h"
#include "level.h"
#include "math.h"

#include "oggplayer.h"
#include "endStart_02_ogg.h"
#include "trail.h"

#include "stdio.h"
#include <ogc/lwp.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include <unistd.h>

bool fixed_dt = FALSE;
bool enable_info = FALSE;
float amplitude = 0.0f;
float dt = 0;
u64 start_frame = 0;

float death_timer = 0.0f;

char *current_song_pointer = NULL;

static lwp_t input_thread;
static volatile bool input_thread_active;
static volatile bool complete_level_flag;
static volatile bool exit_level_flag;
static volatile bool exit_game_flag;

typedef struct InputBuffer {
    KeyInput inputs[INPUT_BUFFER_SIZE];
    volatile u32 write_index;
    volatile u32 read_index;
    mutex_t mutex;
} InputBuffer;

static InputBuffer input_buffer;

static volatile u32 frames_processed = 0;

// Initialize the input buffer in game_loop before creating thread:
void init_input_buffer() {
    LWP_MutexInit(&input_buffer.mutex, false);
    input_buffer.write_index = 0;
    input_buffer.read_index = 0;
    memset(input_buffer.inputs, 0, sizeof(KeyInput) * INPUT_BUFFER_SIZE);
}

void *input_loop(void *arg) {
    printf("Starting input thread\n");
    input_thread_active = TRUE;
    while (1) {
        u64 t0 = gettime();

        // Get next write position
        u32 write_pos = (input_buffer.write_index + 1) & INPUT_BUFFER_MASK;
        
        // Wait if buffer full
        while (write_pos == input_buffer.read_index) {
            usleep(100);
        }
        
        // Write input
        LWP_MutexLock(input_buffer.mutex);
        update_external_input(&input_buffer.inputs[input_buffer.write_index]);
        input_buffer.write_index = write_pos;
        LWP_MutexUnlock(input_buffer.mutex);

        KeyInput input = input_buffer.inputs[input_buffer.write_index];

        //if (input.pressedJump) printf("INPUT THREAD - Step n %d jump is %d\n", input_buffer.write_index, input.pressedJump);
        
        if (level_info.completing) {
            complete_level_flag = TRUE;
            break;
        }

        if (input.pressed1orX) state.noclip ^= 1;
        if (input.pressedDir & INPUT_LEFT) {
            state.hitbox_display++;
            if (state.hitbox_display > 2) state.hitbox_display = 0;
        }

        if (input.pressedHome) {
            exit_game_flag = TRUE;
            break;
        }

        if (input.pressedMinusOrR) {
            exit_level_flag = TRUE;
            break;
        }

        if (input.pressedPlusOrL) {
            enable_info ^= 1;
        }

        u64 t1 = gettime();

        float calc_time = (STEPS_DT * 1000000) - ticks_to_microsecs(t1 - t0);

        if (calc_time > 0) usleep(calc_time);
    }
    input_thread_active = FALSE;
    printf("Exiting input thread\n");
    return NULL;
}

int game_loop() {
    size_t size;
    if (level_info.custom_song_id >= 0) {
        current_song_pointer = load_user_song(level_info.custom_song_id, &size);
    } else {
        current_song_pointer = load_song(songs[level_info.song_id].song_name, &size);
    }

    if (current_song_pointer) {
        MP3Player_SetSeconds(level_info.song_offset);
        MP3Player_PlayBuffer(current_song_pointer, size, seek_filter);
    }

    init_input_buffer();
    LWP_CreateThread(&input_thread, input_loop, NULL, NULL, 0, 100);
    
    double accumulator = 0.0f;
    u64 prevTicks = gettime();
    while (1) {
        start_frame = gettime();
        float frameTime = ticks_to_secs_float(start_frame - prevTicks);
        dt = frameTime;

        if (frameTime > 1) frameTime = 1; // Avoid spiral of death
        if (fixed_dt) {
            frameTime = STEPS_DT;
            fixed_dt = FALSE;
        }
        prevTicks = start_frame;
        
        accumulator += frameTime;

        u64 t0 = gettime();
        while (accumulator >= STEPS_DT) {
            if (input_buffer.read_index != input_buffer.write_index) {
                LWP_MutexLock(input_buffer.mutex);
                state.input = input_buffer.inputs[input_buffer.read_index];
                input_buffer.read_index = (input_buffer.read_index + 1) & INPUT_BUFFER_MASK;
                LWP_MutexUnlock(input_buffer.mutex);
    
                state.old_player = state.player;
                if (level_info.custom_song_id >= 0) {
                    amplitude = CLAMP(MP3Player_GetAmplitude(), 0.1f, 1.f);
                } else {
                    amplitude = (beat_pulse ? 1.f : 0.1f);
                }

                state.current_player = 0;
                trail = trail_p1;
                wave_trail = wave_trail_p1;
                if (death_timer <= 0)  {
                    // Run first player
                    handle_player(&state.player);
                    
                    run_camera();
                    handle_mirror_transition();

                    trail_p1 = trail;
                    wave_trail_p1 = wave_trail;

                    if (state.dead) break;

                    if (state.dual) {
                        // Run second player
                        state.old_player = state.player2;
                        trail = trail_p2;
                        wave_trail = wave_trail_p2;
                        state.current_player = 1;
                        handle_player(&state.player2);
                        trail_p2 = trail;
                        wave_trail_p2 = wave_trail;
                    }
                }
                    
                u64 t2 = gettime();
                handle_objects();
                u64 t3 = gettime();
                triggers_time = ticks_to_microsecs(t3 - t2) / 1000.f * 4;

                t2 = gettime();
                update_particles();
                t3 = gettime();
                particles_time = ticks_to_microsecs(t3 - t2) / 1000.f * 4;

                update_beat();
                
                update_percentage();
                frame_counter++;

                frames_processed++;

                if (state.dead) break;

                accumulator -= STEPS_DT;
            } else {
                 // No input available, wait
                usleep(100);
                accumulator -= 100/1000000.f;

                if (!input_thread_active) break;
            }
        }
        u64 t1 = gettime();
        physics_time = ticks_to_microsecs(t1 - t0) / 1000.f;

        if (state.dead && death_timer <= 0.f) {
            death_timer = 1.f;
            handle_death();
            state.dead = FALSE;
        }

        if (death_timer > 0.f) {
            death_timer -= dt;

            if (death_timer <= 0.f) {
                init_variables();
                reload_level(); 
                if (current_song_pointer) {
                    MP3Player_Reset();
                    MP3Player_SetSeconds(level_info.song_offset);
                    MP3Player_PlayBuffer(current_song_pointer, size, seek_filter);
                    MP3Player_Volume(255);
                }
                update_input();
                fixed_dt = TRUE; 
            }
        }

        if (complete_level_flag) {
            PlayOgg(endStart_02_ogg, endStart_02_ogg_size, 0, OGG_ONE_TIME);
            handle_completion();
            MP3Player_Stop();
            complete_level_flag = FALSE;
            if (current_song_pointer) free(current_song_pointer);
            gameRoutine = ROUTINE_MENU;
            break;
        }

        if (exit_level_flag) {
            MP3Player_Stop();
            MP3Player_Volume(255);
            gameRoutine = ROUTINE_MENU;
            exit_level_flag = FALSE;
            if (current_song_pointer) free(current_song_pointer);
            break;
        }

        if (exit_game_flag) {
            unload_level();
            return TRUE;
        }

        draw_game();
    }

    unload_level();

    return FALSE;
}