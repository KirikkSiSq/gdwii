#pragma once

#include "player.h"
#include "particles.h"

extern int screenWidth;
extern int screenHeight;

typedef struct {
    float camera_x;
    float camera_y;

    float camera_intended_y;

    float camera_x_lerp;
    float camera_y_lerp;

    float ground_x;
    float background_x;
    
    Player player;
    Player old_player;

    int mirror_mult;
    float intended_mirror_factor;
    float intended_mirror_speed_factor;
    float mirror_speed_factor;
    float mirror_factor;

    float ground_y_gfx;

    bool noclip;
    
    Particle particles[MAX_PARTICLES];
} GameState;

enum GameRoutine {
    ROUTINE_MENU,
    ROUTINE_GAME
};

extern int gameRoutine;

extern int frame_counter;

extern float physics_time;
extern float collision_time;
extern float particles_time;
extern float triggers_time;
extern float player_time;

extern float draw_time;
extern float layer_sorting;
extern float obj_particles_time;

extern int number_of_collisions;
extern int number_of_collisions_checks;

extern GameState state;

extern GRRLIB_texImg *font;

void draw_game();