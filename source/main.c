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

#include "blocks.h"

// Include Graphics
#include "GJ_GameSheet_png.h"
#include "game_bg_png.h"

// Declare Static Functions
static void ExitGame(void);

GRRLIB_texImg *bg;

int main() {
    // Init GRRLIB & WiiUse
    GRRLIB_Init();
    WPAD_Init();

    load_spritesheet();

    bg = GRRLIB_LoadTexturePNG(game_bg_png);

    
    GRRLIB_SetAntiAliasing(FALSE);

    f32 angle = 0;
    while (true) {
        WPAD_ScanPads();

        GRRLIB_DrawImg(0, -512, bg, 0, 1, 1, RGBA(56, 121, 255, 255));

        // put_object(BASIC_BLOCK, 64, 8, 0);
        // put_object(BASIC_BLOCK, 128, 64, 45);
        // put_object(BASIC_BLOCK, 64, 128, 90);
        // put_object(BASIC_BLOCK, 640/2, 500/2, 180);

        for (s32 j = 0; j < 640; j += 44) {
            for (s32 i = 0; i < VI_MAX_HEIGHT_NTSC; i += 44) {
                put_object(BASIC_BLOCK, j, i, angle);
            }
        }

        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) {
            break;
        }
        GRRLIB_Render();
        angle++;
    }
    ExitGame();
    return 0;
}

static void ExitGame(void) {
    unload_spritesheet();

    GRRLIB_FreeTexture(bg);

    // Deinitialize GRRLIB & Video
    GRRLIB_Exit();

    // Exit application
    exit(0);
}
