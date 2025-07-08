#include "main.h"
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include "level.h"
#include "custom_mp3player.h"
#include "oggplayer.h"
#include "playSound_01_ogg.h"
#include "menuLoop_mp3.h"

int level_id = 0;

int menu_loop() {
    while (1) {
        WPAD_ScanPads();

        if (!MP3Player_IsPlaying()) {
            MP3Player_PlayBuffer(menuLoop_mp3, menuLoop_mp3_size, NULL);
        }

        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_LEFT) {
            level_id--;
            if (level_id < 0) level_id = LEVEL_NUM - 1; 
        }

        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_RIGHT) {
            level_id++;
            if (level_id >= LEVEL_NUM) level_id = 0;
        }

        GRRLIB_FillScreen(RGBA(0, 127, 255, 255));

        GRRLIB_PrintfTTF(0, 0, font, levels[level_id].level_name, 30, RGBA(255,255,255,255));
        
        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A) {
            // Start level
            gameRoutine = ROUTINE_GAME;
            MP3Player_Stop();
            PlayOgg(playSound_01_ogg, playSound_01_ogg_size, 0, OGG_ONE_TIME);
            for (int i = 0; i < 90; i++) {
                WPAD_ScanPads();
                VIDEO_WaitVSync();
            }
            break;
        }
        
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_HOME) {
            return TRUE;
        }

        GRRLIB_Render();
    }

    return FALSE;
}