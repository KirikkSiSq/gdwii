#pragma once

#include <stdbool.h>
#include <grrlib.h>
#include "math.h"

#define SCREEN_WIDTH_AREA ((screenWidth / BLOCK_SIZE_PX) * 30) 
#define SCREEN_HEIGHT_AREA ((screenHeight / BLOCK_SIZE_PX) * 30 + 8) 

#define MAX_LEVEL_HEIGHT 2400.f

#define MAX_COLLIDED_OBJECTS 4096

typedef struct {
    float x;
    float y;
    
    float vel_x;
    float vel_y;
    
    float gravity;

    float rotation;
    float lerp_rotation;
    
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

    bool gravity_change;
    bool left_ground;

    float ball_rotation_speed;

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
    GAMEMODE_BALL,
    GAMEMODE_COUNT
};

extern Color p1;
extern Color p2;

void handle_death();
void init_variables();
void full_init_variables();
void load_icons();
void unload_icons();
void draw_player();
void handle_player();
void handle_completion();
void set_p_velocity(Player *player, float vel);
GRRLIB_texImg *get_p1_trail_tex();