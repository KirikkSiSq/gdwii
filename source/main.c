/*===========================================
        GRRLIB (GX Version)
        Example code by Xane

        This example shows the different
        new blending modes.
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <math.h>

#include <asndlib.h>
#include "objects.h"
#include <stdio.h>
#include <ogc/lwp_watchdog.h>
#include <ogc/lwp.h>
#include <ogc/lwp_mutex.h>

#include <unistd.h>

#include "main.h"

#include "custom_mp3player.h"

// include generated header
#include "level_loading.h"
#include "objects.h"

#include "font_png.h"

#include "player.h"
#include "math.h"

#include "game.h"
#include "menu.h"

// Declare Static Functions
static void ExitGame(void);

int screenWidth = 0;
int screenHeight = 0;

int gameRoutine = ROUTINE_MENU;

u64 startTime;
int frameCount = 0;
float fps = 0;

GameState state;

GRRLIB_texImg *font = NULL;

int frame_counter = 0;
int old_frame_counter = 0;

// Profiling
float obj_layer_time = 0;
float physics_time = 0;
float collision_time = 0;
float particles_time = 0;
float triggers_time = 0;
float player_time = 0;

int number_of_collisions = 0;
int number_of_collisions_checks = 0;


void draw_game() {
    draw_background(state.background_x / 8, -(state.camera_y / 8) + 512);

    draw_particles(GLITTER_EFFECT);
    
    u64 t0 = gettime();
    draw_all_object_layers();
    u64 t1 = gettime();
    
    obj_layer_time = ticks_to_microsecs(t1 - t0) / 1000.f;

    draw_end_wall();

    draw_ground(0, FALSE);
    
    if (state.ground_y_gfx > 0) {
        if (state.camera_y + state.ground_y_gfx > 0) draw_ground(state.camera_y + state.ground_y_gfx, FALSE);
        draw_ground(state.camera_y + SCREEN_HEIGHT_AREA - state.ground_y_gfx, TRUE);
    }
    
    // FPS logic
    frameCount++;
    u64 currentTime = gettime();
    float elapsed = ticks_to_millisecs(currentTime - startTime) / 1000.0f;

    if (elapsed >= 1.0f) {
        fps = frameCount / elapsed;
        frameCount = 0;
        startTime = currentTime;
    }
    if (enable_info) {    
        t0 = gettime();

        // Render FPS
        char fpsText[64];
        snprintf(fpsText, sizeof(fpsText), "FPS: %.2f Steps: %d Objs: %d", fps, frame_counter - old_frame_counter, objectsArrayList->count);
        GRRLIB_Printf(20, 20, font, RGBA(255,255,255,255), 0.5, fpsText);  // White tex
        
        char layerText[64];
        snprintf(layerText, sizeof(layerText), "Drawn layers: %d", layersDrawn);
        GRRLIB_Printf(20, 50, font, RGBA(255,255,255,255), 0.5, layerText);
        old_frame_counter = frame_counter;
        char player_x[64];
        snprintf(player_x, sizeof(player_x), "X: %.2f", state.player.x);
        GRRLIB_Printf(20, 80, font, RGBA(255,255,255,255), 0.5, player_x);

        char player_y[64];
        snprintf(player_y, sizeof(player_y), "Y: %.2f", state.player.y);
        GRRLIB_Printf(20, 110, font, RGBA(255,255,255,255), 0.5, player_y);
        
        char obj_layer[64];
        snprintf(obj_layer, sizeof(obj_layer), "Layers: %.2f ms", obj_layer_time);
        GRRLIB_Printf(20, 140, font, RGBA(255,255,255,255), 0.5, obj_layer);
        
        char physics[128];
        snprintf(physics, sizeof(physics), "Physics: %.2f ms (P: %.2f Obj: %.2f E: %.2f)", physics_time, player_time, triggers_time, particles_time);
        GRRLIB_Printf(20, 170, font, RGBA(255,255,255,255), 0.5, physics);

        char collision[128];
        snprintf(collision, sizeof(collision), "Collision: %.2f ms (Checks: %d Succeded: %d)", collision_time, number_of_collisions_checks, number_of_collisions);
        GRRLIB_Printf(20, 200, font, RGBA(255,255,255,255), 0.5, collision);

        t1 = gettime();
        float text = ticks_to_microsecs(t1 - t0) / 1000.f;
        
        char text_ms[64];
        snprintf(text_ms, sizeof(text_ms), "Text: %.2f ms", text);
        GRRLIB_Printf(20, 230, font, RGBA(255,255,255,255), 0.5, text_ms);
    }

    if (state.noclip) {
        GRRLIB_Printf(400, 20, font, RGBA(255,255,255,255), 0.5, "Noclip activated");
    }

    GRRLIB_Render();
    layersDrawn = 0;
}

#include <mad.h>

int main() {
    SYS_STDIO_Report(true);
    // Init GRRLIB & WiiUse
    GRRLIB_Init();
    WPAD_Init();
    WPAD_SetIdleTimeout( 60 * 10 );
    WPAD_SetDataFormat( WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR );

    srand(time(NULL));

    // Initialise the audio subsystem
	ASND_Init();
    MP3Player_Init();

    load_spritesheet();

    // Set resolution based on mode
    screenWidth  = rmode->fbWidth;   // Framebuffer width (typically 640)
    screenHeight = rmode->efbHeight; // EFB height (usually 480 or 576)

    startTime = gettime();    

    font = GRRLIB_LoadTexturePNG(font_png);
    GRRLIB_InitTileSet(font, 24, 36, 32);

    init_variables();
    while(1) {
        switch (gameRoutine) {
            case ROUTINE_MENU:
                if (menu_loop()) goto Exit;
                break;
            case ROUTINE_GAME:
                if(game_loop()) goto Exit;
                break;
        }
    }
Exit:
	MP3Player_Stop();
    ExitGame();
    return 0;
}

static void ExitGame(void) {
    unload_spritesheet();
    unload_level();

    // Deinitialize GRRLIB & Video
    GRRLIB_Exit();

    // Exit application
    exit(0);
}