#pragma once

#include <stdbool.h>
#include <grrlib.h>
#include "level_loading.h"
#include "math.h"

#define SCREEN_WIDTH_AREA ((screenWidth / BLOCK_SIZE_PX) * 30) 
#define SCREEN_HEIGHT_AREA ((screenHeight / BLOCK_SIZE_PX) * 30 + 8) 

#define MAX_LEVEL_HEIGHT 2400.f

#define MAX_COLLIDED_OBJECTS 4096

typedef struct {
    GameObject *slope;
    float elapsed;
    bool snapDown;
} SlopeData;

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

    int gamemode;

    bool on_ground;
    bool on_ceiling;
    bool mini;
    bool upside_down;

    bool left_ground;

    float ball_rotation_speed;

    int buffering_state;

    float time_since_ground;
    
    float ufo_last_y;

    float ceiling_inv_time;

    float timeElapsed;

    GameObject *gravObj;

    SlopeData slope_data;
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
    GAMEMODE_UFO,
    GAMEMODE_COUNT
};

enum PlayerSpeeds {
    SPEED_SLOW,
    SPEED_NORMAL,
    SPEED_FAST,
    SPEED_FASTER,
    SPEED_COUNT
};

extern Color p1;
extern Color p2;

extern const float player_speeds[SPEED_COUNT];

void handle_death();
void init_variables();
void full_init_variables();
void load_icons();
void unload_icons();
void draw_player(Player *player);
void handle_mirror_transition();
void handle_player(Player *player);
void handle_completion();
void set_p_velocity(Player *player, float vel);
GRRLIB_texImg *get_p1_trail_tex();
float slope_angle(GameObject *obj, Player *player);
void slope_collide(GameObject *obj, Player *player);
void slope_calc(GameObject *obj, Player *player);
void clear_slope_data(Player *player);
int grav_slope_orient(GameObject *obj, Player *player);
void snap_player_to_slope(GameObject *obj, Player *player); 
bool slope_touching(GameObject *obj, Player *player);
void run_camera();