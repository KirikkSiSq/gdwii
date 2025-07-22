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
#include "game.h"
#include "custom_mp3player.h"
#include "trail.h"

GRRLIB_texImg *icon_l1;
GRRLIB_texImg *icon_l2;
GRRLIB_texImg *ship_l1;
GRRLIB_texImg *ship_l2;
GRRLIB_texImg *ball_l1;
GRRLIB_texImg *ball_l2;

GRRLIB_texImg *trail_tex;

MotionTrail trail;

Color p1;
Color p2;

inline static float getTop(Player *player)  { return player->y + player->height / 2; }
inline static float getBottom(Player *player)  { return player->y - player->height / 2; }
inline static float getRight(Player *player)  { return player->x + player->width / 2; }
inline static float getLeft(Player *player)  { return player->x - player->width / 2; }
inline static float gravBottom(Player *player) { return player->upside_down ? -getTop(player) : getBottom(player); }
inline static float gravTop(Player *player) { return player->upside_down ? -getBottom(player) : getTop(player); }
inline static float grav(Player *player, float val) { return player->upside_down ? -val : val; }

inline static float obj_getTop(GDObjectTyped *object)  { 
    if (positive_fmod(object->rotation, 180.f) >= 90.f) {
        return object->y + (objects[object->id].hitbox.width / 2); 
    } else {
        return object->y + (objects[object->id].hitbox.height / 2); 
    }
}
inline static float obj_getBottom(GDObjectTyped *object)  { 
    if (positive_fmod(object->rotation, 180.f) >= 90.f) {
        return object->y - (objects[object->id].hitbox.width / 2); 
    } else {
        return object->y - (objects[object->id].hitbox.height / 2);
    }
}
inline static float obj_getRight(GDObjectTyped *object)  { 
    if (positive_fmod(object->rotation, 180.f) >= 90.f) {
        return object->x + objects[object->id].hitbox.height / 2;
    } else {
        return object->x + objects[object->id].hitbox.width / 2; 
    }
}
inline static float obj_getLeft(GDObjectTyped *object)  { 
    if (positive_fmod(object->rotation, 180.f) >= 90.f) {
        return object->x - objects[object->id].hitbox.height / 2; 
    } else {
        return object->x - objects[object->id].hitbox.width / 2; 
    }
}
inline static float obj_gravBottom(Player *player, GDObjectTyped *object) { return player->upside_down ? -obj_getTop(object) : obj_getBottom(object); }
inline static float obj_gravTop(Player *player, GDObjectTyped *object) { return player->upside_down ? -obj_getBottom(object) : obj_getTop(object); }

void set_p_velocity(Player *player, float vel) {
    player->vel_y = vel * ((player->mini) ? 0.8 : 1);
}

void handle_collision(Player *player, GDObjectTyped *obj, ObjectHitbox *hitbox) {
    int clip = (player->gamemode == GAMEMODE_SHIP ? 7 : 10);
    switch (hitbox->type) {
        case HITBOX_SOLID: 
            bool padHitBefore = (!state.old_player.on_ground && player->gravity_change && ((state.old_player.vel_y <= 0 && player->vel_y > 0) || (state.old_player.vel_y >= 0 && player->vel_y < 0)));
            
            if (obj_gravTop(player, obj) - gravBottom(player) > clip && intersect(
                player->x, player->y, 9, 9, 0, 
                obj->x, obj->y, hitbox->width, hitbox->height, obj->rotation
            )) {
                player->dead = TRUE;
            } else if (obj_gravTop(player, obj) - gravBottom(player) <= clip && (player->vel_y <= 0)) {
                player->y = grav(player, obj_gravTop(player, obj)) + grav(player, player->height / 2);
                player->vel_y = 0;
                player->on_ground = TRUE;
                player->time_since_ground = 0;
            } else {
                if (player->gamemode != GAMEMODE_CUBE || padHitBefore) {
                    if ((gravTop(player) - obj_gravBottom(player, obj) <= clip && player->vel_y > 0) || padHitBefore) {
                        player->vel_y = 0;
                        if (!padHitBefore) player->on_ceiling = TRUE;
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

void collide_with_obj(GDObjectTyped *obj) {
    Player *player = &state.player;
    ObjectHitbox *hitbox = (ObjectHitbox *) &objects[obj->id].hitbox;

    if (hitbox->type != HITBOX_NONE && !obj->activated && obj->id < OBJECT_COUNT) {
        number_of_collisions_checks++;
        if (hitbox->is_circular) {
            if (intersect_rect_circle(
                player->x, player->y, player->width, player->height, player->rotation, 
                obj->x, obj->y, hitbox->radius
            )) {
                handle_collision(player, obj, hitbox);
                obj->collided = TRUE;
                number_of_collisions++;
            } else {
                obj->collided = FALSE;
            }
        } else {
            float obj_rot = fabsf(obj->rotation);
            float rotation = (obj_rot == 0 || obj_rot == 90 || obj_rot == 180 || obj_rot == 270) ? 0 : player->rotation;
            if (intersect(
                player->x, player->y, player->width, player->height, rotation, 
                obj->x, obj->y, hitbox->width, hitbox->height, obj->rotation
            )) {
                handle_collision(player, obj, hitbox);
                obj->collided = TRUE;
                number_of_collisions++;
            } else {
                obj->collided = FALSE;
            }
        }
    } else {
        obj->collided = FALSE;
    }
}

GDObjectTyped *block_buffer[MAX_COLLIDED_OBJECTS];
int block_count = 0;

GDObjectTyped *hazard_buffer[MAX_COLLIDED_OBJECTS];
int hazard_count = 0;

void collide_with_objects() {
    Player *player = &state.player;
    number_of_collisions = 0;
    number_of_collisions_checks = 0;

    int sx = (int)(player->x / SECTION_SIZE);
    int sy = (int)(player->y / SECTION_SIZE);
    
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            Section *sec = get_or_create_section(sx + dx, sy + dy);
            for (int i = 0; i < sec->object_count; i++) {
                GDObjectTyped *obj = sec->objects[i];
                ObjectHitbox *hitbox = (ObjectHitbox *) &objects[obj->id].hitbox;
                
                if (hitbox->type == HITBOX_SOLID) {
                    block_buffer[block_count++] = obj;
                } else if (hitbox->type == HITBOX_SPIKE) {
                    hazard_buffer[hazard_count++] = obj;
                } else { // HITBOX_SPECIAL
                    collide_with_obj(obj);
                }
            }
        }
    }

    for (int i = 0; i < block_count; i++) {
        GDObjectTyped *obj = block_buffer[i];
        collide_with_obj(obj);
    }
    
    for (int i = 0; i < hazard_count; i++) {
        GDObjectTyped *obj = hazard_buffer[i];
        collide_with_obj(obj);
    }

    block_count = 0;
    hazard_count = 0;
}

void cube_gamemode(Player *player) {
    int mult = (player->upside_down ? -1 : 1);
    
    trail.positionR = (Vec2){player->x, player->y};  
    trail.startingPositionInitialized = TRUE;

    player->gravity = -2794.1082;
    
    if (player->vel_y < -810) player->vel_y = -810;

    if (player->y > 2794.f) player->dead = TRUE;


    player->rotation += 415.3848f * STEPS_DT * mult * (player->mini ? 1.2f : 1.f);

    if (player->on_ground) {
        MotionTrail_StopStroke(&trail);
        player->rotation = round(player->rotation / 90.0f) * 90.0f;
    }

    if ((player->time_since_ground < 0.05f) && (frame_counter & 0b11) == 0) {
        particle_templates[CUBE_DRAG].angle = (player->upside_down ? -90 : 90);
        spawn_particle(CUBE_DRAG, getLeft(player) + 4, (player->upside_down ? getTop(player) - 2 : getBottom(player) + 2), NULL);
    }

    if (player->on_ground && WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) {
        set_p_velocity(player, 603.72);
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
    float scale = (player->mini) ? 0.6f : 1.f;
    
    float x, y;
    rotate_point_around_center(
        player->x, player->y,
        player->rotation,
        player->x - 12 * scale, player->y + (player->upside_down ? 10 : -10) * scale,
        &x, &y
    );
    
    trail.positionR = (Vec2){x, y};  
    trail.startingPositionInitialized = TRUE;

    if ((frame_counter & 0b11) == 0) {   
        // Particle trail
        spawn_particle(SHIP_TRAIL, x, y, NULL);
        
        // Holding particles
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) {
            spawn_particle(HOLDING_SHIP_TRAIL, x, y, NULL);
        }

        // Ground drag effectr
        if (player->on_ground) {
            particle_templates[SHIP_DRAG].speed = 95 * mult;
            particle_templates[SHIP_DRAG].gravity_y = (player->upside_down ? 100 : -300);
            spawn_particle(SHIP_DRAG, player->x, (player->upside_down ? getTop(player) : getBottom(player)), NULL);
        }
    }
}

void update_ship_rotation(Player *player) {
    float diff_x = (player->x - state.old_player.x);
    float diff_y = (player->y - state.old_player.y);

    float angle_rad = atan2f(-diff_y, diff_x);
    player->rotation = iSlerp(player->rotation, RadToDeg(angle_rad), 0.05f, STEPS_DT);
}

void ship_gamemode(Player *player) {
    if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) {
        if (player->vel_y <= grav(player, 103.485492f))
            player->gravity = player->mini ? 1643.5872f : 1397.0491f;
        else
            player->gravity = player->mini ? 1314.86976f : 1117.64328f;
    } else {
        if (player->vel_y >= grav(player, 103.485492f))
            player->gravity = player->mini ? -1577.85408f : -1341.1719f;
        else
            player->gravity = player->mini ? -1051.8984f : -894.11464f;
    }

    ship_particles(player);
    
    float min = player->mini ? -406.566f : -345.6f;
    float max = player->mini ? 508.248f : 432.0f;

    if (player->vel_y < min) {
        player->vel_y = min;
    } else if (player->vel_y > max) {
        player->vel_y = max;
    }
}

void ball_gamemode(Player *player) {
    int mult = (player->upside_down ? -1 : 1);
    
    trail.positionR = (Vec2){player->x, player->y};  
    trail.startingPositionInitialized = TRUE;

    player->gravity = -1676.46672f;  
    
    if (player->on_ground || player->on_ceiling) {
        player->ball_rotation_speed = 2.3;
        MotionTrail_StopStroke(&trail);

        if ((frame_counter & 0b11) == 0) {
            particle_templates[CUBE_DRAG].angle = (player->upside_down ? -90 : 90);
            spawn_particle(CUBE_DRAG, player->x, (player->upside_down ? getTop(player) - 2 : getBottom(player) + 2), NULL);
        }
    }

    // Jump
    if ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A) && (player->on_ground || player->on_ceiling) && player->buffering_state == BUFFER_READY) {
        player->upside_down ^= 1;
        set_p_velocity(player, -181.11601);

        player->buffering_state = BUFFER_END;
        
        player->ball_rotation_speed = -1.f;
    }
    
    player->rotation += player->ball_rotation_speed * mult;

    if (player->vel_y < -810) {
        player->vel_y = -810;
    } else if (player->vel_y > 810) {
        player->vel_y = 810;
    }
}

void run_camera() {
    Player *player = &state.player;

    // Cap at camera_x
    if (state.camera_x + SCREEN_WIDTH_AREA >= level_info.wall_x) {
        state.camera_x = level_info.wall_x - SCREEN_WIDTH_AREA;
    } else {
        state.camera_x += player->vel_x * STEPS_DT;
        state.ground_x += player->vel_x * STEPS_DT * state.mirror_speed_factor;
        state.background_x += player->vel_x * STEPS_DT * state.mirror_speed_factor;
    }

    float upper = 90.f;
    float lower = 120.f;

    if (player->upside_down) {
        upper = 120.f;
        lower = 90.f;
    }
    
    float playable_height = state.player.ceiling_y - state.player.ground_y;
    float calc_height = 0;

    if (state.player.gamemode != GAMEMODE_CUBE) {
        calc_height = (SCREEN_HEIGHT_AREA - playable_height) / 2;
    }

    state.ground_y_gfx = iSlerp(state.ground_y_gfx, calc_height, 0.02f, STEPS_DT);

    if (player->gamemode == GAMEMODE_CUBE) {
        if (player->y <= SCREEN_HEIGHT_AREA + state.camera_y_lerp - upper) {
            if (player->y < lower + state.camera_y_lerp){
                state.camera_y_lerp = player->y - lower;
            }
        } else {
            state.camera_y_lerp = player->y - SCREEN_HEIGHT_AREA + upper;
        }

        if (state.camera_y_lerp < -90.f) state.camera_y_lerp = -90.f;
        if (state.camera_y_lerp > MAX_LEVEL_HEIGHT) state.camera_y_lerp = MAX_LEVEL_HEIGHT;

        state.camera_y = iSlerp(state.camera_y, state.camera_y_lerp, 0.05f, STEPS_DT);
    } else {
        state.camera_y = iSlerp(state.camera_y, state.camera_intended_y, 0.02f, STEPS_DT);
        state.camera_y_lerp = state.camera_y;
    }
}

void spawn_glitter_particles() {
    if ((frame_counter & 0b1111) == 0) {
        particle_templates[GLITTER_EFFECT].angle = random_float(0, 360);
        spawn_particle(GLITTER_EFFECT, state.camera_x + 240, state.camera_y + (SCREEN_HEIGHT_AREA / 2), NULL);
    }
}

void run_player() {
    Player *player = &state.player;
    float scale = (player->mini) ? 0.6f : 1.f;

    player->height = 30 * scale;
    player->width = 30 * scale;

    trail.stroke = 10.f * scale;
    
    // Ground
    if (getBottom(player) <= player->ground_y) {
        if (player->upside_down) {
            player->on_ceiling = TRUE;
        } else {
            player->on_ground = TRUE;           
        }
        player->time_since_ground = 0; 
    } 

    // Ceiling
    if (getTop(player) >= player->ceiling_y) {
        if (player->upside_down) {
            player->on_ground = TRUE;
        } else {
            player->on_ceiling = TRUE;           
        } 
        player->time_since_ground = 0; 
    } 

    switch (player->gamemode) {
        case GAMEMODE_CUBE:
            cube_gamemode(player);

            if (p1_trail && (frame_counter & 0b1111) == 0) {
                particle_templates[P1_TRAIL].start_scale = 0.73333f * scale;
                particle_templates[P1_TRAIL].end_scale = 0.73333f * scale;
                spawn_particle(P1_TRAIL, player->x, player->y, NULL);
            }
            break;
        case GAMEMODE_SHIP:
            MotionTrail_ResumeStroke(&trail);
            spawn_glitter_particles();
            ship_gamemode(player);

            if (p1_trail && (frame_counter & 0b1111) == 0) {
                particle_templates[P1_TRAIL].start_scale = 0.73333f * scale / 1.8;
                particle_templates[P1_TRAIL].end_scale = 0.73333f * scale / 1.8;
                spawn_particle(P1_TRAIL, player->x, player->y, NULL);
            }
            break;
        case GAMEMODE_BALL:
            ball_gamemode(player);
            if (p1_trail && (frame_counter & 0b1111) == 0) {
                particle_templates[P1_TRAIL].start_scale = 0.73333f * scale;
                particle_templates[P1_TRAIL].end_scale = 0.73333f * scale;
                spawn_particle(P1_TRAIL, player->x, player->y, NULL);
            }
            break;
        
    }
    
    player->time_since_ground += STEPS_DT;
    player->lerp_rotation = iSlerp(player->lerp_rotation, player->rotation, 0.2f, STEPS_DT);
    
    player->vel_y += player->gravity * STEPS_DT;
    player->y += player_get_vel(player, player->vel_y) * STEPS_DT;
    player->x += player->vel_x * STEPS_DT;

    // Ground
    if (player->gamemode == GAMEMODE_SHIP) update_ship_rotation(player);
    
    if (getBottom(player) < player->ground_y) {
        if (player->gamemode == GAMEMODE_CUBE && player->upside_down) {
            player->dead = TRUE;
            return;
        }

        player->vel_y = 0;
        player->y = player->ground_y + (player->height / 2);
    }

    // Ceiling
    if (getTop(player) > player->ceiling_y) {
        player->vel_y = 0;
        player->y = player->ceiling_y - (player->height / 2);
 
    } 

    
    // End level
    if (player->x > level_info.wall_x + 30) {
        level_info.completing = TRUE;
    }
}

void handle_mirror_transition() {
    state.mirror_factor = approachf(state.mirror_factor, state.intended_mirror_factor, 0.01f, 0.002f);
    state.mirror_speed_factor = approachf(state.mirror_speed_factor, state.intended_mirror_speed_factor, 0.02f, 0.004f);
    if (state.mirror_factor >= 0.5f) {
        state.mirror_mult = -1;
    } else {
        state.mirror_mult = 1;
    }
}

void handle_player() {
    Player *player = &state.player;
    if ((WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_A)) {
        if (player->buffering_state == BUFFER_NONE) {
            player->buffering_state = BUFFER_READY;
        }
    } else {
        player->buffering_state = BUFFER_NONE;
    }
    
    player->gravity_change = FALSE;
    player->on_ground = FALSE;
    player->on_ceiling = FALSE;

    u32 t0 = gettime();
    collide_with_objects();
    u32 t1 = gettime();
    collision_time = ticks_to_microsecs(t1 - t0) / 1000.f * 4.f;
    
    t0 = gettime();
    run_player();
    t1 = gettime();
    player_time = ticks_to_microsecs(t1 - t0) / 1000.f * 4.f;

    
    run_camera();
    handle_mirror_transition();

    if (state.noclip) state.player.dead = FALSE;
}

void full_init_variables() {
    state.ground_x = 0;
    state.background_x = 0;

    particle_templates[CUBE_DRAG].start_color.r = p1.r;
    particle_templates[CUBE_DRAG].start_color.g = p1.g;
    particle_templates[CUBE_DRAG].start_color.b = p1.b;
    
    particle_templates[CUBE_DRAG].end_color.r = p1.r;
    particle_templates[CUBE_DRAG].end_color.g = p1.g;
    particle_templates[CUBE_DRAG].end_color.b = p1.b;

    particle_templates[GLITTER_EFFECT].start_color.r = p1.r;
    particle_templates[GLITTER_EFFECT].start_color.g = p1.g;
    particle_templates[GLITTER_EFFECT].start_color.b = p1.b;
    
    particle_templates[GLITTER_EFFECT].end_color.r = p1.r;
    particle_templates[GLITTER_EFFECT].end_color.g = p1.g;
    particle_templates[GLITTER_EFFECT].end_color.b = p1.b;

    particle_templates[P1_TRAIL].start_color.r = p1.r;
    particle_templates[P1_TRAIL].start_color.g = p1.g;
    particle_templates[P1_TRAIL].start_color.b = p1.b;
    
    particle_templates[P1_TRAIL].end_color.r = p1.r;
    particle_templates[P1_TRAIL].end_color.g = p1.g;
    particle_templates[P1_TRAIL].end_color.b = p1.b;

    init_variables();
}

void init_variables() {
    MotionTrail_Init(&trail, 0.3f, 3, 10.0f, p2, trail_tex);
    MotionTrail_StopStroke(&trail);

    state.camera_x = -120;
    state.camera_x_lerp = -120;
    state.camera_y = -90;
    state.camera_y_lerp = -90;


    state.ground_y_gfx = 0;
    state.mirror_factor = 0;
    state.mirror_speed_factor = 1.f;
    state.intended_mirror_factor = 0;
    state.intended_mirror_speed_factor = 1.f;

    current_fading_effect = FADE_NONE;
    p1_trail = FALSE;

    level_info.completing = FALSE;
    
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
}

void handle_death() {
    MP3Player_Stop();
    for (s32 i = 0; i < 60; i++) {
        draw_game();
    }
    init_variables();
    reload_level();
}

void handle_completion() {
    for (s32 i = 0; i < 240; i++) {
        draw_game();
    }
}

void load_icons() {
    icon_l1 = GRRLIB_LoadTexturePNG(player_01_001_png);
    icon_l2 = GRRLIB_LoadTexturePNG(player_01_2_001_png);
    ship_l1 = GRRLIB_LoadTexturePNG(ship_01_001_png);
    ship_l2 = GRRLIB_LoadTexturePNG(ship_01_2_001_png);
    ball_l1 = GRRLIB_LoadTexturePNG(player_ball_01_001_png);
    ball_l2 = GRRLIB_LoadTexturePNG(player_ball_01_2_001_png);
    trail_tex = GRRLIB_LoadTexturePNG(trail_png);

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
    GRRLIB_FreeTexture(ship_l1);
    GRRLIB_FreeTexture(ship_l2);
    GRRLIB_FreeTexture(ball_l1);
    GRRLIB_FreeTexture(ball_l2);
    GRRLIB_FreeTexture(trail_tex);
}

void draw_ship(Player *player, float calc_x, float calc_y) {
    GRRLIB_SetHandle(icon_l1, 30, 30);  // 60x60
    GRRLIB_SetHandle(icon_l2, 30, 30);
    GRRLIB_SetHandle(ship_l1, 38, 24);  // 76x48
    GRRLIB_SetHandle(ship_l2, 38, 24);
    
    float scale = (player->mini) ? 0.6f : 1.f;

    int mult = (player->upside_down ? -1 : 1);

    float x;
    float y;

    float calculated_scale = 0.733f * state.mirror_mult * scale;
    float calculated_rotation = player->rotation * state.mirror_mult;

    #define CUBE_DIVISOR 1.8

    rotate_point_around_center_gfx(
        get_mirror_x(calc_x, state.mirror_factor), calc_y,
        7, ((player->upside_down) ? 5 : -9) * scale,
        38, 30,
        60, 60,
        calculated_rotation,
        &x, &y
    );
    set_texture(icon_l1);
    // Top (icon)
    custom_drawImg(
        x + 6 - (30), y + 6 - (30),
        icon_l1,
        calculated_rotation,
        calculated_scale / CUBE_DIVISOR, (0.733f * scale) / CUBE_DIVISOR,
        RGBA(p1.r, p1.g, p1.b, 255)
    );

    set_texture(icon_l2);
    custom_drawImg(
        x + 6 - (30), y + 6 - (30),
        icon_l2,
        calculated_rotation,
        calculated_scale / CUBE_DIVISOR, (0.733f * scale) / CUBE_DIVISOR,
        RGBA(p2.r, p2.g, p2.b, 255)
    );

    float y_rot = (player->upside_down) ? -4 : 12;
    if (player->mini) {
        y_rot = (player->upside_down) ? 0 : 9.6;
    }
    rotate_point_around_center_gfx(
        get_mirror_x(calc_x, state.mirror_factor), calc_y,
        0, y_rot,
        38, 30,
        76, 48,
        calculated_rotation,
        &x, &y
    );

    set_texture(ship_l1);
    // Bottom (ship)
    custom_drawImg(
        x + 6 - (30), y + 6 - (30),
        ship_l1,
        calculated_rotation,
        calculated_scale, (0.733f * scale) * mult,
        RGBA(p1.r, p1.g, p1.b, 255)
    );

    set_texture(ship_l2);
    custom_drawImg(
        x + 6 - (30), y + 6 - (30),
        ship_l2,
        calculated_rotation,
        calculated_scale, (0.733f * scale) * mult,
        RGBA(p2.r, p2.g, p2.b, 255)
    );
}

void draw_player() {
    Player *player = &state.player;

    float calc_x = ((player->x - state.camera_x) * SCALE);
    float calc_y = screenHeight - ((player->y - state.camera_y) * SCALE);
    
    GRRLIB_SetBlend(GRRLIB_BLEND_ADD);

    MotionTrail_Update(&trail, dt);
    MotionTrail_Draw(&trail);

    GX_SetTevOp  (GX_TEVSTAGE0, GX_MODULATE);
    GX_SetVtxDesc(GX_VA_TEX0,   GX_DIRECT);

    GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);

    draw_particles(P1_TRAIL);

    float scale = (player->mini) ? 0.6f : 1.f;

    switch (player->gamemode) {
        case GAMEMODE_CUBE:
            GRRLIB_SetHandle(icon_l1, 30, 30);
            GRRLIB_SetHandle(icon_l2, 30, 30);
        
            set_texture(icon_l1);
            custom_drawImg(
                get_mirror_x(calc_x, state.mirror_factor) + 6 - (30), calc_y + 6 - (30),
                icon_l1,
                player->lerp_rotation * state.mirror_mult,
                0.73333333333333333333333333333333 * state.mirror_mult * scale,
                0.73333333333333333333333333333333 * scale,
                RGBA(p1.r, p1.g, p1.b, 255)
            );

            set_texture(icon_l2);
            custom_drawImg(
                get_mirror_x(calc_x, state.mirror_factor) + 6 - (30), calc_y + 6 - (30),
                icon_l2,
                player->lerp_rotation * state.mirror_mult,
                0.73333333333333333333333333333333 * state.mirror_mult * scale,
                0.73333333333333333333333333333333 * scale,
                RGBA(p2.r, p2.g, p2.b, 255)
            );
            break;
        case GAMEMODE_SHIP:
            draw_ship(player, calc_x - 8 * state.mirror_mult, calc_y);
            break;
        case GAMEMODE_BALL:
            GRRLIB_SetHandle(ball_l1, 36, 36);
            GRRLIB_SetHandle(ball_l2, 36, 36);
            set_texture(ball_l1);
            custom_drawImg(
                get_mirror_x(calc_x, state.mirror_factor) + 6 - (36), calc_y + 6 - (36),
                ball_l1,
                player->lerp_rotation * state.mirror_mult,
                0.73333333333333333333333333333333 * state.mirror_mult * scale,
                0.73333333333333333333333333333333 * scale,
                RGBA(p1.r, p1.g, p1.b, 255)
            );

            set_texture(ball_l2);
            custom_drawImg(
                get_mirror_x(calc_x, state.mirror_factor) + 6 - (36), calc_y + 6 - (36),
                ball_l2,
                player->lerp_rotation * state.mirror_mult,
                0.73333333333333333333333333333333 * state.mirror_mult * scale,
                0.73333333333333333333333333333333 * scale,
                RGBA(p2.r, p2.g, p2.b, 255)
            );
            break;
    }
    set_texture(prev_tex);
}

GRRLIB_texImg *get_p1_trail_tex() {
    switch (state.player.gamemode) {
        case GAMEMODE_CUBE:
            return icon_l1;
        
        case GAMEMODE_SHIP:
            return icon_l1;
        
        case GAMEMODE_BALL:
            return ball_l1;
    }
    return icon_l1;
}