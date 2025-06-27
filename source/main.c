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
#include "blocks.h"

#include "oggplayer.h"

// include generated header
#include "BackOnTrack_ogg.h"
#include "level_loading.h"
#include "blocks.h"

#include "crash_screen.h"

// Declare Static Functions
static void ExitGame(void);

float camera_x = 0;
float camera_y = 0;

int screenWidth = 0;
int screenHeight = 0;

extern void __exception_sethandler(u32 n, void (*handler)(frame_context *));

int main() {
    SYS_STDIO_Report(true);
    // Init GRRLIB & WiiUse
    GRRLIB_Init();
    WPAD_Init();
    WPAD_SetIdleTimeout( 60 * 10 );
    WPAD_SetDataFormat( WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR );

    __exception_sethandler(EX_DSI, crash_handler);
    __exception_sethandler(EX_ISI, crash_handler);
    __exception_sethandler(EX_PRG, crash_handler);

    // Initialise the audio subsystem
	ASND_Init();

    load_spritesheet();

    GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);  // Auto-detects best mode

    // Set resolution based on mode
    screenWidth  = rmode->fbWidth;   // Framebuffer width (typically 640)
    screenHeight = rmode->efbHeight; // EFB height (usually 480 or 576)

    load_level();
    
    PlayOgg(BackOnTrack_ogg, BackOnTrack_ogg_size, 0, OGG_ONE_TIME);

    while (true) {
        WPAD_ScanPads();

        draw_background(0, -512);

        // put_object(BASIC_BLOCK, 64, 8, 0);
        // put_object(BASIC_BLOCK, 128, 64, 45);
        // put_object(BASIC_BLOCK, 64, 128, 90);
        // put_object(BASIC_BLOCK, 640/2, 500/2, 180);

        handle_objects();

        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_LEFT) {
            camera_x -= 8; 
        }
        
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_RIGHT) {
            camera_x += 8; 
        }
        
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_UP) {
            camera_y -= 8; 
        }
        
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_DOWN) {
            camera_y += 8; 
        }

        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_HOME) {
            break;
        }
        GRRLIB_Render();
    }
	StopOgg();
    ExitGame();
    return 0;
}

static void ExitGame(void) {
    unload_spritesheet();

    // Deinitialize GRRLIB & Video
    GRRLIB_Exit();

    // Exit application
    exit(0);
}
