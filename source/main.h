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
    
    Player player;
    Player old_player;

    float ground_y_gfx;
    
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