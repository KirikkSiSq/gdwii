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

#include "pusab_ttf.h"

#include "player.h"

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

GRRLIB_ttfFont *font = NULL;

int frame_counter = 0;
int old_frame_counter = 0;

void draw_game() {
    draw_background(state.camera_x / 8, -(state.camera_y / 8) + 512);

    draw_particles(GLITTER_EFFECT);

    draw_all_object_layers();

    draw_ground(state.player.ground_y, FALSE);
    draw_ground(state.player.ceiling_y, TRUE);
    
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
        // Render FPS
        char fpsText[64];
        snprintf(fpsText, sizeof(fpsText), "FPS: %.2f", fps);
        GRRLIB_PrintfTTF(20, 20, font, fpsText, 20, 0xFFFFFFFF);  // White tex
        
        char layerText[64];
        snprintf(layerText, sizeof(layerText), "Drawn layers: %d (%d)", layersDrawn, frame_counter - old_frame_counter);
        GRRLIB_PrintfTTF(20, 50, font, layerText, 20, 0xFFFFFFFF);
        old_frame_counter = frame_counter;
        char player_x[64];
        snprintf(player_x, sizeof(player_x), "X: %.2f", state.player.x);
        GRRLIB_PrintfTTF(20, 80, font, player_x, 20, 0xFFFFFFFF);

        char player_y[64];
        snprintf(player_y, sizeof(player_y), "Y: %.2f", state.player.y);
        GRRLIB_PrintfTTF(20, 110, font, player_y, 20, 0xFFFFFFFF);
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

    GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);  // Auto-detects best mode

    // Set resolution based on mode
    screenWidth  = rmode->fbWidth;   // Framebuffer width (typically 640)
    screenHeight = rmode->efbHeight; // EFB height (usually 480 or 576)

    startTime = gettime();    

    font = GRRLIB_LoadTTF(pusab_ttf, pusab_ttf_size);

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