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

#include "oggplayer.h"

// include generated header
#include "Jumper_ogg.h"
#include "level_loading.h"
#include "objects.h"

#include "pusab_ttf.h"

#include "player.h"


// Declare Static Functions
static void ExitGame(void);

int screenWidth = 0;
int screenHeight = 0;

u64 startTime;
int frameCount = 0;
float fps = 0;

GameState state;

GRRLIB_ttfFont *font = NULL;

int frame_counter = 0;
int old_frame_counter = 0;

#define TICK_RATE  (1.0f / 60.0f)    // 60 logic updates per second
#define TICKS_PER_SEC  (float)TB_TIMER_CLOCK   // ~81,000,000 on Wii

void draw_game() {
    draw_background(state.camera_x / 8, -(state.camera_y / 8) + 512);

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

    GRRLIB_Render();
    layersDrawn = 0;
}

#define ticks_to_secs_float(ticks) (((float)(ticks)/(float)(TB_TIMER_CLOCK*1000)))

bool fixed_dt = FALSE;

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

    load_spritesheet();

    GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);  // Auto-detects best mode

    // Set resolution based on mode
    screenWidth  = rmode->fbWidth;   // Framebuffer width (typically 640)
    screenHeight = rmode->efbHeight; // EFB height (usually 480 or 576)

    startTime = gettime();    

    font = GRRLIB_LoadTTF(pusab_ttf, pusab_ttf_size);

    init_variables();
    
    load_level();

    PlayOgg(Jumper_ogg, Jumper_ogg_size, 0, OGG_ONE_TIME);

    u64 prevTicks = gettime();
    double accumulator = 0.0f;

    while(1) {
        u64 currentTicks = gettime();
        float frameTime = ticks_to_secs_float(currentTicks - prevTicks);
        if (frameTime > STEPS_DT * 16) frameTime = STEPS_DT * 16; // Avoid spiral of death
        if (fixed_dt) {
            frameTime = STEPS_DT;
            fixed_dt = FALSE;
        }
        prevTicks = currentTicks;

        accumulator += frameTime;

        while (accumulator >= STEPS_DT) {
            WPAD_ScanPads();
            state.old_player = state.player;
            handle_player();
            handle_objects();
            update_particles();
            frame_counter++;

            if (state.player.dead) break;

            accumulator -= STEPS_DT;
        }
                      
        if (state.player.dead) {
            StopOgg();
            handle_death();
            PlayOgg(Jumper_ogg, Jumper_ogg_size, 0, OGG_ONE_TIME);
            WPAD_ScanPads();
            fixed_dt = TRUE;
        }

        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_HOME) {
            break;
        }

        draw_game();
    }
	StopOgg();
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