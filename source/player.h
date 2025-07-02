#pragma once

#include <stdbool.h>

#define SCREEN_HEIGHT_AREA ((screenHeight / BLOCK_SIZE_PX) * 30)

typedef struct {
    float x;
    float y;
    
    float vel_x;
    float vel_y;
    
    float gravity;

    float rotation;
    
    float width;
    float height;

    float ground_y;
    float ceiling_y;

    int gamemode;

    bool on_ground;
    bool on_ceiling;
    bool mini;
    bool upside_down;
    bool dead;

    int buffering_state;

    float time_since_ground;
} Player;

enum BufferingState {
    BUFFER_NONE,
    BUFFER_READY,
    BUFFER_END
};

enum PlayerGamemode {
    GAMEMODE_CUBE,
    GAMEMODE_SHIP,
    GAMEMODE_COUNT
};

void handle_death();
void init_variables();
void load_icons();
void unload_icons();
void draw_player();
void handle_player();