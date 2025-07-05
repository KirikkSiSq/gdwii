#include "player.h"
#include "collision.h"
#include "objects.h"
#include "level_loading.h"
#include "main.h"
#include <wiiuse/wpad.h>
#include <math.h>
#include "math.h"
#include "object_includes.h"
#include <unistd.h>
#include <stdio.h>
#include "icons_includes.h"

GRRLIB_texImg *icon_l1;
GRRLIB_texImg *icon_l2;
GRRLIB_texImg *ship_l1;
GRRLIB_texImg *ship_l2;

Color p1;
Color p2;

inline float getTop(Player *player)  { return player->y + player->height / 2; }
inline float getBottom(Player *player)  { return player->y - player->height / 2; }
inline float getRight(Player *player)  { return player->x + player->width / 2; }
inline float getLeft(Player *player)  { return player->x - player->width / 2; }
inline float gravBottom(Player *player) { return player->upside_down ? -getTop(player) : getBottom(player); }
inline float gravTop(Player *player) { return player->upside_down ? -getBottom(player) : getTop(player); }
inline float grav(Player *player, float val) { return player->upside_down ? -val : val; }

inline float obj_getTop(GDObjectTyped *object)  { return object->y + (objects[object->id].hitbox.height / 2); }
inline float obj_getBottom(GDObjectTyped *object)  { return object->y - (objects[object->id].hitbox.height / 2); }
inline float obj_getRight(GDObjectTyped *object)  { return object->x + objects[object->id].hitbox.width / 2; }
inline float obj_getLeft(GDObjectTyped *object)  { return object->x - objects[object->id].hitbox.width / 2; }
inline float obj_gravBottom(Player *player, GDObjectTyped *object) { return player->upside_down ? -obj_getTop(object) : obj_getBottom(object); }
inline float obj_gravTop(Player *player, GDObjectTyped *object) { return player->upside_down ? -obj_getBottom(object) : obj_getTop(object); }


void set_intended_ceiling(Player *player) {
    float mid_point = (player->ground_y + player->ceiling_y) / 2;
    state.camera_intended_y = mid_point - (SCREEN_HEIGHT_AREA / 2);
}

void handle_special_hitbox(Player *player, GDObjectTyped *obj, ObjectHitbox *hitbox) {
    switch (obj->id) {
        case YELLOW_PAD:
            player->vel_y = 864;
            player->on_ground = FALSE;
            break;
        
        case YELLOW_ORB:
            if ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) && player->buffering_state == BUFFER_READY) {    
                player->vel_y = 603.72;
                player->on_ground = FALSE;
                player->buffering_state = BUFFER_END;
            }
            break;

        case CUBE_PORTAL: 
            if (player->gamemode != GAMEMODE_CUBE) {
                player->ground_y = 0;
                player->ceiling_y = 999999;

                player->vel_y /= 2;
                player->gamemode = GAMEMODE_CUBE;
            }
            break;
            
        case SHIP_PORTAL: 
            if (player->gamemode != GAMEMODE_SHIP) {
                player->ground_y = maxf(0, ceilf((obj->y - 180) / 30.f)) * 30;
                player->ceiling_y = player->ground_y + 300;
                
                set_intended_ceiling(player);

                player->vel_y /= 2;
                player->gamemode = GAMEMODE_SHIP;
            }
            break;
        
        case BLUE_GRAVITY_PORTAL:
            if (player->upside_down) {
                player->vel_y /= -2;
                player->upside_down = FALSE;
            }
            break;
        case YELLOW_GRAVITY_PORTAL:
            if (!player->upside_down) {
                player->vel_y /= -2;
                player->upside_down = TRUE;
            }
            break;
    }
}

void handle_collision(Player *player, GDObjectTyped *obj, ObjectHitbox *hitbox) {
    int clip = 10;
    switch (hitbox->type) {
        case HITBOX_SOLID: 
            if (intersect(
                player->x, player->y, 9, 9, 0, 
                obj->x, obj->y, hitbox->width, hitbox->height, obj->rotation
            )) {
                player->dead = TRUE;
            } else if (obj_gravTop(player, obj) - gravBottom(player) <= clip && player->vel_y <= 0) {
                player->vel_y = 0;
                player->on_ground = TRUE;
                player->time_since_ground = 0;
                player->y = grav(player, obj_gravTop(player, obj)) + grav(player, player->height / 2);
            } else {
                if (player->gamemode == GAMEMODE_SHIP) {
                    if (gravTop(player) - obj_gravBottom(player, obj) <= clip && player->vel_y > 0) {
                        player->vel_y = 0;
                        player->on_ceiling = TRUE;
                        player->time_since_ground = 0;
                        player->y = grav(player, obj_gravBottom(player, obj)) - grav(player, player->height / 2);
                    }
                }
            }
            break;
        case HITBOX_SPIKE:
            player->dead = TRUE;
            break;
        case HITBOX_SPECIAL:
            handle_special_hitbox(player, obj, hitbox);
            break;
    }
}

float player_get_vel(Player *player, float vel) {
    return vel * (player->upside_down ? -1 : 1);
}

void collide_with_objects() {
    Player *player = &state.player;

    for (int i = 0; i < objectsArrayList->count; i++) {
        GDObjectTyped *obj = objectsArrayList->objects[i]; 
        ObjectHitbox *hitbox = (ObjectHitbox *) &objects[obj->id].hitbox;

        if (intersect(
            player->x, player->y, player->width, player->height, 0, 
            obj->x, obj->y, hitbox->width, hitbox->height, obj->rotation
        )) {
            handle_collision(player, obj, hitbox);
        }
    }
}

void cube_gamemode(Player *player) {
    int mult = (player->upside_down ? -1 : 1);

    player->gravity = -2794.1082;
    
    if (player->vel_y < -810) player->vel_y = -810;

    player->rotation += 415.3848 * STEPS_DT * mult;

    if (player->on_ground) {
        player->rotation = round(player->rotation / 90.0f) * 90.0f;
    }

    if ((player->time_since_ground < 0.05f)&& (frame_counter & 0b11) == 0) {
        particle_templates[CUBE_DRAG].speed = 75 * mult;
        particle_templates[CUBE_DRAG].gravity_y = (player->upside_down ? 100 : -300);
        spawn_particle(CUBE_DRAG, player->x, (player->upside_down ? getTop(player) : getBottom(player)), NULL);
    }

    if ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A)) {
        if (player->buffering_state == BUFFER_NONE) {
            player->buffering_state = BUFFER_READY;
        }
    } else {
        player->buffering_state = BUFFER_NONE;
    }

    if (player->on_ground && WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) {
        player->vel_y = 603.72;
        player->on_ground = FALSE;
        player->buffering_state = BUFFER_END;

        if (!(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A)) {
            player->vel_y -= player->gravity * STEPS_DT;
            printf("Second jump\n");
        } else {
            printf("First jump\n");
        }
    }
}

void ship_particles(Player *player) {
    int mult = (player->upside_down ? -1 : 1);
    if ((frame_counter & 0b11) == 0) {
        // Particle trail
        spawn_particle(SHIP_TRAIL, player->x - 4, (player->upside_down ? getTop(player) - 6 : getBottom(player) + 4), NULL);
        
        // Holding particles
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) {
            spawn_particle(HOLDING_SHIP_TRAIL, player->x - 4, (player->upside_down ? getTop(player) - 6 : getBottom(player) + 4), NULL);
        }

        // Ground drag effectr
        if (player->on_ground) {
            particle_templates[SHIP_DRAG].speed = 95 * mult;
            particle_templates[SHIP_DRAG].gravity_y = (player->upside_down ? 100 : -300);
            spawn_particle(SHIP_DRAG, player->x, (player->upside_down ? getTop(player) : getBottom(player)), NULL);
        }
    }
}

void ship_gamemode(Player *player) {
    if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) {
        if (player->vel_y <= grav(player, 103.485492))
            player->gravity = player->mini ? 1643.5872 : 1397.0491;
        else
            player->gravity = player->mini ? 1314.86976 : 1117.64328;
    } else {
        if (player->vel_y >= grav(player, 103.485492))
            player->gravity = player->mini ? -1577.85408 : -1341.1719;
        else
            player->gravity = player->mini ? -1051.8984 : -894.11464;
    }

    ship_particles(player);

    player->rotation = atan2f(player->vel_y, player->vel_x) * (180.0f / M_PI) * (player->upside_down ? 1 : -1);
    
    float min = player->mini ? -406.566 : -345.6;
    float max = player->mini ? 508.248 : 432.0;

    if (player->vel_y < min) {
        player->vel_y = min;
    } else if (player->vel_y > max) {
        player->vel_y = max;
    }
}

void run_camera() {
    Player *player = &state.player;

    state.camera_x += 311.580093712804 * STEPS_DT;

    float upper = 240.f;
    float lower = 120.f;

    if (player->upside_down) {
        upper = 210.f;
        lower = 90.f;
    }

    if (player->gamemode == GAMEMODE_CUBE) {
        if (grav(player, player->vel_y) > 0 && player->y > state.camera_y + upper) {
            state.camera_y_lerp += player_get_vel(player, player->vel_y) * STEPS_DT;
        }

        if (grav(player, player->vel_y) < 0 && player->y < state.camera_y + lower) {
            state.camera_y_lerp += player_get_vel(player, player->vel_y) * STEPS_DT;
        }

        if (state.camera_y_lerp < -90.f) state.camera_y_lerp = -90.f;

        state.camera_y = approachf(state.camera_y, state.camera_y_lerp, 0.2f, 0.05f);
    } else {
        state.camera_y = approachf(state.camera_y, state.camera_intended_y, 0.1f, 0.025f);
        state.camera_y_lerp = state.camera_y;
    }

}

void run_player() {
    Player *player = &state.player;
    switch (player->gamemode) {
        case GAMEMODE_CUBE:
            cube_gamemode(player);
            break;
        case GAMEMODE_SHIP:
            ship_gamemode(player);
            break;
        
    }
    
    player->time_since_ground += STEPS_DT;
    
    player->vel_y += player->gravity * STEPS_DT;
    player->y += player_get_vel(player, player->vel_y) * STEPS_DT;
    player->x += player->vel_x * STEPS_DT;
    
    player->on_ground = FALSE;
    player->on_ceiling = FALSE;
    
    // Ground
    if (getBottom(player) < player->ground_y) {
        player->vel_y = 0;
        player->y = player->ground_y + (player->height / 2);
        
        if (player->upside_down) {
            player->on_ceiling = TRUE;
        } else {
            player->on_ground = TRUE;           
        }
        player->time_since_ground = 0;
    } 

    // Ceiling
    if (getTop(player) > player->ceiling_y) {
        player->vel_y = 0;
        player->y = player->ceiling_y - (player->height / 2);
        if (player->upside_down) {
            player->on_ground = TRUE;
        } else {
            player->on_ceiling = TRUE;           
        }
        player->time_since_ground = 0;  
    } 
    
}

void handle_player() {
    run_player();
    run_camera();
    collide_with_objects();
}

void init_variables() {
    state.camera_x = -120;
    state.camera_x_lerp = -120;
    state.camera_y = -90;
    state.camera_y_lerp = -90;

    current_fading_effect = FADE_NONE;
    
    memset(&state.player, 0, sizeof(Player));

    Player *player = &state.player;
    player->width = 30;
    player->height = 30;
    player->x = 0;
    player->y = player->height / 2;
    player->vel_x = 311.580093712804;
    player->vel_y = 0;
    player->ground_y = 0;
    player->ceiling_y = 999999;
    player->gamemode = GAMEMODE_CUBE;
    player->on_ground = TRUE;
    player->on_ceiling = FALSE;
    player->upside_down = FALSE;
    player->dead = FALSE;

    particle_templates[CUBE_DRAG].start_color.r = p1.r;
    particle_templates[CUBE_DRAG].start_color.g = p1.g;
    particle_templates[CUBE_DRAG].start_color.b = p1.b;
    
    particle_templates[CUBE_DRAG].end_color.r = p1.r;
    particle_templates[CUBE_DRAG].end_color.g = p1.g;
    particle_templates[CUBE_DRAG].end_color.b = p1.b;
}

void handle_death() {
    for (s32 i = 0; i < 60; i++) {
        draw_game();
    }
    init_variables();
    reload_level();
}

void load_icons() {
    icon_l1 = GRRLIB_LoadTexturePNG(player_01_001_png);
    icon_l2 = GRRLIB_LoadTexturePNG(player_01_2_001_png);
    ship_l1 = GRRLIB_LoadTexturePNG(ship_01_001_png);
    ship_l2 = GRRLIB_LoadTexturePNG(ship_01_2_001_png);

    p1.r = 0;
    p1.g = 255;
    p1.b = 0;

    p2.r = 0;
    p2.g = 255;
    p2.b = 255;
}

void unload_icons() {
    GRRLIB_FreeTexture(icon_l1);
    GRRLIB_FreeTexture(icon_l2);
}

void draw_ship(Player *player, float calc_x, float calc_y) {
    GRRLIB_SetHandle(icon_l1, 30, 30);  // 60x60
    GRRLIB_SetHandle(icon_l2, 30, 30);
    GRRLIB_SetHandle(ship_l1, 38, 24);  // 76x48
    GRRLIB_SetHandle(ship_l2, 38, 24);

    int mult = (player->upside_down ? -1 : 1);

    float x;
    float y;

    #define CUBE_DIVISOR 1.8

    rotate_point_around_center(
        calc_x, calc_y,
        7, (player->upside_down) ? 5 : -9,
        30, 30,
        60, 60,
        player->rotation,
        &x, &y
    );

    // Top (icon)
    GRRLIB_DrawImg(
        x,
        y,
        icon_l1,
        player->rotation,
        0.733f / CUBE_DIVISOR, 0.733f / CUBE_DIVISOR,
        RGBA(p1.r, p1.g, p1.b, 255)
    );

    GRRLIB_DrawImg(
        x,
        y,
        icon_l2,
        player->rotation,
        0.733f / CUBE_DIVISOR, 0.733f / CUBE_DIVISOR,
        RGBA(p2.r, p2.g, p2.b, 255)
    );

    rotate_point_around_center(
        calc_x, calc_y,
        0, (player->upside_down) ? -4 : 12,
        30, 30,
        76, 48,
        player->rotation,
        &x, &y
    );

    // Bottom (ship)
    GRRLIB_DrawImg(
        x,
        y,
        ship_l1,
        player->rotation,
        0.733f, 0.733f * mult,
        RGBA(p1.r, p1.g, p1.b, 255)
    );

    GRRLIB_DrawImg(
        x,
        y,
        ship_l2,
        player->rotation,
        0.733f, 0.733f * mult,
        RGBA(p2.r, p2.g, p2.b, 255)
    );
}

void draw_player() {
    Player *player = &state.player;

    float calc_x = ((getLeft(player) - state.camera_x) * SCALE);
    float calc_y = screenHeight - ((getTop(player) - state.camera_y) * SCALE);

    GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);

    switch (player->gamemode) {
        case GAMEMODE_CUBE:
            GRRLIB_SetHandle(icon_l1, 30, 30);
            GRRLIB_SetHandle(icon_l2, 30, 30);
            GRRLIB_DrawImg(
                calc_x, calc_y - 2,
                icon_l1,
                player->rotation,
                0.73333333333333333333333333333333,
                0.73333333333333333333333333333333,
                RGBA(p1.r, p1.g, p1.b, 255)
            );

            GRRLIB_DrawImg(
                calc_x, calc_y - 2,
                icon_l2,
                player->rotation,
                0.73333333333333333333333333333333,
                0.73333333333333333333333333333333,
                RGBA(p2.r, p2.g, p2.b, 255)
            );
            break;
        case GAMEMODE_SHIP:
            draw_ship(player, calc_x - 8, calc_y);
            break;
    }

}