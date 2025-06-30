#include "player.h"
#include "collision.h"
#include "blocks.h"
#include "level_loading.h"
#include "main.h"
#include <wiiuse/wpad.h>
#include <math.h>
#include "math.h"
#include "object_includes.h"
#include <unistd.h>
#include <stdio.h>


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
    gameplay_state->camera_intended_y = mid_point - (SCREEN_HEIGHT_AREA / 2);
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
                player->y = grav(player, obj_gravTop(player, obj)) + grav(player, player->height / 2);
            } else {
                if (player->gamemode == GAMEMODE_SHIP) {
                    if (gravTop(player) - obj_gravBottom(player, obj) <= clip && player->vel_y > 0) {
                        player->vel_y = 0;
                        player->on_ground = TRUE;
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
    Player *player = &gameplay_state->player;

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

    player->rotation += 415.3848 * dt * mult;

    if (player->on_ground) {
        player->rotation = round(player->rotation / 90.0f) * 90.0f;
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
    Player *player = &gameplay_state->player;

    gameplay_state->camera_x += 311.580093712804 * dt;

    float upper = 240.f;
    float lower = 120.f;

    if (player->upside_down) {
        upper = 210.f;
        lower = 90.f;
    }

    if (player->gamemode == GAMEMODE_CUBE) {
        if (grav(player, player->vel_y) > 0 && player->y > gameplay_state->camera_y + upper) {
            gameplay_state->camera_y_lerp += player_get_vel(player, player->vel_y) * dt;
        }

        if (grav(player, player->vel_y) < 0 && player->y < gameplay_state->camera_y + lower) {
            gameplay_state->camera_y_lerp += player_get_vel(player, player->vel_y) * dt;
        }

        if (gameplay_state->camera_y_lerp < -90.f) gameplay_state->camera_y_lerp = -90.f;

        gameplay_state->camera_y = approachf(gameplay_state->camera_y, gameplay_state->camera_y_lerp, 0.2f, 0.05f);
    } else {
        gameplay_state->camera_y = approachf(gameplay_state->camera_y, gameplay_state->camera_intended_y, 0.1f, 0.025f);
        gameplay_state->camera_y_lerp = gameplay_state->camera_y;
    }

}

void run_player() {
    Player *player = &gameplay_state->player;
    switch (player->gamemode) {
        case GAMEMODE_CUBE:
            cube_gamemode(player);
            break;
        case GAMEMODE_SHIP:
            ship_gamemode(player);
            break;
        
    }
    
    player->vel_y += player->gravity * dt;
    player->y += player_get_vel(player, player->vel_y) * dt;
    player->x += player->vel_x * dt;
    
    player->on_ground = FALSE;
    
    // Ground
    if (getBottom(player) < player->ground_y) {
        player->vel_y = 0;
        player->y = player->ground_y + (player->height / 2);
        player->on_ground = TRUE;
    } 

    // Ceiling
    if (getTop(player) > player->ceiling_y) {
        player->vel_y = 0;
        player->y = player->ceiling_y - (player->height / 2);
        player->on_ground = TRUE;
    } 
}

void handle_player() {
    for (int i = 0; i < 4; i++) {
        run_player();
        run_camera();
        collide_with_objects();
    }
}

void init_variables() {
    gameplay_state->camera_x = -90;
    gameplay_state->camera_x_lerp = -90;
    gameplay_state->camera_y = -90;
    gameplay_state->camera_y_lerp = -90;

    current_fading_effect = FADE_NONE;
    
    memset(&gameplay_state->player, 0, sizeof(Player));

    Player *player = &gameplay_state->player;
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
    player->dead = FALSE;
}

void handle_death() {
    usleep(1000000);
    init_variables();
}

void draw_player() {
    Player *player = &render_state->player;

    float calc_x = ((getLeft(player) - render_state->camera_x) * scale);
    float calc_y = screenHeight - ((getTop(player) - render_state->camera_y) * scale);

    GRRLIB_texImg *image = object_images[BASIC_BLOCK][1];

    GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
    GRRLIB_DrawImg(
        calc_x, calc_y - 2,
        image,
        player->rotation,
        0.73333333333333333333333333333333,
        0.73333333333333333333333333333333,
        RGBA(255, 255, 255, 255)
    );
}