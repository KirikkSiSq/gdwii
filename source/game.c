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
#include <math.h>

int paused_loop();
int handle_wall_cutscene();

bool fixed_dt = FALSE;
bool enable_info = FALSE;
float amplitude = 0.0f;
float dt = 0;
u64 start_frame = 0;

float death_timer = 0.0f;
float completion_timer = 0.0f;
bool completion_shake = FALSE;

char *current_song_pointer = NULL;

static lwp_t input_thread;
static volatile bool input_thread_active;
static volatile bool complete_level_flag;
static volatile bool exit_level_flag;

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
    exit_level_flag = FALSE;
    while (1) {
        u64 t0 = gettime();

        // Get next write position
        u32 write_pos = (input_buffer.write_index + 1) & INPUT_BUFFER_MASK;
        
        // Wait if buffer full
        while (write_pos == input_buffer.read_index && !exit_level_flag) {
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

        if (input.pressedDir & INPUT_RIGHT) {
            enable_info ^= 1;
        }

        if (input.pressedPlusOrL) {
            state.paused ^= 1;
        }

        if (exit_level_flag) {
            break;
        }

        u64 t1 = gettime();

        float calc_time = (STEPS_DT * 1000000) - ticks_to_microsecs(t1 - t0);

        if (calc_time > 0) usleep(calc_time);
    }
    input_thread_active = FALSE;
    printf("Exiting input thread\n");
    return NULL;
}

int paused_loop() {
    LWP_SuspendThread(input_thread);
    MP3Player_Pause();
    while (1) {
        start_frame = gettime();
        update_input();
        if (state.input.pressedMinusOrR) {
            MP3Player_Stop();
            MP3Player_Volume(0);
            gameRoutine = ROUTINE_MENU;
            if (current_song_pointer) free(current_song_pointer);
            LWP_ResumeThread(input_thread);
            exit_level_flag = TRUE;
            state.paused = FALSE;
            return TRUE;
        }

        // Unpause
        if (state.input.pressedPlusOrL) {
            break;
        }

        draw_game();
    }
    MP3Player_Unpause();
    LWP_ResumeThread(input_thread);
    state.paused = FALSE;
    return FALSE;
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
            if (complete_level_flag || input_buffer.read_index != input_buffer.write_index) {
                if (!complete_level_flag) {
                    LWP_MutexLock(input_buffer.mutex);
                    state.input = input_buffer.inputs[input_buffer.read_index];
                    input_buffer.read_index = (input_buffer.read_index + 1) & INPUT_BUFFER_MASK;
                    LWP_MutexUnlock(input_buffer.mutex);
                }
    
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
            if (handle_wall_cutscene()) break;
        }   

        if (state.paused) {
            if (paused_loop()) break;
            fixed_dt = TRUE; 
        }

        draw_game();
    }
    
    LWP_JoinThread(input_thread, NULL);

    unload_level();

    return FALSE;
}

Ray end_rays[MAX_RAYS];

void erase_rays() {
    for (int i = 0; i < MAX_RAYS; i++) {
        end_rays[i].active = FALSE;
    }
}

void fade_rays() {
    for (int i = 0; i < MAX_RAYS; i++) {
        if (end_rays[i].active) {
            u32 color = end_rays[i].color;

            float alpha = CLAMP(A(color) - 240 * dt, 0, 255);
            end_rays[i].color = RGBA(R(color), G(color), B(color), alpha);
        }
    }
}

void create_ray(float x, float y, float angle, float length, float startWidth, float endWidth, float duration, u32 color) {
    for (int i = 0; i < MAX_RAYS; i++) {
        Ray *ray = &end_rays[i];
        if (!ray->active) {
            ray->x = x;
            ray->y = y;
            ray->angle = angle;

            ray->length = length;
            ray->startWidth = startWidth;
            ray->endWidth = endWidth;

            ray->elapsed = 0;
            ray->duration = duration;

            ray->color = color;

            ray->active = TRUE;
            break;
        }
    }
}

void draw_rays() {
    GX_SetVtxDesc(GX_VA_TEX0, GX_NONE);  // No texture
    GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    GRRLIB_SetBlend(GRRLIB_BLEND_ADD);

    for (int ray = 0; ray < MAX_RAYS; ray++) {
        
        if (!end_rays[ray].active) continue;

        float angle = end_rays[ray].angle;

        float x = end_rays[ray].x;
        float y = end_rays[ray].y;
        
        float startWidth = end_rays[ray].startWidth;
        float endWidth = end_rays[ray].endWidth;

        float length = end_rays[ray].length;

        float elapsed = end_rays[ray].elapsed;
        float duration = end_rays[ray].duration;
        
        u32 color = end_rays[ray].color;

        float t = elapsed / duration;

        if (t > 1.0f) t = 1.0f;
        if (t < 0) t = 0;
        
        float rad = DegToRad(angle);
        float cosA = cosf(rad);
        float sinA = sinf(rad);
        
        Vec2 vertices[4];

        // Set vertices
        vertices[0].x = x;
        vertices[0].y = y + startWidth / 2;

        vertices[1].x = x;
        vertices[1].y = y - startWidth / 2;

        vertices[2].x = x - length * t;
        vertices[2].y = y + (startWidth + (endWidth - startWidth) * t) / 2;

        vertices[3].x = x - length * t;
        vertices[3].y = y - (startWidth + (endWidth - startWidth) * t) / 2;

        GX_Begin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        
        // Rotate around x and y
        for (int i = 0; i < 4; i++) {
        
            float vertex_x = vertices[i].x - x;
            float vertex_y = vertices[i].y - y;
            float new_vertex_x = vertex_x * cosA - vertex_y * sinA;
            float new_vertex_y = vertex_x * sinA + vertex_y * cosA;

            vertices[i].x = new_vertex_x + x;
            vertices[i].y = new_vertex_y + y;
            
            float calc_x = ((vertices[i].x - state.camera_x) * SCALE) + 6 * state.mirror_mult - widthAdjust;  
            float calc_y = screenHeight - ((vertices[i].y - state.camera_y) * SCALE) + 6;
            
            GX_Position3f32(get_mirror_x(calc_x, state.mirror_factor), calc_y, 0.f);
            GX_Color1u32(color);
        }
        GX_End();

        end_rays[ray].elapsed += dt;
    }
    GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
    
    GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);
    GX_SetTevOp(GX_TEVSTAGE0, GX_MODULATE);
}

int rays_spawned = 0;
float first_angle = 0;
int circles_spawned = 0;
int handle_wall_cutscene() {
    if (completion_timer == 0) {
        completion_shake = TRUE;
        circles_spawned = 0;
        rays_spawned = 0;
        
        particle_templates[END_WALL_COLL_CIRCLE].end_scale = 400;
        particle_templates[END_WALL_COLL_CIRCLE].life = 0.5f;
        spawn_particle(END_WALL_COLL_CIRCLE, level_info.wall_x, level_info.wall_y, NULL);
        PlayOgg(endStart_02_ogg, endStart_02_ogg_size, 0, OGG_ONE_TIME);
    }

    if (completion_timer > 0.2) {
        if (completion_timer > 0.2 + (rays_spawned * 0.2)) {

            float angle;
            // First ray chooses the boundary, second mirrors it, the rest are random
            if (rays_spawned == 0) {
                angle = first_angle = random_float(35, 45);
            } else if (rays_spawned == 1) {
                angle = -first_angle;
            } else {
                angle = random_float(0, first_angle);

                // Odd rays are on the second half relative to even rays
                if ((rays_spawned & 1) != 0) {
                    angle = -angle;
                }
            }

            float width = random_float(10, 20);
            create_ray(level_info.wall_x, level_info.wall_y, angle, 1000, width, width * 2, 0.25f, RGBA(p1.r, p1.g, p1.b, random_int(63, 255)));
            rays_spawned++;
        }
    }

    if (completion_timer > 2) {
        // Big circle
        if (circles_spawned == 0) {
            particle_templates[END_WALL_COLL_CIRCLE].end_scale = 400;
            particle_templates[END_WALL_COLL_CIRCLE].life = 0.5f;
            spawn_particle(END_WALL_COLL_CIRCLE, level_info.wall_x, level_info.wall_y, NULL); // Comes from wall
            spawn_particle(END_WALL_COLL_CIRCLE, state.camera_x + WIDTH_ADJUST_AREA + SCREEN_WIDTH_AREA / 2, state.camera_y + SCREEN_HEIGHT_AREA / 2, NULL); // Comes from complete text
            circles_spawned++;
        } else {
            if (completion_timer > 2 + (circles_spawned * 0.1)) {
                spawn_particle(END_WALL_COMPLETE_CIRCLES, state.camera_x + WIDTH_ADJUST_AREA + SCREEN_WIDTH_AREA / 2, state.camera_y + SCREEN_HEIGHT_AREA / 2, NULL); // Comes from complete text
                circles_spawned++;
            }
        }
        fade_rays();
        completion_shake = FALSE;
    }

    if (completion_timer > 5) {
        completion_timer = 0.0f;
        MP3Player_Stop();
        complete_text_elapsed = 0.f;
        complete_level_flag = FALSE;
        if (current_song_pointer) free(current_song_pointer);
        gameRoutine = ROUTINE_MENU;
        erase_rays();
        return TRUE;
    }

    completion_timer += dt;
    return FALSE;
}