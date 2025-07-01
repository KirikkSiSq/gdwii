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

GameState state_buffers[THREAD_COUNT];
GameState *gameplay_state;
GameState *render_state;

GRRLIB_ttfFont *font = NULL;

lwp_t state_mutex;

volatile bool should_exit = 0;

float dt;

int frame_counter = 0;

#define TICK_RATE  (1.0f / 60.0f)    // 60 logic updates per second
#define TICKS_PER_SEC  (float)TB_TIMER_CLOCK   // ~81,000,000 on Wii

lwp_t graphics_thread_handle;
lwp_t gameplay_thread_handle;

void *graphics_thread(void *arg) {
    printf("Graphics thread started\n");

    while (1) {
        if (should_exit) {
            break;
        }

        LWP_MutexLock(state_mutex);
        memcpy(render_state, gameplay_state, sizeof(GameState));
        LWP_MutexUnlock(state_mutex);

        draw_background(render_state->camera_x / 8, -(render_state->camera_y / 8) + 512);

        draw_all_object_layers();

        draw_ground(render_state->player.ground_y, FALSE);
        draw_ground(render_state->player.ceiling_y, TRUE);
        
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
        GRRLIB_PrintfTTF(20, 20, font, fpsText, 20, 0xFFFFFFFF);  // White text

        // Render mem
        char memText[64];
        snprintf(memText, sizeof(memText), "Level pool: %0.2f KB / %d KB", mempool_bytes_used(&level_pool) / 1024.f, mempool_bytes_total(&level_pool) / 1024);
        GRRLIB_PrintfTTF(20, 50, font, memText, 20, 0xFFFFFFFF);
        
        char layerText[64];
        snprintf(layerText, sizeof(layerText), "Drawn layers: %d", layersDrawn);
        GRRLIB_PrintfTTF(20, 110, font, layerText, 20, 0xFFFFFFFF);

        GRRLIB_Render();

        layersDrawn = 0;
    }
    return NULL;
}

#define ticks_to_secs_float(ticks) (((float)(ticks)/(float)(TB_TIMER_CLOCK*1000)))

void *gameplay_thread(void *arg) {
    
    printf("Gameplay thread started\n");
    load_level();
    
    PlayOgg(Jumper_ogg, Jumper_ogg_size, 0, OGG_ONE_TIME);

    // Create render thread
    int result = LWP_CreateThread(
        &graphics_thread_handle, // Thread handle (output)
        graphics_thread,     // Function to run
        NULL,               // Argument to thread function
        NULL,               // Stack (NULL = auto allocate)
        32768,               // Stack size
        50                  // Priority
    );

    if (result != 0) {
        printf("Failed to create graphics thread: %d\n", result);
        return NULL;
    }

    u64 lastTicks = gettime();  // Initial time in ticks
    while (1) {
        WPAD_ScanPads();

        u64 frameStart = gettime();
        dt = ticks_to_secs_float(frameStart - lastTicks) / 4; // 4 because it has to be 1/240 for gameplay 
        lastTicks = frameStart;

        LWP_MutexLock(state_mutex);

        
        for (int i = 0; i < 4; i++) {
            gameplay_state->old_player = gameplay_state->player;
            handle_player();
            handle_objects();
            update_particles();
            frame_counter++;
        }
        
        LWP_MutexUnlock(state_mutex);
        
        if (gameplay_state->player.dead) {
            StopOgg();
            handle_death();
            PlayOgg(Jumper_ogg, Jumper_ogg_size, 0, OGG_ONE_TIME);
            lastTicks = frameStart = gettime();
            dt = 1 / 240.f;
        }


        if (should_exit) {
            break;
        }
        
        u64 frameEnd = gettime();
        double elapsed = ticks_to_microsecs(frameEnd - frameStart);
        double sleepTime = 16666 - elapsed;

        if (sleepTime > 0) {
            usleep((long) sleepTime);
        }
    }
    return NULL;
}

int main() {
    SYS_STDIO_Report(true);
    // Init GRRLIB & WiiUse
    GRRLIB_Init();
    WPAD_Init();
    WPAD_SetIdleTimeout( 60 * 10 );
    WPAD_SetDataFormat( WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR );

    mempool_init(&level_pool, level_pool_buffer, LEVEL_POOL_SIZE);

    LWP_MutexInit(&state_mutex, false);

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

    gameplay_state = &state_buffers[GAMEPLAY_THREAD];
    render_state = &state_buffers[RENDER_THREAD];

    init_variables();

    // Create gameplay thread
    int result = LWP_CreateThread(
        &gameplay_thread_handle, // Thread handle (output)
        gameplay_thread,     // Function to run
        NULL,               // Argument to thread function
        NULL,               // Stack (NULL = auto allocate)
        32768,               // Stack size
        50                  // Priority
    );

    if (result != 0) {
        printf("Failed to create gameplay thread: %d\n", result);
        goto exit;
    }

    while(1) {
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_HOME) {
            break;
        }
        VIDEO_WaitVSync();
    }
exit:
    should_exit = 1; // Signal threads to exit
    
    void *retval;
    LWP_JoinThread(gameplay_thread_handle, &retval);
    LWP_JoinThread(graphics_thread_handle, &retval);
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