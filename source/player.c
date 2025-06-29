#include "player.h"
#include "collision.h"
#include "blocks.h"
#include "level_loading.h"
#include "main.h"
#include <wiiuse/wpad.h>
#include <math.h>
#include "object_includes.h"

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
            if (obj_gravTop(player, obj) - gravBottom(player) <= clip && player->vel_y <= 0) {
                player->vel_y = 0;
                player->on_ground = TRUE;
                player->y = grav(player, obj_gravTop(player, obj)) + grav(player, player->height / 2);
            }
            break;
        case HITBOX_SPIKE:
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

    player->gravity = 2794.1082;
    
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

void run_player() {
    Player *player = &gameplay_state->player;
    switch (player->gamemode) {
        case GAMEMODE_CUBE:
            cube_gamemode(player);
            break;
        
    }
    
    player->vel_y -= player->gravity * dt;
    player->y += player_get_vel(player, player->vel_y) * dt;
    player->x += 311.580093712804 * dt;
    gameplay_state->camera_x += 311.580093712804 * dt;

    if (player->y - player->height / 2 < 0) {
        player->vel_y = 0;
        player->y = player->height / 2;
        player->on_ground = TRUE;
    } else {
        player->on_ground = FALSE;
    }
}

void handle_player() {
    for (int i = 0; i < 4; i++) {
        run_player();
        collide_with_objects();
    }
}

void init_player() {
    gameplay_state->camera_x = -90;
    gameplay_state->camera_y = -60;

    Player *player = &gameplay_state->player;
    player->width = 30;
    player->height = 30;
    player->x = 0;
    player->y = player->height / 2;
    player->on_ground = TRUE;
}

void draw_player() {
    Player *player = &render_state->player;

    float calc_x = ((getLeft(player) - render_state->camera_x) * scale);
    float calc_y = screenHeight - ((getTop(player) - render_state->camera_y) * scale);

    GRRLIB_texImg *image = object_images[0][1];

    GRRLIB_DrawImg(
        calc_x, calc_y - 2,
        image,
        player->rotation,
        0.73333333333333333333333333333333,
        0.73333333333333333333333333333333,
        RGBA(255, 255, 255, 255)
    );
}