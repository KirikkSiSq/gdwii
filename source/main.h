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
    
    Particle particles[MAX_PARTICLES];
} GameState;

enum ThreadIndex {
    GAMEPLAY_THREAD,
    RENDER_THREAD,
    THREAD_COUNT
};

#define STEPS_DT (1.0f / 240.0f) // 1/240 seconds per physics step

extern int frame_counter;

extern GameState state;

void draw_game();
void print_debug(GRRLIB_ttfFont *font);