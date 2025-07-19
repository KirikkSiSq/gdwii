#include <grrlib.h>
#include "game_bg_png.h"
#include "game_ground_png.h"
#include "objects.h"
#include "level_loading.h"
#include "stdio.h"
#include "object_includes.h"
#include "ground_line_png.h"
#include "main.h"
#include "math.h"
#include <math.h>
#include "game.h"
#include "custom_mp3player.h"
#include "player.h"
#include "trail.h"
#include "level.h"

#include <wiiuse/wpad.h>
#include "particles.h"
#include "particle_png.h"
#include <ogc/lwp_watchdog.h>

float jump_heights_table[JUMP_TYPES_COUNT][GAMEMODE_COUNT] = {
    /* YELLOW PAD */ {864,    432,    518.4},
    /* YELLOW ORB */ {603.72, 603.72, 422.60399},
    /* BLUE PAD   */ {-345.6, -345.6, -207.36001},
    /* BLUE ORB   */ {-241.488, -241.488, -169.04160},
};

struct ColorChannel channels[COL_CHANNEL_COUNT] = {
    // BG
    {
        .color = {
            .r = 56,
            .g = 121,
            .b = 255,
        },
        .blending = FALSE
    },
    // Ground
    {
        .color = {
            .r = 56,
            .g = 121,
            .b = 255,
        },
        .blending = FALSE
    },
    // Obj
    {
        .color = {
            .r = 255,
            .g = 255,
            .b = 255,
        },
        .blending = FALSE
    },
    // Line
    {
        .color = {
            .r = 255,
            .g = 255,
            .b = 255,
        },
        .blending = TRUE
    },
    // Black
    {
        .color = {
            .r = 0,
            .g = 0,
            .b = 0,
        },
        .blending = FALSE
    },
    // LBG -- add later
    {
        .color = {
            .r = 0,
            .g = 0,
            .b = 0,
        },
        .blending = FALSE
    },
    // P1
    {
        .color = {
            .r = 0,
            .g = 255,
            .b = 0,
        },
        .blending = TRUE
    },
    // P2
    {
        .color = {
            .r = 0,
            .g = 255,
            .b = 255,
        },
        .blending = TRUE
    },
    // Unmodifiable (white)
    {
        .color = {
            .r = 255,
            .g = 255,
            .b = 255,
        },
        .blending = FALSE
    }
};

float get_mirror_x(float x, float factor) {
    return x + factor * (screenWidth - 2.0f * x);
}

void set_intended_ceiling(Player *player) {
    float mid_point = (player->ground_y + player->ceiling_y) / 2;
    state.camera_intended_y = mid_point - (SCREEN_HEIGHT_AREA / 2);
}

void handle_special_hitbox(Player *player, GDObjectTyped *obj, ObjectHitbox *hitbox) {
    switch (obj->id) {
        case YELLOW_PAD:
            MotionTrail_ResumeStroke(&trail);
            set_p_velocity(player, jump_heights_table[JUMP_YELLOW_PAD][player->gamemode]);
            player->on_ground = FALSE;
            
            particle_templates[USE_EFFECT].start_scale = 0;
            particle_templates[USE_EFFECT].end_scale = 60;

            particle_templates[USE_EFFECT].start_color.r = 255;
            particle_templates[USE_EFFECT].start_color.g = 255;
            particle_templates[USE_EFFECT].start_color.b = 0;
            particle_templates[USE_EFFECT].start_color.a = 255;

            particle_templates[USE_EFFECT].end_color.r = 255;
            particle_templates[USE_EFFECT].end_color.g = 255;
            particle_templates[USE_EFFECT].end_color.b = 0;
            particle_templates[USE_EFFECT].end_color.a = 0;

            spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

            obj->activated = TRUE;
            break;

        case BLUE_PAD:
            float rotation = adjust_angle(obj->rotation, obj->flippedV, obj->flippedH);
            if ((rotation < 90 || rotation > 270) && player->upside_down)
			    break;
                
            if ((rotation > 90 && rotation < 270) && !player->upside_down)
			    break;

            MotionTrail_ResumeStroke(&trail);
            set_p_velocity(player, jump_heights_table[JUMP_BLUE_PAD][player->gamemode]);
            player->upside_down ^= 1;
            player->on_ground = FALSE;
            
            particle_templates[USE_EFFECT].start_scale = 0;
            particle_templates[USE_EFFECT].end_scale = 60;

            particle_templates[USE_EFFECT].start_color.r = 56;
            particle_templates[USE_EFFECT].start_color.g = 200;
            particle_templates[USE_EFFECT].start_color.b = 255;
            particle_templates[USE_EFFECT].start_color.a = 255;

            particle_templates[USE_EFFECT].end_color.r = 56;
            particle_templates[USE_EFFECT].end_color.g = 200;
            particle_templates[USE_EFFECT].end_color.b = 255;
            particle_templates[USE_EFFECT].end_color.a = 0;

            spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

            obj->activated = TRUE;
            break;
        
        case YELLOW_ORB:
            if ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) && player->buffering_state == BUFFER_READY) {    
                MotionTrail_ResumeStroke(&trail);
                
                set_p_velocity(player, jump_heights_table[JUMP_YELLOW_ORB][player->gamemode]);
                
                player->ball_rotation_speed = -1.f;
                
                player->on_ground = FALSE;
                player->on_ceiling = FALSE;
                player->buffering_state = BUFFER_END;

                particle_templates[USE_EFFECT].start_scale = 50;
                particle_templates[USE_EFFECT].end_scale = 0;

                particle_templates[USE_EFFECT].start_color.r = 255;
                particle_templates[USE_EFFECT].start_color.g = 255;
                particle_templates[USE_EFFECT].start_color.b = 0;
                particle_templates[USE_EFFECT].start_color.a = 0;

                particle_templates[USE_EFFECT].end_color.r = 255;
                particle_templates[USE_EFFECT].end_color.g = 255;
                particle_templates[USE_EFFECT].end_color.b = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            } 
            if (!obj->collided) spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
            break;
        
        case BLUE_ORB:
            if ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) && player->buffering_state == BUFFER_READY) {    
                MotionTrail_ResumeStroke(&trail);
                
                set_p_velocity(player, jump_heights_table[JUMP_BLUE_ORB][player->gamemode]);
                player->upside_down ^= 1;
                
                player->ball_rotation_speed = -1.f;
                
                player->on_ground = FALSE;
                player->on_ceiling = FALSE;
                player->buffering_state = BUFFER_END;

                particle_templates[USE_EFFECT].start_scale = 50;
                particle_templates[USE_EFFECT].end_scale = 0;

                particle_templates[USE_EFFECT].start_color.r = 56;
                particle_templates[USE_EFFECT].start_color.g = 200;
                particle_templates[USE_EFFECT].start_color.b = 255;
                particle_templates[USE_EFFECT].start_color.a = 0;

                particle_templates[USE_EFFECT].end_color.r = 56;
                particle_templates[USE_EFFECT].end_color.g = 200;
                particle_templates[USE_EFFECT].end_color.b = 255;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            } 
            if (!obj->collided) spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
            break;

        case CUBE_PORTAL: 
            if (player->gamemode != GAMEMODE_CUBE) {
                if (player->gamemode != GAMEMODE_BALL) MotionTrail_StopStroke(&trail);
                player->ground_y = 0;
                player->ceiling_y = 999999;

                if (player->gamemode != GAMEMODE_BALL) player->vel_y /= 2;

                player->gamemode = GAMEMODE_CUBE;

                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                particle_templates[USE_EFFECT].start_color.r = 0;
                particle_templates[USE_EFFECT].start_color.g = 255;
                particle_templates[USE_EFFECT].start_color.b = 50;
                particle_templates[USE_EFFECT].start_color.a = 0;

                particle_templates[USE_EFFECT].end_color.r = 0;
                particle_templates[USE_EFFECT].end_color.g = 255;
                particle_templates[USE_EFFECT].end_color.b = 50;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
            }
            obj->activated = TRUE;
            break;
            
        case SHIP_PORTAL: 
            player->ground_y = maxf(0, ceilf((obj->y - 180) / 30.f)) * 30;
            player->ceiling_y = player->ground_y + 300;
            set_intended_ceiling(player);

            if (player->gamemode != GAMEMODE_SHIP) {
                player->vel_y /= 2;
                player->gamemode = GAMEMODE_SHIP;

                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                particle_templates[USE_EFFECT].start_color.r = 255;
                particle_templates[USE_EFFECT].start_color.g = 31;
                particle_templates[USE_EFFECT].start_color.b = 255;
                particle_templates[USE_EFFECT].start_color.a = 0;

                particle_templates[USE_EFFECT].end_color.r = 255;
                particle_templates[USE_EFFECT].end_color.g = 31;
                particle_templates[USE_EFFECT].end_color.b = 255;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
            }
            obj->activated = TRUE;
            break;
        
        case BLUE_GRAVITY_PORTAL:
            if (player->upside_down) {
                if (player->gamemode != GAMEMODE_BALL) MotionTrail_ResumeStroke(&trail);
                player->vel_y /= -2;
                player->upside_down = FALSE;

                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                particle_templates[USE_EFFECT].start_color.r = 56;
                particle_templates[USE_EFFECT].start_color.g = 200;
                particle_templates[USE_EFFECT].start_color.b = 255;
                particle_templates[USE_EFFECT].start_color.a = 0;

                particle_templates[USE_EFFECT].end_color.r = 56;
                particle_templates[USE_EFFECT].end_color.g = 200;
                particle_templates[USE_EFFECT].end_color.b = 255;
                particle_templates[USE_EFFECT].end_color.a = 255;
                
                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
            }
            obj->activated = TRUE;
            break;
        case YELLOW_GRAVITY_PORTAL:
            if (!player->upside_down) {
                if (player->gamemode != GAMEMODE_BALL) MotionTrail_ResumeStroke(&trail);
                player->vel_y /= -2;
                player->upside_down = TRUE;

                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                particle_templates[USE_EFFECT].start_color.r = 255;
                particle_templates[USE_EFFECT].start_color.g = 255;
                particle_templates[USE_EFFECT].start_color.b = 0;
                particle_templates[USE_EFFECT].start_color.a = 0;

                particle_templates[USE_EFFECT].end_color.r = 255;
                particle_templates[USE_EFFECT].end_color.g = 255;
                particle_templates[USE_EFFECT].end_color.b = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;
                
                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
            }
            obj->activated = TRUE;
            break;
        case ORANGE_MIRROR_PORTAL:
            particle_templates[USE_EFFECT].start_scale = 80;
            particle_templates[USE_EFFECT].end_scale = 0;

            particle_templates[USE_EFFECT].start_color.r = 255;
            particle_templates[USE_EFFECT].start_color.g = 94;
            particle_templates[USE_EFFECT].start_color.b = 0;
            particle_templates[USE_EFFECT].start_color.a = 0;

            particle_templates[USE_EFFECT].end_color.r = 255;
            particle_templates[USE_EFFECT].end_color.g = 94;
            particle_templates[USE_EFFECT].end_color.b = 0;
            particle_templates[USE_EFFECT].end_color.a = 255;
            
            spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

            state.intended_mirror_factor = 1.f;
            state.intended_mirror_speed_factor = -1.f;
            obj->activated = TRUE;
            break;
        case BLUE_MIRROR_PORTAL:
            particle_templates[USE_EFFECT].start_scale = 80;
            particle_templates[USE_EFFECT].end_scale = 0;

            particle_templates[USE_EFFECT].start_color.r = 56;
            particle_templates[USE_EFFECT].start_color.g = 200;
            particle_templates[USE_EFFECT].start_color.b = 255;
            particle_templates[USE_EFFECT].start_color.a = 0;

            particle_templates[USE_EFFECT].end_color.r = 56;
            particle_templates[USE_EFFECT].end_color.g = 200;
            particle_templates[USE_EFFECT].end_color.b = 255;
            particle_templates[USE_EFFECT].end_color.a = 255;
            
            spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

            state.intended_mirror_factor = 0.f;
            state.intended_mirror_speed_factor = 1.f;
            obj->activated = TRUE;
            break;
        
        case BALL_PORTAL: 
            player->ground_y = maxf(0, ceilf((obj->y - 150) / 30.f)) * 30;
            player->ceiling_y = player->ground_y + 240;
            set_intended_ceiling(player);

            if (player->gamemode != GAMEMODE_BALL) {
                player->ball_rotation_speed = -1.f;

                if (player->gamemode == GAMEMODE_SHIP) player->vel_y /= 2;
                
                player->gamemode = GAMEMODE_BALL;

                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                particle_templates[USE_EFFECT].start_color.r = 255;
                particle_templates[USE_EFFECT].start_color.g = 0;
                particle_templates[USE_EFFECT].start_color.b = 0;
                particle_templates[USE_EFFECT].start_color.a = 0;

                particle_templates[USE_EFFECT].end_color.r = 255;
                particle_templates[USE_EFFECT].end_color.g = 0;
                particle_templates[USE_EFFECT].end_color.b = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
            }
            obj->activated = TRUE;
            break;

        case BIG_PORTAL:
            player->mini = FALSE;

            particle_templates[USE_EFFECT].start_scale = 80;
            particle_templates[USE_EFFECT].end_scale = 0;

            particle_templates[USE_EFFECT].start_color.r = 0;
            particle_templates[USE_EFFECT].start_color.g = 255;
            particle_templates[USE_EFFECT].start_color.b = 50;
            particle_templates[USE_EFFECT].start_color.a = 0;

            particle_templates[USE_EFFECT].end_color.r = 0;
            particle_templates[USE_EFFECT].end_color.g = 255;
            particle_templates[USE_EFFECT].end_color.b = 50;
            particle_templates[USE_EFFECT].end_color.a = 255;

            spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
            
            obj->activated = TRUE;
            break;        

        case MINI_PORTAL:
            player->mini = TRUE;

            particle_templates[USE_EFFECT].start_scale = 80;
            particle_templates[USE_EFFECT].end_scale = 0;

            particle_templates[USE_EFFECT].start_color.r = 255;
            particle_templates[USE_EFFECT].start_color.g = 31;
            particle_templates[USE_EFFECT].start_color.b = 255;
            particle_templates[USE_EFFECT].start_color.a = 0;

            particle_templates[USE_EFFECT].end_color.r = 255;
            particle_templates[USE_EFFECT].end_color.g = 31;
            particle_templates[USE_EFFECT].end_color.b = 255;
            particle_templates[USE_EFFECT].end_color.a = 255;
            
            spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
            
            obj->activated = TRUE;
            break;
    }
}

// Prepare Graphics
GRRLIB_texImg *bg;
GRRLIB_texImg *ground;
GRRLIB_texImg *ground_line;
GRRLIB_texImg *object_images[OBJECT_COUNT][MAX_OBJECT_LAYERS]; 

int current_fading_effect = FADE_NONE;

bool p1_trail = FALSE;

struct TriggerBuffer trigger_buffer[COL_CHANNEL_COUNT];

void load_spritesheet() {
    // Load Textures 
    bg = GRRLIB_LoadTexturePNG(game_bg_png);
    ground = GRRLIB_LoadTexturePNG(game_ground_png);
    ground_line = GRRLIB_LoadTexturePNG(ground_line_png);
    particleTex = GRRLIB_LoadTexturePNG(particle_png);

    for (s32 object = 1; object < OBJECT_COUNT; object++) {
        for (s32 layer = 0; layer < MAX_OBJECT_LAYERS; layer++) {
            // Skip unused layers
            if (!objects[object].layers[layer].texture) continue;

            printf("Loading texture of object %d layer %d\n", object, layer);
            
            GRRLIB_texImg *image = GRRLIB_LoadTexturePNG((const u8 *) objects[object].layers[layer].texture);
            if (image == NULL || image->data == NULL) {
                printf("Couldn't load texture of object %d layer %d\n", object, layer);
            } else {
                printf("Loaded texture of object %d layer %d\n", object, layer);
                GRRLIB_SetHandle(image, (image->w/2), (image->h/2));
                object_images[object][layer] = image;
            }
        }
    }

    load_icons();
}

void unload_spritesheet() {
    // Free all memory used by textures.
    GRRLIB_FreeTexture(bg);
    GRRLIB_FreeTexture(ground);
    GRRLIB_FreeTexture(ground_line);
    GRRLIB_FreeTexture(particleTex);

    for (s32 object = 0; object < OBJECT_COUNT; object++) {
        for (s32 layer = 0; layer < objects[object].num_layers; layer++) {
            GRRLIB_FreeTexture(object_images[object][layer]);
        }
    }
    
    unload_icons();
}

void handle_object_particles(GDObjectTyped *obj, GDObjectLayer *layer) {
    switch (obj->id) {
        case YELLOW_ORB:
            particle_templates[ORB_PARTICLES].start_color.r = 255;
            particle_templates[ORB_PARTICLES].start_color.g = 255;
            particle_templates[ORB_PARTICLES].start_color.b = 0;

            particle_templates[ORB_PARTICLES].end_color.r = 255;
            particle_templates[ORB_PARTICLES].end_color.g = 255;
            particle_templates[ORB_PARTICLES].end_color.b = 0;
            if (!state.player.dead) spawn_particle(ORB_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(ORB_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            break;
        
        case YELLOW_PAD:
            particle_templates[PAD_PARTICLES].angle = 180.f - (adjust_angle_y(obj->rotation, obj->flippedV) + 90.f);

            particle_templates[PAD_PARTICLES].start_color.r = 255;
            particle_templates[PAD_PARTICLES].start_color.g = 255;
            particle_templates[PAD_PARTICLES].start_color.b = 0;

            particle_templates[PAD_PARTICLES].end_color.r = 255;
            particle_templates[PAD_PARTICLES].end_color.g = 255;
            particle_templates[PAD_PARTICLES].end_color.b = 0;

            if (!state.player.dead) spawn_particle(PAD_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(PAD_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            break;

        case BLUE_ORB:
            particle_templates[ORB_PARTICLES].start_color.r = 56;
            particle_templates[ORB_PARTICLES].start_color.g = 200;
            particle_templates[ORB_PARTICLES].start_color.b = 255;

            particle_templates[ORB_PARTICLES].end_color.r = 56;
            particle_templates[ORB_PARTICLES].end_color.g = 200;
            particle_templates[ORB_PARTICLES].end_color.b = 255;
            if (!state.player.dead) spawn_particle(ORB_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(ORB_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            break;
        
        case BLUE_PAD:
            particle_templates[PAD_PARTICLES].angle = 180.f - (adjust_angle_y(obj->rotation, obj->flippedV) + 90.f);
            
            particle_templates[PAD_PARTICLES].start_color.r = 56;
            particle_templates[PAD_PARTICLES].start_color.g = 200;
            particle_templates[PAD_PARTICLES].start_color.b = 255;

            particle_templates[PAD_PARTICLES].end_color.r = 56;
            particle_templates[PAD_PARTICLES].end_color.g = 200;
            particle_templates[PAD_PARTICLES].end_color.b = 255;
            if (!state.player.dead) spawn_particle(PAD_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(PAD_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            break;
            
            
        case YELLOW_GRAVITY_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_x(obj->rotation, obj->flippedH);

                particle_templates[PORTAL_PARTICLES].start_color.r = 255;
                particle_templates[PORTAL_PARTICLES].start_color.g = 255;
                particle_templates[PORTAL_PARTICLES].start_color.b = 0;
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;

                particle_templates[PORTAL_PARTICLES].end_color.r = 255;
                particle_templates[PORTAL_PARTICLES].end_color.g = 255;
                particle_templates[PORTAL_PARTICLES].end_color.b = 0;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                if (!state.player.dead) spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;

        case BLUE_GRAVITY_PORTAL:
        case BLUE_MIRROR_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_x(obj->rotation, obj->flippedH);

                particle_templates[PORTAL_PARTICLES].start_color.r = 56;
                particle_templates[PORTAL_PARTICLES].start_color.g = 200;
                particle_templates[PORTAL_PARTICLES].start_color.b = 255;
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;

                particle_templates[PORTAL_PARTICLES].end_color.r = 56;
                particle_templates[PORTAL_PARTICLES].end_color.g = 200;
                particle_templates[PORTAL_PARTICLES].end_color.b = 255;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                if (!state.player.dead) spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;
        
        case CUBE_PORTAL:
        case BIG_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_x(obj->rotation, obj->flippedH);

                particle_templates[PORTAL_PARTICLES].start_color.r = 0;
                particle_templates[PORTAL_PARTICLES].start_color.g = 255;
                particle_templates[PORTAL_PARTICLES].start_color.b = 50;
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;

                particle_templates[PORTAL_PARTICLES].end_color.r = 0;
                particle_templates[PORTAL_PARTICLES].end_color.g = 255;
                particle_templates[PORTAL_PARTICLES].end_color.b = 50;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                if (!state.player.dead) spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;

        case SHIP_PORTAL:
        case MINI_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_x(obj->rotation, obj->flippedH);

                particle_templates[PORTAL_PARTICLES].start_color.r = 255;
                particle_templates[PORTAL_PARTICLES].start_color.g = 31;
                particle_templates[PORTAL_PARTICLES].start_color.b = 255;
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;

                particle_templates[PORTAL_PARTICLES].end_color.r = 255;
                particle_templates[PORTAL_PARTICLES].end_color.g = 31;
                particle_templates[PORTAL_PARTICLES].end_color.b = 255;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                if (!state.player.dead) spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;

        case ORANGE_MIRROR_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_x(obj->rotation, obj->flippedH);

                particle_templates[PORTAL_PARTICLES].start_color.r = 255;
                particle_templates[PORTAL_PARTICLES].start_color.g = 91;
                particle_templates[PORTAL_PARTICLES].start_color.b = 0;
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;

                particle_templates[PORTAL_PARTICLES].end_color.r = 255;
                particle_templates[PORTAL_PARTICLES].end_color.g = 91;
                particle_templates[PORTAL_PARTICLES].end_color.b = 0;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                if (!state.player.dead) spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;
        
        case BALL_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_x(obj->rotation, obj->flippedH);

                particle_templates[PORTAL_PARTICLES].start_color.r = 255;
                particle_templates[PORTAL_PARTICLES].start_color.g = 0;
                particle_templates[PORTAL_PARTICLES].start_color.b = 0;
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;

                particle_templates[PORTAL_PARTICLES].end_color.r = 255;
                particle_templates[PORTAL_PARTICLES].end_color.g = 0;
                particle_templates[PORTAL_PARTICLES].end_color.b = 0;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                if (!state.player.dead) spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;
    }
}

int get_fade_value(float x, int right_edge) {
    #define FADE_WIDTH 75
    if (x < 0 || x > right_edge)
        return 0;
    else if (x < FADE_WIDTH)
        return (int)(255.0f * (x / FADE_WIDTH));
    else if (x > right_edge - FADE_WIDTH)
        return (int)(255.0f * ((right_edge - x) / FADE_WIDTH));
    else
        return 255;
}

int get_xy_fade_offset(float x, int right_edge) {
    int fade = get_fade_value(x, right_edge);
    return (255 - fade) / 2;
}

float get_in_scale_fade(float x, int right_edge) {
    int fade = get_fade_value(x, right_edge);
    return (fade / 255.f);
}

float get_out_scale_fade(float x, int right_edge) {
    int fade = 255 - get_fade_value(x, right_edge);
    return 1 + ((fade / 255.f) / 2);
}

void get_fade_vars(GDObjectTyped *obj, float x, int *fade_x, int *fade_y, float *fade_scale) {
    switch (obj->transition_applied) {
        case FADE_NONE:
            break;
        case FADE_UP:
            *fade_y = get_xy_fade_offset(x, screenWidth);
            break;
        case FADE_DOWN:
            *fade_y = -get_xy_fade_offset(x, screenWidth);
            break;
        case FADE_RIGHT:
            *fade_x = get_xy_fade_offset(x, screenWidth) * state.mirror_mult;
            break;
        case FADE_LEFT:
            *fade_x = -get_xy_fade_offset(x, screenWidth) * state.mirror_mult;
            break;
        case FADE_SCALE_IN:
            *fade_scale = get_in_scale_fade(x, screenWidth);
            break;
        case FADE_SCALE_OUT:
            *fade_scale = get_out_scale_fade(x, screenWidth);
            break;
        case FADE_UP_SLOW:
            *fade_x = get_xy_fade_offset(x, screenWidth) * state.mirror_mult * ((current_fading_effect == FADE_CIRCLE_RIGHT) ? 1 : -1);
        case FADE_UP_STATIONARY:
            *fade_y = get_xy_fade_offset(x, screenWidth) / 3;
            break;
        case FADE_DOWN_SLOW:
            *fade_x = get_xy_fade_offset(x, screenWidth) * state.mirror_mult * ((current_fading_effect == FADE_CIRCLE_RIGHT) ? 1 : -1);
        case FADE_DOWN_STATIONARY:
            *fade_y = -get_xy_fade_offset(x, screenWidth) / 3;
            break;
    }
}

int layer_pulses(GDObjectTyped *obj, GDObjectLayer *layer) {
    switch (obj->id) {
        case YELLOW_ORB:
        case BLUE_ORB:
        case PULSING_CIRCLE:
        case PULSING_CIRCUNFERENCE:
        case PULSING_HEART:
        case PULSING_DIAMOND:
        case PULSING_STAR:
        case PULSING_NOTE:
            return 1;
        case ROD_BIG:
        case ROD_MEDIUM:
        case ROD_SMALL:
            if (layer->layerNum == 1) {
                return 1;
            }
            break;
    }

    return 0;
}

float get_object_pulse(float amplitude, GDObjectTyped *obj) {
    switch (obj->id) {
        case YELLOW_ORB:
        case BLUE_ORB:
            return map_range(amplitude, 0.f, 1.f, 0.3f, 1.2f);
        case PULSING_CIRCLE:
        case PULSING_CIRCUNFERENCE:
        case PULSING_HEART:
        case PULSING_DIAMOND:
        case PULSING_STAR:
        case PULSING_NOTE:
        case ROD_BIG:
        case ROD_MEDIUM:
        case ROD_SMALL:
            return amplitude;
    }
    return amplitude;
}

GRRLIB_texImg *get_randomized_texture(GRRLIB_texImg *image, GDObjectTyped *obj, GDObjectLayer *layer) {
    switch (obj->id) {
        case GROUND_SPIKE:
            return object_images[GROUND_SPIKE][obj->random % 3];
        case ROD_BIG:
        case ROD_MEDIUM:
        case ROD_SMALL:
            if (layer->layerNum == 1) {
                return object_images[ROD_BIG][level_info.pulsing_type + 1]; // balls start at 1
            }
            break;
            
    }

    return image;
}

int get_opacity(GDObjectTyped *obj, float x) {
    int opacity = get_fade_value(x, screenWidth);

    switch (obj->id) {
        case BLACK_FULL:
        case BLACK_EDGE:
        case BLACK_CORNER:
        case BLACK_INS_CORNER:
        case BLACK_FILLER:
        case BLACK_PILLAR_END:
        case BLACK_PILLAR:
            if (obj->transition_applied == FADE_NONE) opacity = 255;
            break;
    }

    return opacity;
}

static inline void put_object_layer(GDObjectTyped *obj, float x, float y, GDObjectLayer *layer) {
    u64 t0 = gettime();

    int obj_id = obj->id;

    int layer_index = layer->layerNum;

    int x_flip_mult = (obj->flippedH ? -1 : 1);
    int y_flip_mult = (obj->flippedV ? -1 : 1);

    struct ObjectLayer *objectLayer = layer->layer;
    float x_offset = objectLayer->x_offset * x_flip_mult;
    float y_offset = objectLayer->y_offset * y_flip_mult;

    GRRLIB_texImg *image = object_images[obj_id][layer_index];

    int width = image->w;
    int height = image->h;

    int col_channel = objectLayer->col_channel;

    if (channels[col_channel].blending) {
        GRRLIB_SetBlend(GRRLIB_BLEND_ADD);
    } else {
        GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
    }
    
    int opacity = get_opacity(obj, x);
    
    u32 color = RGBA(channels[col_channel].color.r, channels[col_channel].color.g, channels[col_channel].color.b, opacity);
        
    float angle_rad = obj->rotation * (M_PI / 180.0f); // Convert degrees to radians
    float cos_a = cosf(angle_rad);
    float sin_a = sinf(angle_rad);

    float x_off_rot = (x_offset * cos_a - y_offset * sin_a) * state.mirror_mult;
    float y_off_rot = x_offset * sin_a + y_offset * cos_a;

    int fade_x = 0;
    int fade_y = 0;

    float fade_scale = 1.f;

    get_fade_vars(obj, x, &fade_x, &fade_y, &fade_scale);

    if (layer_pulses(obj, layer)) {
        obj->ampl_scaling = iSlerp(obj->ampl_scaling, get_object_pulse(amplitude, obj), 0.2f, STEPS_DT);
        fade_scale *= obj->ampl_scaling;
    }

    float rotation = adjust_angle(obj->rotation, 0, state.mirror_mult < 0);

    switch(obj->id) {
        case ROD_BIG:
        case ROD_MEDIUM:
        case ROD_SMALL:
            if (layer->layerNum == 1) {
                rotation = 0.f;
                x_flip_mult = 1.f;
                y_flip_mult = 1.f;
            }
    }

    if (obj->transition_applied == FADE_DOWN_STATIONARY || obj->transition_applied == FADE_UP_STATIONARY) {
        if (opacity < 255) {
            if (x > screenWidth / 2) {
                x = screenWidth - FADE_WIDTH;
            } else {
                x = FADE_WIDTH;
            }
        }
    }
    u64 t1 = gettime();
    layer_calc_time += ticks_to_microsecs(t1 - t0) / 1000.f;
    
    t0 = gettime();
    GRRLIB_DrawImg(
        /* X        */ get_mirror_x(x, state.mirror_factor) + 6 - (width/2) + x_off_rot + fade_x,
        /* Y        */ y + 6 - (height/2) + y_off_rot + fade_y,
        /* Texture  */ get_randomized_texture(image, obj, layer), 
        /* Rotation */ rotation, 
        /* Scale X  */ 0.73333333333333333333333333333333 * x_flip_mult * fade_scale * state.mirror_mult, 
        /* Scale Y  */ 0.73333333333333333333333333333333 * y_flip_mult * fade_scale, 
        /* Color    */ color
    );
    t1 = gettime();
    
    draw_time += ticks_to_microsecs(t1 - t0) / 1000.f;
}


void draw_background_image(f32 x, f32 y, bool vflip) {
    for (s32 i = 0; i < BG_DIMENSIONS; i++) {
        float calc_x = i*BG_CHUNK;
        for (s32 j = 0; j < BG_DIMENSIONS; j++) {
            float calc_y = j*BG_CHUNK;
            
            GRRLIB_SetHandle(bg, 512, 512);
            GRRLIB_DrawPart(
                x + calc_x, 
                y + (vflip ? (BG_CHUNK * 3) - calc_y : calc_y), 
                i * 256, 
                j * 256,
                256, 
                256,
                bg, 0, 1 * BACKGROUND_SCALE, (vflip ? -1 : 1) * BACKGROUND_SCALE, RGBA(channels[BG].color.r, channels[BG].color.g, channels[BG].color.b, 255)
            );
        }
    }
}

void draw_background(f32 x, f32 y) {
    float offset = 1024 * BACKGROUND_SCALE;
    int tiles_x = (screenWidth / offset) + 2;
    int tiles_y = (screenHeight / offset) + 2;

    float calc_x = positive_fmod(x, offset);
    float calc_y = positive_fmod(y, offset);

    for (int i = -1; i < tiles_x; i++) {
        for (int j = -1; j < tiles_y; j++) {
            // Calculate position for each tile
            float draw_x = -calc_x + i * offset;
            float draw_y = -calc_y + j * offset;
            
            // Flip every other row
            bool vflip = ((j % 2) != 0);
            draw_background_image(draw_x, draw_y, vflip);
        }
    }
}

#define GROUND_SIZE 176 // pixels
#define LINE_SCALE 0.5f

void draw_end_wall() {
    float calc_x = ((level_info.wall_x - state.camera_x) * SCALE);
    float calc_y =  positive_fmod(state.camera_y * SCALE, BLOCK_SIZE_PX) + screenHeight;    
    
    if (calc_x < screenWidth + 20) {
        for (s32 j = 0; j < objects[CHECKER_EDGE].num_layers; j++) {
            GRRLIB_texImg *image = object_images[CHECKER_EDGE][j];
            int width = image->w;
            int height = image->h;

            for (float i = -BLOCK_SIZE_PX; i < screenHeight + BLOCK_SIZE_PX * 2; i += BLOCK_SIZE_PX) {
                GRRLIB_DrawImg(
                    get_mirror_x(calc_x + 6, state.mirror_factor) - (width/2), 
                    calc_y + 6 - i - (height/2),    
                    image,
                    adjust_angle(270, 0, state.mirror_mult < 0),
                    0.73333333333333333333333333333333 * state.mirror_mult, 0.73333333333333333333333333333333,
                    RGBA(255, 255, 255, 255) 
                );
            }
        }
    }
}

void draw_ground(f32 y, bool is_ceiling) {
    int mult = (is_ceiling ? -1 : 1);

    float calc_x = 0 - positive_fmod(state.ground_x * SCALE, GROUND_SIZE);
    float calc_y = screenHeight - ((y - state.camera_y) * SCALE);

    for (float i = -GROUND_SIZE; i < screenWidth + GROUND_SIZE; i += GROUND_SIZE) {
        GRRLIB_DrawImg(
            calc_x + i + 6, 
            calc_y + 6,    
            ground,
            0, 1.375, 1.375 * mult,
            RGBA(channels[GROUND].color.r, channels[GROUND].color.g, channels[GROUND].color.b, 255) 
        );
    }

    if (channels[LINE].blending) {
        GRRLIB_SetBlend(GRRLIB_BLEND_ADD);
    }

    int line_width = ground_line->w;
    
    GRRLIB_DrawImg(
        (screenWidth / 2) - (line_width / (2 / LINE_SCALE)),
        calc_y + (is_ceiling ? 4 : 6),
        ground_line,
        0, LINE_SCALE, 0.75,
        RGBA(channels[LINE].color.r, channels[LINE].color.g, channels[LINE].color.b, 255)
    );
    
    if (channels[LINE].blending) {
        GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
    }
}

void handle_special_fading(GDObjectTyped *obj, float calc_x, float calc_y) {
    switch (current_fading_effect) {
        case FADE_INWARDS:
            if (calc_y > (screenHeight / 2)) {
                obj->transition_applied = FADE_UP;
            } else {
                obj->transition_applied = FADE_DOWN;
            }
            break;
        case FADE_OUTWARDS:
            if (calc_y > (screenHeight / 2)) {
                obj->transition_applied = FADE_DOWN;
            } else {
                obj->transition_applied = FADE_UP;
            }
            break;
        case FADE_CIRCLE_LEFT:
            if (calc_x > (screenWidth / 2)) {
                if (calc_y > (screenHeight / 2)) {
                    obj->transition_applied = FADE_UP_STATIONARY;
                } else {
                    obj->transition_applied = FADE_DOWN_STATIONARY;
                }
            } else {
                if (calc_y > (screenHeight / 2)) {
                    obj->transition_applied = FADE_UP_SLOW;
                } else {
                    obj->transition_applied = FADE_DOWN_SLOW;
                }
            }
            break;
        case FADE_CIRCLE_RIGHT:
            if (calc_x > (screenWidth / 2)) {
                if (calc_y > (screenHeight / 2)) {
                    obj->transition_applied = FADE_UP_SLOW;
                } else {
                    obj->transition_applied = FADE_DOWN_SLOW;
                }
            } else {
                if (calc_y > (screenHeight / 2)) {
                    obj->transition_applied = FADE_UP_STATIONARY;
                } else {
                    obj->transition_applied = FADE_DOWN_STATIONARY;
                }
            }
            break;
        default:
            obj->transition_applied = current_fading_effect;  
    }   
}

int layersDrawn = 0;

float get_rotation_speed(GDObjectTyped *obj) {
    switch (obj->id) {
        case SAW_BIG: 
        case SAW_MEDIUM:
        case SAW_SMALL:
            return 360.f;
        
        case SAW_DECO_BIG:
        case SAW_DECO_MEDIUM:
        case SAW_DECO_SMALL:
        case SAW_DECO_TINY:
            return 180.f;
    }
    return 0;
}

void draw_all_object_layers() {
    u64 t0 = gettime();
    float screen_x_max = screenWidth + 90.0f;
    float screen_y_max = screenHeight + 90.0f;

    int cam_sx = (int)((state.camera_x + SCREEN_WIDTH_AREA / 2) / GFX_SECTION_SIZE);
    int cam_sy = (int)((state.camera_y + SCREEN_HEIGHT_AREA / 2) / GFX_SECTION_SIZE);

    GDLayerSortable *visible_layers[MAX_VISIBLE_LAYERS];
    int visible_count = 1;

    visible_layers[0] = &gfx_player_layer;

    int width = (SCREEN_WIDTH_AREA / 2) / GFX_SECTION_SIZE + 2;
    int height = (SCREEN_HEIGHT_AREA / 2) / GFX_SECTION_SIZE + 2;

    // Gather layers from all visible sections
    for (int dx = -width; dx <= width; dx++) {
        for (int dy = -height; dy <= height; dy++) {
            GFXSection *sec = get_or_create_gfx_section(cam_sx + dx, cam_sy + dy);
            for (int i = 0; i < sec->layer_count; i++) {
                GDObjectTyped *obj = sec->layers[i]->layer->obj;

                float calc_x = ((obj->x - state.camera_x) * SCALE);
                float calc_y = screenHeight - ((obj->y - state.camera_y) * SCALE);  
                if (calc_x > -90 && calc_x < screen_x_max) {        
                    if (calc_y > -90 && calc_y < screen_y_max) {    
                        if (visible_count < MAX_VISIBLE_LAYERS) {
                            visible_layers[visible_count++] = sec->layers[i];
                        }
                    }
                }
            }
        }
    }

    // Sort globally
    qsort(visible_layers, visible_count, sizeof(GDLayerSortable*), compare_sortable_layers);
    
    u64 t1 = gettime();
    layer_sorting = ticks_to_microsecs(t1 - t0) / 1000.f;

    // Draw in sorted order
    for (int i = 0; i < visible_count; i++) {
        GDObjectLayer *layer = visible_layers[i]->layer;
        GDObjectTyped *obj = layer->obj;

        int obj_id = obj->id;

        if (obj_id == PLAYER_OBJECT) {
            draw_particles(CUBE_DRAG);
            draw_particles(SHIP_TRAIL);
            draw_particles(HOLDING_SHIP_TRAIL);
            draw_player();
            draw_particles(SHIP_DRAG);
        } else if (obj_id - 1 < OBJECT_COUNT) {
            float calc_x = ((obj->x - state.camera_x) * SCALE);
            float calc_y = screenHeight - ((obj->y - state.camera_y) * SCALE);  
            layersDrawn++;

            int fade_val = get_fade_value(calc_x, screenWidth);
            bool fade_edge = (fade_val == 255 || fade_val == 0);
            bool is_layer0 = (layer->layerNum == 0);

            if (is_layer0 && fade_edge) handle_special_fading(obj, calc_x, calc_y);
            
            if (is_layer0 && objects[obj_id].is_saw) {
                obj->rotation += ((obj->random & 1) ? -get_rotation_speed(obj) : get_rotation_speed(obj)) * dt;
            }

            handle_object_particles(obj, layer);
            put_object_layer(obj, calc_x, calc_y, layer);
        }
    }
}

void handle_col_triggers() {
    for (int chan = 0; chan < COL_CHANNEL_COUNT; chan++) {
        struct TriggerBuffer *buffer = &trigger_buffer[chan];

        if (buffer->active) {
            Color lerped_color;

            if (buffer->seconds > 0) {
                float multiplier = buffer->time_run / buffer->seconds;
                lerped_color = color_lerp(buffer->old_color, buffer->new_color, multiplier);
            } else {
                lerped_color = buffer->new_color;
            }

            channels[chan].color = lerped_color;

            buffer->time_run += STEPS_DT;

            if (buffer->time_run > buffer->seconds) {
                buffer->active = FALSE;
            }
        }
    }
}

void handle_triggers(GDObjectTyped *obj) {
    int obj_id = obj->id;

    struct TriggerBuffer *buffer = NULL;

    if (objects[obj_id].is_trigger) {
        if (obj->x < state.player.x && obj->x > state.old_player.x) {
            switch (obj_id) {
                case TRIGGER_FADE_NONE:
                    current_fading_effect = FADE_NONE;
                    break;
                    
                case TRIGGER_FADE_UP:
                    current_fading_effect = FADE_UP;
                    break;
                    
                case TRIGGER_FADE_DOWN:
                    current_fading_effect = FADE_DOWN;
                    break;
                    
                case TRIGGER_FADE_RIGHT:
                    current_fading_effect = FADE_RIGHT;
                    break;
                    
                case TRIGGER_FADE_LEFT:
                    current_fading_effect = FADE_LEFT;
                    break;
                    
                case TRIGGER_FADE_SCALE_IN:
                    current_fading_effect = FADE_SCALE_IN;
                    break;
                    
                case TRIGGER_FADE_SCALE_OUT:
                    current_fading_effect = FADE_SCALE_OUT;
                    break;
                
                case TRIGGER_FADE_INWARDS:
                    current_fading_effect = FADE_INWARDS;
                    break;

                case TRIGGER_FADE_OUTWARDS:
                    current_fading_effect = FADE_OUTWARDS;
                    break;
                
                case TRIGGER_FADE_LEFT_SEMICIRCLE:
                    current_fading_effect = FADE_CIRCLE_LEFT;
                    break;

                case TRIGGER_FADE_RIGHT_SEMICIRCLE:
                    current_fading_effect = FADE_CIRCLE_RIGHT;
                    break;

                case BG_TRIGGER:
                    buffer = &trigger_buffer[BG];
                    buffer->active = TRUE;
                    buffer->old_color = channels[BG].color;
                    buffer->new_color.r = obj->trig_colorR;
                    buffer->new_color.g = obj->trig_colorG;
                    buffer->new_color.b = obj->trig_colorB;
                    buffer->seconds = obj->trig_duration;
                    buffer->time_run = 0;
                    break;
                
                case GROUND_TRIGGER:
                    buffer = &trigger_buffer[GROUND];
                    buffer->active = TRUE;
                    buffer->old_color = channels[GROUND].color;
                    buffer->new_color.r = obj->trig_colorR;
                    buffer->new_color.g = obj->trig_colorG;
                    buffer->new_color.b = obj->trig_colorB;
                    buffer->seconds = obj->trig_duration;
                    buffer->time_run = 0;
                    break;
                         
                case LINE_TRIGGER:
                case 915: // gd converts 1.4 line trigger to 2.0 one for some reason
                    buffer = &trigger_buffer[LINE];
                    buffer->active = TRUE;
                    buffer->old_color = channels[LINE].color;
                    buffer->new_color.r = obj->trig_colorR;
                    buffer->new_color.g = obj->trig_colorG;
                    buffer->new_color.b = obj->trig_colorB;
                    buffer->seconds = obj->trig_duration;
                    buffer->time_run = 0;
                    break;
                
                case ENABLE_TRAIL:
                    p1_trail = TRUE;
                    break;
                
                case DISABLE_TRAIL:
                    p1_trail = FALSE;
                    break;
            }
        }
    }
}

u64 last_beat_time = 0;
int pulse_frames_left = 0;
int beat_pulse = 0;

void update_beat() {
    const float beat_interval_ms = 60000.f / songs[level_info.song_id].tempo;

    u64 now = gettime();
    u64 elapsed_ms = ticks_to_millisecs(now - last_beat_time);

    // Check if we've hit the next beat
    if (elapsed_ms >= beat_interval_ms) {
        last_beat_time = now;
        pulse_frames_left = 20;
        beat_pulse = true;
    }

    // Countdown pulse frames
    if (pulse_frames_left > 0) {
        pulse_frames_left--;
        beat_pulse = true;
    } else {
        beat_pulse = false;
    }

    if (MP3Player_GetAmplitude() < 0.05f) {
        beat_pulse = false;
    }
}

void handle_objects() {
    int sx = (int)(state.player.x / SECTION_SIZE);
    for (int dx = -1; dx <= 1; dx++) {
        for (int sy = 0; sy <= MAX_LEVEL_HEIGHT / SECTION_SIZE; sy++) {
            Section *sec = get_or_create_section(sx + dx, sy);
            for (int i = 0; i < sec->object_count; i++) {
                GDObjectTyped *obj = sec->objects[i];
                handle_triggers(obj);
            }
        }
    }
    handle_col_triggers();
}