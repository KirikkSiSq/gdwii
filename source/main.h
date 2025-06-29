#pragma once

#include "player.h"

extern int screenWidth;
extern int screenHeight;

typedef struct {
    float camera_x;
    float camera_y;
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