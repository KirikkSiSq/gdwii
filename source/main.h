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

extern GameState state;

extern GRRLIB_ttfFont *font;

void draw_game();
void print_debug(GRRLIB_ttfFont *font);