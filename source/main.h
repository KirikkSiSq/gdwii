#pragma once

#include "player.h"

extern int screenWidth;
extern int screenHeight;

typedef struct {
    float camera_x;
    float camera_y;

    float camera_intended_y;

    float camera_x_lerp;
    float camera_y_lerp;
    
    Player player;
} GameState;

enum ThreadIndex {
    GAMEPLAY_THREAD,
    RENDER_THREAD,
    THREAD_COUNT
};

extern float dt;

extern GameState state_buffers[THREAD_COUNT];
extern GameState *gameplay_state;
extern GameState *render_state;

void print_debug(GRRLIB_ttfFont *font);