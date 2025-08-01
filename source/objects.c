#include <grrlib.h>
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
#include "collision.h"

#include <wiiuse/wpad.h>
#include "particles.h"
#include "particle_png.h"
#include <ogc/lwp_watchdog.h>

GRRLIB_texImg *prev_tex = NULL;
int prev_blending = GRRLIB_BLEND_ALPHA;

const float jump_heights_table[SPEED_COUNT][JUMP_TYPES_COUNT][GAMEMODE_COUNT][2] = {
    { // SLOW               CUBE                   SHIP                  BALL                    UFO
    /* YELLOW PAD */ {{864,      691.2},    {432,      691.2},    {518.4,       414.72002},   {573.48,   458.784}},
    /* YELLOW ORB */ {{573.48,   458.784},  {573.48,   458.784},  {401.435993,  321.148795},  {573.48,   458.784}},
    /* BLUE PAD   */ {{-345.6,   -276.48},  {-229.392, -183.519}, {-160.574397, -128.463298}, {-229.392, -183.519}},
    /* BLUE ORB   */ {{-229.392, -183.519}, {-229.392, -183.519}, {-160.574397, -128.463298}, {-229.392, -183.519}},
    /* PINK PAD   */ {{561.6,    449.28},   {302.4,    241.92},   {362.88001,   290.30401},   {345.6,    276.4}},
    /* PINK ORB   */ {{412.884,  330.318},  {212.166,  169.776},  {309.090595,  247.287596},  {240.84,   192.672}},
    },
    { // NORMAL
    /* YELLOW PAD */ {{864,      691.2},    {432,      691.2},    {518.4,       414.72002},   {432,      691.2}},
    /* YELLOW ORB */ {{603.72,   482.976},  {603.72,   482.976},  {422.60399,   338.08319},   {603.72,   482.976}},
    /* BLUE PAD   */ {{-345.6,   -276.48},  {-345.6,   -276.48},  {-207.36001,  -165.88801},  {-345.6,   -276.48}},
    /* BLUE ORB   */ {{-241.488, -193.185}, {-241.488, -193.18},  {-169.04160,  -135.2295},   {-241.488, -193.185}},
    /* PINK PAD   */ {{561.6,    449.28},   {302.4,    241.92},   {362.88001,   290.30401},   {345.6,    276.4}},
    /* PINK ORB   */ {{434.7,    347.76},   {223.398,  178.686},  {325.42019,   260.3286},    {258.984,  207.198}},
    },
    { // FAST
    /* YELLOW PAD */ {{864,      691.2},    {432,      691.2},    {518.4,       414.72002},   {432,      691.2}},
    /* YELLOW ORB */ {{616.68,   481.734},  {616.68,   481.734},  {431.67599,   345.34079},   {616.68,   481.734}},
    /* BLUE PAD   */ {{-345.6,   -276.48},  {-345.6,   -276.48},  {-207.36001,  -165.88801},  {-345.6,   -276.48}},
    /* BLUE ORB   */ {{-246.672, -197.343}, {-246.672, -197.343}, {-172.6704,   -138.1401},   {-246.672, -197.343}},
    /* PINK PAD   */ {{561.6,    449.28},   {302.4,    241.92},   {362.88001,   290.30401},   {345.6,    276.4}},
    /* PINK ORB   */ {{443.988,  355.212},  {228.15,   182.52},   {332.37539,   265.923},     {258.984,  207.198}},
    },
    { // FASTER
    /* YELLOW PAD */ {{864,      691.2},    {432,      691.2},    {518.4,       414.72002},   {432,      691.2}},
    /* YELLOW ORB */ {{606.42,   485.136},  {606.42,   485.136},  {424.493993,  339.59519},   {606.42,   485.136}},
    /* BLUE PAD   */ {{-345.6,   -276.48},  {-345.6,   -276.48},  {-207.36001,  -165.88801},  {-345.6,   -276.48}},
    /* BLUE ORB   */ {{-242.568, -194.049}, {-242.568, -194.049}, {-169.7976,   -135.8343},   {-242.568, -194.049}},
    /* PINK PAD   */ {{561.6,    449.28},   {302.4,    241.92},   {362.88001,   290.30401},   {345.6,    276.4}},
    /* PINK ORB   */ {{436.644,  349.272},  {224.37,   179.496},  {326.85659,   261.5004},    {254.718,  203.742}},
    }
};

struct ColorChannel channels[COL_CHANNEL_COUNT];

float get_mirror_x(float x, float factor) {
    return x + factor * (screenWidth - 2.0f * x);
}

void set_intended_ceiling(Player *player) {
    float mid_point = (player->ground_y + player->ceiling_y) / 2;
    state.camera_intended_y = mid_point - (SCREEN_HEIGHT_AREA / 2);
}

void set_particle_color(int template_id, int r, int g, int b) {
    particle_templates[template_id].start_color.r = r;
    particle_templates[template_id].start_color.g = g;
    particle_templates[template_id].start_color.b = b;

    particle_templates[template_id].end_color.r = r;
    particle_templates[template_id].end_color.g = g;
    particle_templates[template_id].end_color.b = b;
}

void handle_special_hitbox(Player *player, GameObject *obj, ObjectHitbox *hitbox) {
    switch (obj->id) {
        case YELLOW_PAD:
            if (!obj->activated) {
                MotionTrail_ResumeStroke(&trail);
                player->vel_y = jump_heights_table[player->speed][JUMP_YELLOW_PAD][player->gamemode][player->mini];
                player->on_ground = FALSE;
                player->left_ground = TRUE;
                player->ufo_last_y = player->y;
                
                particle_templates[USE_EFFECT].start_scale = 0;
                particle_templates[USE_EFFECT].end_scale = 60;

                set_particle_color(USE_EFFECT, 255, 255, 0);
                particle_templates[USE_EFFECT].start_color.a = 255;
                particle_templates[USE_EFFECT].end_color.a = 0;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            }
            break;

        case PINK_PAD:
            if (!obj->activated) {
                MotionTrail_ResumeStroke(&trail);
                player->vel_y = jump_heights_table[player->speed][JUMP_PINK_PAD][player->gamemode][player->mini];
                player->on_ground = FALSE;
                player->left_ground = TRUE;
                player->ufo_last_y = player->y;
                
                particle_templates[USE_EFFECT].start_scale = 0;
                particle_templates[USE_EFFECT].end_scale = 60;

                set_particle_color(USE_EFFECT, 255, 31, 255);
                particle_templates[USE_EFFECT].start_color.a = 255;
                particle_templates[USE_EFFECT].end_color.a = 0;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            }
            break;

        case BLUE_PAD:
            if (obj->activated) player->gravObj = obj;
            else {
                float rotation = adjust_angle(obj->rotation, obj->flippedV, obj->flippedH);
                if ((rotation < 90 || rotation > 270) && player->upside_down)
                    break;
                    
                if ((rotation > 90 && rotation < 270) && !player->upside_down)
                    break;

                MotionTrail_ResumeStroke(&trail);
                player->left_ground = TRUE;

                player->gravObj = obj;

                player->vel_y = jump_heights_table[player->speed][JUMP_BLUE_PAD][player->gamemode][player->mini];
                player->upside_down ^= 1;
                player->on_ground = FALSE;
                player->ufo_last_y = player->y;
                
                particle_templates[USE_EFFECT].start_scale = 0;
                particle_templates[USE_EFFECT].end_scale = 60;

                set_particle_color(USE_EFFECT, 56, 200, 255);
                particle_templates[USE_EFFECT].start_color.a = 255;
                particle_templates[USE_EFFECT].end_color.a = 0;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            }
            break;
        
        case YELLOW_ORB:
            if (!obj->activated && (state.input.holdA) && player->buffering_state == BUFFER_READY) {    
                MotionTrail_ResumeStroke(&trail);
                
                player->vel_y = jump_heights_table[player->speed][JUMP_YELLOW_ORB][player->gamemode][player->mini];
                
                player->ball_rotation_speed = -1.f;
                
                player->on_ground = FALSE;
                player->on_ceiling = FALSE;
                player->left_ground = TRUE;
                player->buffering_state = BUFFER_END;
                player->ufo_last_y = player->y;

                particle_templates[USE_EFFECT].start_scale = 50;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 255, 255, 0);
                particle_templates[USE_EFFECT].start_color.a = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            } 
            if (!obj->collided) spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
            break;
        
        case PINK_ORB:
            if (!obj->activated && (state.input.holdA) && player->buffering_state == BUFFER_READY) {    
                MotionTrail_ResumeStroke(&trail);
                
                player->vel_y = jump_heights_table[player->speed][JUMP_PINK_ORB][player->gamemode][player->mini];
                
                player->ball_rotation_speed = -1.f;
                
                player->on_ground = FALSE;
                player->on_ceiling = FALSE;
                player->left_ground = TRUE;
                player->buffering_state = BUFFER_END;
                player->ufo_last_y = player->y;

                particle_templates[USE_EFFECT].start_scale = 50;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 255, 31, 255);
                particle_templates[USE_EFFECT].start_color.a = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            } 
            if (!obj->collided) spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
            break;
        
        case BLUE_ORB:
            if (!obj->activated && (state.input.holdA) && player->buffering_state == BUFFER_READY) {    
                MotionTrail_ResumeStroke(&trail);
                player->gravObj = obj;
                
                player->vel_y = jump_heights_table[player->speed][JUMP_BLUE_ORB][player->gamemode][player->mini];
                player->upside_down ^= 1;
                
                player->ball_rotation_speed = -1.f;
                
                player->on_ground = FALSE;
                player->on_ceiling = FALSE;
                player->left_ground = TRUE;
                player->buffering_state = BUFFER_END;
                player->ufo_last_y = player->y;

                particle_templates[USE_EFFECT].start_scale = 50;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 56, 200, 255);
                particle_templates[USE_EFFECT].start_color.a = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                obj->activated = TRUE;
            } 
            if (!obj->collided) spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
            break;

        case CUBE_PORTAL: 
            if (!obj->activated) {
                if (player->gamemode != GAMEMODE_CUBE) {
                    if (player->gamemode != GAMEMODE_BALL) MotionTrail_StopStroke(&trail);
                    player->ground_y = 0;
                    player->ceiling_y = 999999;

                    if (player->gamemode != GAMEMODE_BALL) player->vel_y /= 2;

                    player->gamemode = GAMEMODE_CUBE;

                    particle_templates[USE_EFFECT].start_scale = 80;
                    particle_templates[USE_EFFECT].end_scale = 0;

                    set_particle_color(USE_EFFECT, 0, 255, 50);
                    particle_templates[USE_EFFECT].start_color.a = 0;
                    particle_templates[USE_EFFECT].end_color.a = 255;

                    spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                }
                obj->activated = TRUE;
            }
            break;
            
        case SHIP_PORTAL: 
            if (!obj->activated) {
                player->ground_y = maxf(0, ip1_ceilf((obj->y - 180) / 30.f)) * 30;
                player->ceiling_y = player->ground_y + 300;
                set_intended_ceiling(player);

                if (player->gamemode != GAMEMODE_SHIP) {
                    player->vel_y /= (player->gamemode == GAMEMODE_UFO) ? 4 : 2;
                    player->gamemode = GAMEMODE_SHIP;

                    particle_templates[USE_EFFECT].start_scale = 80;
                    particle_templates[USE_EFFECT].end_scale = 0;

                    set_particle_color(USE_EFFECT, 255, 31, 255);
                    particle_templates[USE_EFFECT].start_color.a = 0;
                    particle_templates[USE_EFFECT].end_color.a = 255;

                    spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                }
                obj->activated = TRUE;
            }
            break;
        
        case BLUE_GRAVITY_PORTAL:
            player->gravObj = obj;
            if (!obj->activated) {
                player->ceiling_inv_time = 0.1f;
                if (player->upside_down) {
                    if (player->gamemode != GAMEMODE_BALL) MotionTrail_ResumeStroke(&trail);
                    player->vel_y /= -2;
                    player->upside_down = FALSE;
                    player->left_ground = TRUE;
                    player->ufo_last_y = player->y;

                    particle_templates[USE_EFFECT].start_scale = 80;
                    particle_templates[USE_EFFECT].end_scale = 0;

                    set_particle_color(USE_EFFECT, 56, 200, 255);
                    particle_templates[USE_EFFECT].start_color.a = 0;
                    particle_templates[USE_EFFECT].end_color.a = 255;
                    
                    spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                }
                obj->activated = TRUE;
            }
            break;
        case YELLOW_GRAVITY_PORTAL:
            player->gravObj = obj;
            if (!obj->activated) {
                player->ceiling_inv_time = 0.1f;
                if (!player->upside_down) {
                    if (player->gamemode != GAMEMODE_BALL) MotionTrail_ResumeStroke(&trail);
                    player->vel_y /= -2;
                    player->upside_down = TRUE;
                    player->left_ground = TRUE;
                    player->ufo_last_y = player->y;

                    particle_templates[USE_EFFECT].start_scale = 80;
                    particle_templates[USE_EFFECT].end_scale = 0;

                    set_particle_color(USE_EFFECT, 255, 255, 0);
                    particle_templates[USE_EFFECT].start_color.a = 0;
                    particle_templates[USE_EFFECT].end_color.a = 255;
                    
                    spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                }
            }
            obj->activated = TRUE;
            break;
        case ORANGE_MIRROR_PORTAL:
            if (!obj->activated) {
                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 255, 94, 0);
                particle_templates[USE_EFFECT].start_color.a = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;
                
                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                state.intended_mirror_factor = 1.f;
                state.intended_mirror_speed_factor = -1.f;
                obj->activated = TRUE;
            }
            break;
        case BLUE_MIRROR_PORTAL:
            if (!obj->activated) {
                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 56, 200, 255);
                particle_templates[USE_EFFECT].start_color.a = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;
                
                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);

                state.intended_mirror_factor = 0.f;
                state.intended_mirror_speed_factor = 1.f;
                obj->activated = TRUE;
            }
            break;
        
        case BALL_PORTAL: 
            if (!obj->activated) {
                player->ground_y = maxf(0, ip1_ceilf((obj->y - 150) / 30.f)) * 30;
                player->ceiling_y = player->ground_y + 240;
                set_intended_ceiling(player);

                if (player->gamemode != GAMEMODE_BALL) {
                    player->ball_rotation_speed = -1.f;

                    if (player->gamemode == GAMEMODE_SHIP || player->gamemode == GAMEMODE_UFO) player->vel_y /= 2;
                    
                    player->gamemode = GAMEMODE_BALL;

                    particle_templates[USE_EFFECT].start_scale = 80;
                    particle_templates[USE_EFFECT].end_scale = 0;

                    set_particle_color(USE_EFFECT, 255, 0, 0);
                    particle_templates[USE_EFFECT].start_color.a = 0;
                    particle_templates[USE_EFFECT].end_color.a = 255;

                    spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                }
                obj->activated = TRUE;
            }
            break;

        case BIG_PORTAL:
            if (!obj->activated) {
                player->mini = FALSE;

                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 0, 255, 50);
                particle_templates[USE_EFFECT].start_color.a = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                
                obj->activated = TRUE;
            }
            break;        

        case MINI_PORTAL:
            if (!obj->activated) {
                player->mini = TRUE;

                particle_templates[USE_EFFECT].start_scale = 80;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 255, 31, 255);
                particle_templates[USE_EFFECT].start_color.a = 0;
                particle_templates[USE_EFFECT].end_color.a = 255;
                
                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                
                obj->activated = TRUE;
            }
            break;
        case UFO_PORTAL:
            if (!obj->activated) {
                player->ground_y = maxf(0, ip1_ceilf((obj->y - 180) / 30.f)) * 30;
                player->ceiling_y = player->ground_y + 300;
                set_intended_ceiling(player);

                if (player->gamemode != GAMEMODE_UFO) {
                    player->vel_y /= (state.old_player.gamemode == GAMEMODE_SHIP) ? 4 : 2;
                    player->gamemode = GAMEMODE_UFO;
                    player->ufo_last_y = player->y;

                    if (state.old_player.gamemode == GAMEMODE_SHIP) {
                        player->buffering_state = BUFFER_READY;
                    }

                    particle_templates[USE_EFFECT].start_scale = 80;
                    particle_templates[USE_EFFECT].end_scale = 0;

                    set_particle_color(USE_EFFECT, 255, 127, 0);
                    particle_templates[USE_EFFECT].start_color.a = 0;
                    particle_templates[USE_EFFECT].end_color.a = 255;

                    spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                }
                obj->activated = TRUE;
            }
            break;
        case SECRET_COIN:
            if (!obj->activated) {
                // Coin particle
                spawn_particle(COIN_OBJ, obj->x, obj->y, NULL);

                // Explode particles
                particle_templates[BREAKABLE_BRICK_PARTICLES].start_color.a = 127;
                for (s32 i = 0; i < 10; i++) {
                    spawn_particle(BREAKABLE_BRICK_PARTICLES, obj->x, obj->y, obj);
                }

                // Use particles
                particle_templates[USE_EFFECT].start_scale = 60;
                particle_templates[USE_EFFECT].end_scale = 0;

                set_particle_color(USE_EFFECT, 255, 255, 0);
                particle_templates[USE_EFFECT].start_color.a = 255;
                particle_templates[USE_EFFECT].end_color.a = 0;

                spawn_particle(USE_EFFECT, obj->x, obj->y, obj);
                spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);

                obj->toggled = TRUE;
                obj->activated = TRUE;
            }
            break;
        case SLOW_SPEED_PORTAL:
            if (!obj->activated) {
                if (player->speed != SPEED_SLOW) {
                    set_particle_color(SPEEDUP, 255, 220, 0);
                    particle_templates[SPEEDUP].speed = -20;
                    particle_templates[SPEEDUP].sourcePosVarY = 20;
                    for (int i = 0; i < 20; i++) {
                        spawn_particle(SPEEDUP, state.camera_x + SCREEN_WIDTH_AREA + 20, state.camera_y + (SCREEN_HEIGHT_AREA / 2), NULL);
                    }
                }
                spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
                player->speed = SPEED_SLOW;
                obj->activated = TRUE;
            }
            break;
        case NORMAL_SPEED_PORTAL:
            if (!obj->activated) {
                if (player->speed != SPEED_NORMAL) {
                    set_particle_color(SPEEDUP, 0, 255, 255);
                    particle_templates[SPEEDUP].speed = -60;
                    particle_templates[SPEEDUP].sourcePosVarY = 90;
                    for (int i = 0; i < 20; i++) {
                        spawn_particle(SPEEDUP, state.camera_x + SCREEN_WIDTH_AREA + 90, state.camera_y + (SCREEN_HEIGHT_AREA / 2), NULL);
                    }
                }
                spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
                player->speed = SPEED_NORMAL;
                obj->activated = TRUE;
            }
            break;
        case FAST_SPEED_PORTAL:
            if (!obj->activated) {
                if (player->speed != SPEED_FAST) {
                    set_particle_color(SPEEDUP, 64, 255, 64);
                    particle_templates[SPEEDUP].speed = -100;
                    particle_templates[SPEEDUP].sourcePosVarY = 120;
                    for (int i = 0; i < 20; i++) {
                        spawn_particle(SPEEDUP, state.camera_x + SCREEN_WIDTH_AREA + 120, state.camera_y + (SCREEN_HEIGHT_AREA / 2), NULL);
                    }
                }
                spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
                player->speed = SPEED_FAST;
                obj->activated = TRUE;
            }
            break;
        case FASTER_SPEED_PORTAL:
            if (!obj->activated) {
                if (player->speed != SPEED_FASTER) {
                    set_particle_color(SPEEDUP, 255, 127, 255);
                    particle_templates[SPEEDUP].speed = -160;
                    particle_templates[SPEEDUP].sourcePosVarY = 200;
                    for (int i = 0; i < 20; i++) {
                        spawn_particle(SPEEDUP, state.camera_x + SCREEN_WIDTH_AREA + 200, state.camera_y + (SCREEN_HEIGHT_AREA / 2), NULL);
                    }
                }
                spawn_particle(ORB_HITBOX_EFFECT, obj->x, obj->y, obj);
                player->speed = SPEED_FASTER;
                obj->activated = TRUE;
            }
            break;
    }
    if (!obj->collided) obj->hitbox_counter++; 
}

// Prepare Graphics
GRRLIB_texImg *bg;
GRRLIB_texImg *ground;
GRRLIB_texImg *ground_line;
GRRLIB_texImg *object_images[OBJECT_COUNT][MAX_OBJECT_LAYERS]; 

int current_fading_effect = FADE_NONE;

bool p1_trail = FALSE;

struct TriggerBuffer trigger_buffer[COL_CHANNEL_COUNT];

int find_existing_texture(int curr_object, const unsigned char *texture) {
    for (s32 object = 1; object < curr_object; object++) {
        for (s32 layer = 0; layer < MAX_OBJECT_LAYERS; layer++) {
            const unsigned char *loaded_texture = objects[object].layers[layer].texture;
            if (loaded_texture == texture) {
                return (object * MAX_OBJECT_LAYERS) + layer;
            }
        }
    }
    return -1;
}

void load_spritesheet() {
    // Load Textures 
    ground_line = GRRLIB_LoadTexturePNG(ground_line_png);

    for (s32 object = 1; object < OBJECT_COUNT; object++) {
        for (s32 layer = 0; layer < MAX_OBJECT_LAYERS; layer++) {
            // Skip unused layers
            const unsigned char *texture = objects[object].layers[layer].texture;
            if (!texture) continue;

            printf("Loading texture of object %d layer %d\n", object, layer);
            
            int existing = find_existing_texture(object, texture);
            if (existing < 0) {
                GRRLIB_texImg *image = GRRLIB_LoadTexturePNG((const u8 *) texture);
                if (image == NULL || image->data == NULL) {
                    printf("Couldn't load texture of object %d layer %d\n", object, layer);
                } else {
                    printf("Loaded texture of object %d layer %d\n", object, layer);
                    GRRLIB_SetHandle(image, (image->w/2), (image->h/2));
                    object_images[object][layer] = image;
                }
            } else {
                int object_found = existing / MAX_OBJECT_LAYERS;
                int layer_found = existing % MAX_OBJECT_LAYERS;

                printf("Texture already loaded in object %d layer %d\n", object_found, layer_found);
                object_images[object][layer] = object_images[object_found][layer_found];
            }
        }
    }

    load_icons();
}

void unload_spritesheet() {
    // Free all memory used by textures.
    GRRLIB_FreeTexture(ground_line);

    for (s32 object = 0; object < OBJECT_COUNT; object++) {
        for (s32 layer = 0; layer < objects[object].num_layers; layer++) {
            const unsigned char *texture = objects[object].layers[layer].texture;
            int existing = find_existing_texture(object, texture);
            // Dont double free textures
            if (existing < 0) {
                GRRLIB_FreeTexture(object_images[object][layer]);
            }
        }
    }
    
    unload_icons();
}
void handle_post_draw_object_particles(GameObject *obj, GDObjectLayer *layer) {
    switch (obj->id) {
        case SLOW_SPEED_PORTAL:
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarX = objects[SLOW_SPEED_PORTAL].hitbox.width / 2;
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarY = objects[SLOW_SPEED_PORTAL].hitbox.height / 2;
            set_particle_color(SPEED_PORTAL_AMBIENT, 255, 220, 0);
            if ((frameCount & 0b1111) == 0) spawn_particle(SPEED_PORTAL_AMBIENT, obj->x, obj->y, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            draw_obj_particles(SPEED_PORTAL_AMBIENT, obj);
            break;
        case NORMAL_SPEED_PORTAL:
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarX = objects[NORMAL_SPEED_PORTAL].hitbox.width / 2;
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarY = objects[NORMAL_SPEED_PORTAL].hitbox.height / 2;
            set_particle_color(SPEED_PORTAL_AMBIENT, 0, 255, 255);
            if ((frameCount & 0b1111) == 0) spawn_particle(SPEED_PORTAL_AMBIENT, obj->x, obj->y, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            draw_obj_particles(SPEED_PORTAL_AMBIENT, obj);
            break;
        case FAST_SPEED_PORTAL:
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarX = objects[FAST_SPEED_PORTAL].hitbox.width / 2;
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarY = objects[FAST_SPEED_PORTAL].hitbox.height / 2;
            set_particle_color(SPEED_PORTAL_AMBIENT, 64, 255, 64);
            if ((frameCount & 0b1111) == 0) spawn_particle(SPEED_PORTAL_AMBIENT, obj->x, obj->y, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            draw_obj_particles(SPEED_PORTAL_AMBIENT, obj);
            break;
        case FASTER_SPEED_PORTAL:
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarX = objects[FASTER_SPEED_PORTAL].hitbox.width / 2;
            particle_templates[SPEED_PORTAL_AMBIENT].sourcePosVarY = objects[FASTER_SPEED_PORTAL].hitbox.height / 2;
            set_particle_color(SPEED_PORTAL_AMBIENT, 255, 127, 255);
            if ((frameCount & 0b1111) == 0) spawn_particle(SPEED_PORTAL_AMBIENT, obj->x, obj->y, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            draw_obj_particles(SPEED_PORTAL_AMBIENT, obj);
            break;
    }

    if (GRRLIB_Settings.blend != prev_blending) {
        GRRLIB_SetBlend(prev_blending);
    }
}

void handle_pre_draw_object_particles(GameObject *obj, GDObjectLayer *layer) {
    switch (obj->id) {
        case YELLOW_ORB:
            set_particle_color(ORB_PARTICLES, 255, 255, 0);
            spawn_particle(ORB_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(ORB_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            break;
        
        case YELLOW_PAD:
            particle_templates[PAD_PARTICLES].angle = 180.f - (adjust_angle_y(obj->rotation, obj->flippedV) + 90.f);

            set_particle_color(PAD_PARTICLES, 255, 255, 0);
            spawn_particle(PAD_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(PAD_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            break;

        case PINK_ORB:
            set_particle_color(ORB_PARTICLES, 255, 31, 255);
            spawn_particle(ORB_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(ORB_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            break;

        case PINK_PAD:
            particle_templates[PAD_PARTICLES].angle = 180.f - (adjust_angle_y(obj->rotation, obj->flippedV) + 90.f);

            set_particle_color(PAD_PARTICLES, 255, 31, 255);
            spawn_particle(PAD_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(PAD_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            break;

        case BLUE_ORB:
            set_particle_color(ORB_PARTICLES, 56, 200, 255);
            spawn_particle(ORB_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(ORB_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            break;
        
        case BLUE_PAD:
            particle_templates[PAD_PARTICLES].angle = 180.f - (adjust_angle_y(obj->rotation, obj->flippedV) + 90.f);
            
            set_particle_color(PAD_PARTICLES, 56, 200, 255);
            spawn_particle(PAD_PARTICLES, obj->x, obj->y, obj);
            draw_obj_particles(PAD_PARTICLES, obj);
            draw_obj_particles(USE_EFFECT, obj);
            break;
            
            
        case YELLOW_GRAVITY_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_y(obj->rotation, obj->flippedH);

                set_particle_color(PORTAL_PARTICLES, 255, 255, 0);
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;

        case BLUE_GRAVITY_PORTAL:
        case BLUE_MIRROR_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_y(obj->rotation, obj->flippedH);

                set_particle_color(PORTAL_PARTICLES, 56, 200, 255);
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;
        
        case CUBE_PORTAL:
        case BIG_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_y(obj->rotation, obj->flippedH);

                set_particle_color(PORTAL_PARTICLES, 0, 255, 50);
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;

        case SHIP_PORTAL:
        case MINI_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_y(obj->rotation, obj->flippedH);

                set_particle_color(PORTAL_PARTICLES, 255, 31, 255);
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;

        case ORANGE_MIRROR_PORTAL:
        case UFO_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_y(obj->rotation, obj->flippedH);

                set_particle_color(PORTAL_PARTICLES, 255, 91, 0);
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;
        
        case BALL_PORTAL:
            if (layer->layerNum == 1) {
                particle_templates[PORTAL_PARTICLES].angle = 180.f - adjust_angle_y(obj->rotation, obj->flippedH);

                set_particle_color(PORTAL_PARTICLES, 255, 0, 0);
                particle_templates[PORTAL_PARTICLES].start_color.a = 127;
                particle_templates[PORTAL_PARTICLES].end_color.a = 255;
                spawn_particle(PORTAL_PARTICLES, obj->x, obj->y, obj);
                draw_obj_particles(PORTAL_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
            }
            break;
        case BREAKABLE_BLOCK:
            if (layer->layerNum == 1) {
                particle_templates[BREAKABLE_BRICK_PARTICLES].start_color.a = 255;
                draw_obj_particles(BREAKABLE_BRICK_PARTICLES, obj);
            }
            break;
        case SECRET_COIN:
            if (!obj->activated) {
                spawn_particle(COIN_PARTICLES, obj->x - 2, obj->y, obj);
                spawn_particle(COIN_PARTICLES, obj->x - 2, obj->y, obj);
                spawn_particle(COIN_PARTICLES, obj->x - 2, obj->y, obj);
                draw_obj_particles(COIN_PARTICLES, obj);
            } else {
                draw_obj_particles(BREAKABLE_BRICK_PARTICLES, obj);
                draw_obj_particles(USE_EFFECT, obj);
                draw_obj_particles(ORB_HITBOX_EFFECT, obj);
            }
            break;
    }
}

int get_fade_value(float x, int right_edge) {
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

void get_fade_vars(GameObject *obj, float x, int *fade_x, int *fade_y, float *fade_scale) {
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

int layer_pulses(GameObject *obj, GDObjectLayer *layer) {
    switch (obj->id) {
        case YELLOW_ORB:
        case BLUE_ORB:
        case PINK_ORB:
        case PULSING_CIRCLE:
        case PULSING_CIRCUNFERENCE:
        case PULSING_HEART:
        case PULSING_DIAMOND:
        case PULSING_STAR:
        case PULSING_NOTE:
        case PULSING_SQUARE:
        case PULSING_TRIANGLE:
        case D_ARROW:
        case D_EXMARK:
        case D_QMARK:
        case D_CROSS:
        case PULSING_BIG_CIRCUNFERENCE:
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

float get_object_pulse(float amplitude, GameObject *obj) {
    switch (obj->id) {
        case YELLOW_ORB:
        case BLUE_ORB:
        case PINK_ORB:
            return map_range(amplitude, 0.f, 1.f, 0.3f, 1.2f);
        case PULSING_CIRCLE:
        case PULSING_CIRCUNFERENCE:
        case PULSING_HEART:
        case PULSING_DIAMOND:
        case PULSING_STAR:
        case PULSING_NOTE:
        case PULSING_SQUARE:
        case PULSING_TRIANGLE:
        case ROD_BIG:
        case ROD_MEDIUM:
        case ROD_SMALL:
            return amplitude;
        case D_ARROW:
        case D_EXMARK:
        case D_QMARK:
        case D_CROSS:
        case PULSING_BIG_CIRCUNFERENCE:
            return map_range(amplitude, 0.f, 1.f, 0.8f, 1.2f);
    }
    return amplitude;
}

GRRLIB_texImg *get_randomized_texture(GRRLIB_texImg *image, GameObject *obj, GDObjectLayer *layer) {
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
        case SECRET_COIN:
            int index = (frame_counter & 0b1100000) >> 5;
            return object_images[SECRET_COIN][index];
        case BUSH_GROUND_SPIKE:
            return object_images[BUSH_GROUND_SPIKE][obj->random & 0b11];
    }

    return image;
}

GRRLIB_texImg *get_coin_particle_texture() {
    int index = (frame_counter & 0b110000) >> 4;
    return object_images[SECRET_COIN][index];
}

int get_opacity(GameObject *obj, float x) {
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

float get_fading_obj_fade(GameObject *obj, float x, float right_edge) {
    if (x < FADING_OBJ_PADDING || x > right_edge - FADING_OBJ_PADDING)
        return 1.f;
    else if (x < FADING_OBJ_PADDING + FADING_OBJ_WIDTH)
        return clampf(1.f - ((x - FADING_OBJ_PADDING) / FADING_OBJ_WIDTH), 0.05f, 1.f);
    else if (x > right_edge - FADING_OBJ_WIDTH - FADING_OBJ_PADDING)
        return clampf(1.f - ((right_edge - (x + FADING_OBJ_PADDING)) / FADING_OBJ_WIDTH), 0.05f, 1.f);
    else
        return 0.05f;
}

float get_rotation_speed(GameObject *obj) {
    switch (obj->id) {
        case SAW_BIG: 
        case SAW_MEDIUM:
        case SAW_SMALL:
        case BLADE_BIG:
        case BLADE_MEDIUM:
        case BLADE_SMALL:
        case BLADE_ALT_BIG:
        case BLADE_ALT_MEDIUM:
        case BLADE_ALT_SMALL:
            return 360.f;
        
        case SAW_DECO_BIG:
        case SAW_DECO_MEDIUM:
        case SAW_DECO_SMALL:
        case SAW_DECO_TINY:
        case WHEEL_BIG:
        case WHEEL_MEDIUM:
        case WHEEL_SMALL:
        case SPIKEWHEEL_BIG:
        case SPIKEWHEEL_MEDIUM:
        case SPIKEWHEEL_SMALL:
        case CARTWHEEL_BIG:
        case CARTWHEEL_MEDIUM:
        case CARTWHEEL_SMALL:
        case ROUND_CLOUD_BIG:
        case ROUND_CLOUD_MEDIUM:
        case ROUND_CLOUD_SMALL:
            return 180.f;
    }
    return 0.f;
}

static inline void put_object_layer(GameObject *obj, float x, float y, GDObjectLayer *layer) {
    int obj_id = obj->id;

    int layer_index = layer->layerNum;

    int x_flip_mult = (obj->flippedH ? -1 : 1);
    int y_flip_mult = (obj->flippedV ? -1 : 1);

    struct ObjectLayer *objectLayer = layer->layer;
    float x_offset = objectLayer->x_offset * x_flip_mult;
    float y_offset = objectLayer->y_offset * y_flip_mult;

    GRRLIB_texImg *tex = get_randomized_texture(object_images[obj_id][layer_index], obj, layer);

    int width = tex->w;
    int height = tex->h;

    int col_channel = objectLayer->col_channel;

    int blending;
    if (channels[col_channel].blending) {
        blending = GRRLIB_BLEND_ADD;
    } else {
        blending = GRRLIB_BLEND_ALPHA;
    }

    int opacity = get_opacity(obj, x);
    int unmodified_opacity = opacity;
    
    if (objects[obj_id].fades) {
        opacity *= get_fading_obj_fade(obj, x, screenWidth);
    }

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
        obj->ampl_scaling = ease_out(obj->ampl_scaling, get_object_pulse(amplitude, obj), 0.2f);
        fade_scale *= obj->ampl_scaling;
    }

    float rotation = adjust_angle(obj->rotation, 0, state.mirror_mult < 0);

    switch(obj_id) {
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
        if (unmodified_opacity < 255) {
            if (x > screenWidth / 2) {
                x = screenWidth - FADE_WIDTH;
            } else {
                x = FADE_WIDTH;
            }
        }
    }
    
    if (prev_tex != tex) {
        prev_tex = tex;
        set_texture(tex);
    }
    

    if (blending != prev_blending) {
        GRRLIB_SetBlend(blending);
        prev_blending = blending;
    }

    custom_drawImg(
        /* X        */ get_mirror_x(x, state.mirror_factor) + 6 - (width/2) + x_off_rot + fade_x,
        /* Y        */ y + 6 - (height/2) + y_off_rot + fade_y,
        /* Texture  */ tex, 
        /* Rotation */ rotation, 
        /* Scale X  */ 0.73333333333333333333333333333333 * x_flip_mult * fade_scale * state.mirror_mult, 
        /* Scale Y  */ 0.73333333333333333333333333333333 * y_flip_mult * fade_scale, 
        /* Color    */ color
    );
}


void draw_background_image(f32 x, f32 y, bool vflip) {
    for (s32 i = 0; i < BG_DIMENSIONS; i++) {
        float calc_x = i*BG_CHUNK;
        for (s32 j = 0; j < BG_DIMENSIONS; j++) {
            float calc_y = j*BG_CHUNK;
            
            GRRLIB_SetHandle(bg, 512, 512);
            custom_drawPart(
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
    GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
    GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);
    set_texture(bg);

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
    
    GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
    GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);

    if (calc_x < screenWidth + 20) {
        for (s32 j = 0; j < objects[CHECKER_EDGE].num_layers; j++) {
            GRRLIB_texImg *image = object_images[CHECKER_EDGE][j];
            int width = image->w;
            int height = image->h;
            set_texture(image);

            for (float i = -BLOCK_SIZE_PX; i < screenHeight + BLOCK_SIZE_PX * 2; i += BLOCK_SIZE_PX) {
                custom_drawImg(
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
    
    GX_SetTevOp  (GX_TEVSTAGE0, GX_PASSCLR);
    GX_SetVtxDesc(GX_VA_TEX0,   GX_NONE);
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

void handle_special_fading(GameObject *obj, float calc_x, float calc_y) {
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

int compare_by_layer_index(const void *a, const void *b) {
    GDLayerSortable *la = *(GDLayerSortable **)a;
    GDLayerSortable *lb = *(GDLayerSortable **)b;

    int layerA = la->layer->layerNum;
    int layerB = lb->layer->layerNum;

    if (layerA != layerB) {
        return layerA - layerB;
    } 

    return la->originalIndex - lb->originalIndex;
}

void draw_all_object_layers() {
    u64 t0 = gettime();
    if (GRRLIB_Settings.antialias == false) {
        GX_SetCopyFilter(GX_FALSE, rmode->sample_pattern, GX_FALSE, rmode->vfilter);
    } else {
        GX_SetCopyFilter(rmode->aa, rmode->sample_pattern, GX_TRUE, rmode->vfilter);
    }
    
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
                GameObject *obj = sec->layers[i]->layer->obj;
                
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
    int i = 0;
    while (i < visible_count) {
        int obj_id = visible_layers[i]->layer->obj->id;
        int j = i + 1;

        // Find run of same object
        while (j < visible_count &&
            visible_layers[j]->layer->obj->id == obj_id) {
            j++;
        }

        // Reorder [i, j) to group layers by increasing layer index
        if (j - i > 1) {
            qsort(&visible_layers[i], j - i, sizeof(GDLayerSortable*), compare_by_layer_index);
        }

        i = j;
    }
    
    u64 t1 = gettime();
    layer_sorting = ticks_to_microsecs(t1 - t0) / 1000.f;
    
    draw_particles(GLITTER_EFFECT);
    layersDrawn = visible_count;

    prev_blending = -1;

    // Draw in sorted order
    for (int i = 0; i < visible_count; i++) {
        GDObjectLayer *layer = visible_layers[i]->layer;
        GameObject *obj = layer->obj;

        int obj_id = obj->id;

        if (obj_id == PLAYER_OBJECT) {
            u64 t2 = gettime();
            draw_particles(DEATH_CIRCLE);
            draw_particles(DEATH_PARTICLES);
            draw_particles(CUBE_DRAG);
            draw_particles(SHIP_TRAIL);
            draw_particles(HOLDING_SHIP_TRAIL);
            draw_particles(UFO_JUMP);
            draw_particles(UFO_TRAIL);
            if (death_timer <= 0) {
                draw_player();
            }
            draw_particles(SHIP_DRAG);
            draw_particles(COIN_OBJ);
            u64 t3 = gettime();
            player_draw_time = ticks_to_microsecs(t3 - t2) / 1000.f;

            // Restore variables
            set_texture(prev_tex);
            GRRLIB_SetBlend(prev_blending);
        } else if (obj_id < OBJECT_COUNT) {
            u64 t0 = gettime();
            float calc_x = ((obj->x - state.camera_x) * SCALE);
            float calc_y = screenHeight - ((obj->y - state.camera_y) * SCALE);  

            int fade_val = get_fade_value(calc_x, screenWidth);
            bool fade_edge = (fade_val == 255 || fade_val == 0);
            bool is_layer0 = (layer->layerNum == 0);

            if (is_layer0 && fade_edge) handle_special_fading(obj, calc_x, calc_y);
            
            if (is_layer0 && objects[obj_id].is_saw) {
                obj->rotation += ((obj->random & 1) ? -get_rotation_speed(obj) : get_rotation_speed(obj)) * dt;
            }

            handle_pre_draw_object_particles(obj, layer); 
            u64 t1 = gettime();
            obj_particles_time += t1 - t0;

            t0 = gettime();
            if (!obj->toggled) put_object_layer(obj, calc_x, calc_y, layer);
            t1 = gettime();
            draw_time += t1 - t0;
            
            t0 = gettime();
            handle_post_draw_object_particles(obj, layer); 
            t1 = gettime();
            obj_particles_time += t1 - t0;
        }
    }

    draw_particles(SPEEDUP);

    draw_time = ticks_to_microsecs(draw_time) / 1000.f;
    obj_particles_time = ticks_to_microsecs(obj_particles_time) / 1000.f;
    
    prev_tex = NULL;
    prev_blending = GRRLIB_BLEND_ALPHA;
    GRRLIB_SetBlend(prev_blending);
    
    GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);
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

void handle_copy_channels() {
    for (int chan = 0; chan < COL_CHANNEL_COUNT; chan++) {
        int copy_color_id = channels[chan].copy_color_id;
        if (copy_color_id > 0) {
            channels[chan].color = channels[copy_color_id].color;
        }
    }
}

void upload_to_buffer(GameObject *obj, int channel) {
    if (channel == 0) channel = 1;
    struct TriggerBuffer *buffer = &trigger_buffer[channel];
    buffer->active = TRUE;
    buffer->old_color = channels[channel].color;
    if (obj->p1_color) {
        buffer->new_color.r = p1.r;
        buffer->new_color.g = p1.g;
        buffer->new_color.b = p1.b;
    } else if (obj->p2_color) {
        buffer->new_color.r = p2.r;
        buffer->new_color.g = p2.g;
        buffer->new_color.b = p2.b;
    } else {
        buffer->new_color.r = obj->trig_colorR;
        buffer->new_color.g = obj->trig_colorG;
        buffer->new_color.b = obj->trig_colorB;
    }
    if (channel < BG) {
        channels[channel].blending = obj->blending;
    }
    buffer->seconds = obj->trig_duration;
    buffer->time_run = 0;
}

void run_trigger(GameObject *obj) {
    switch (obj->id) {
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
            upload_to_buffer(obj, BG);
            if (!obj->tintGround) break;
        
        case GROUND_TRIGGER:
            upload_to_buffer(obj, GROUND);
            break;
                    
        case LINE_TRIGGER:
        case 915: // gd converts 1.4 line trigger to 2.0 one for some reason
            upload_to_buffer(obj, LINE);
            break;
        
        case OBJ_TRIGGER:
            upload_to_buffer(obj, OBJ);
            break;
        
        case OBJ_2_TRIGGER:
            upload_to_buffer(obj, 1);
            break;

        case ENABLE_TRAIL:
            p1_trail = TRUE;
            break;
        
        case DISABLE_TRAIL:
            p1_trail = FALSE;
            break;

        case 899: // 2.0 color trigger
            upload_to_buffer(obj, obj->target_color_id);
            break;
    }
    obj->activated = TRUE;
}

void handle_triggers(GameObject *obj) {
    int obj_id = obj->id;
    Player *player = &state.player;
    
    if ((objects[obj_id].is_trigger || obj->id > OBJECT_COUNT) && !obj->activated) {
        if (obj->touchTriggered) {
            if (intersect(
                player->x, player->y, player->width, player->height, 0, 
                obj->x, obj->y, 30, 30, obj->rotation
            )) {
                run_trigger(obj);
            }
        } else {
            if (obj->x < state.player.x && obj->x > state.old_player.x) {
                run_trigger(obj);
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
                GameObject *obj = sec->objects[i];
                handle_triggers(obj);
            }
        }
    }
    calculate_lbg();
    handle_col_triggers();
    handle_copy_channels();
}