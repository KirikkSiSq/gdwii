#pragma once

#include <stdbool.h>

typedef struct {
    float x;
    float y;
    float width;
    float height;
    float vel_x;
    float vel_y;
    float gravity;
    float rotation;
    int gamemode;
    bool on_ground;
    bool upside_down;
    int buffering_state;
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
void init_player();
void draw_player();
void handle_player();