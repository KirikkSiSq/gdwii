#include "main.h"
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include "level.h"
#include "custom_mp3player.h"
#include "oggplayer.h"
#include "playSound_01_ogg.h"
#include "menuLoop_mp3.h"

#include <fat.h>
#include <dirent.h>
#include <sys/types.h>
#include "filesystem.h"

#include "menu.h"

#include <stdio.h>

int main_levels();
int sdcard_levels();

int level_id = 0;

char sd_level_paths[MAX_SD_LEVELS][MAX_PATH_LEN];
int sd_level_count = 0;

char current_level_name[255];

int level_mode = 0;

size_t outsize;

int menu_loop() {
    if (!fatInitDefault()) {
		printf("fatInitDefault failure\n");
	}
    
	struct dirent *pent;
	struct stat statbuf;
    
    DIR *pdir = opendir("sd:/levels/");

	if (!pdir){
		printf("opendir() failure; terminating\n");
	}

	while ((pent=readdir(pdir))!=NULL) {
		
        stat(pent->d_name,&statbuf);

		if(strcmp(".", pent->d_name) == 0 || strcmp("..", pent->d_name) == 0)
			continue;

        const char *ext = strrchr(pent->d_name, '.');
        if (ext && strcmp(ext, ".gmd") == 0) {
            snprintf(sd_level_paths[sd_level_count], MAX_PATH_LEN, "sd:/levels/%s", pent->d_name);
            
            sd_level_count++;
            if (sd_level_count >= MAX_SD_LEVELS) break;

            printf("Found GMD file: %s %llu\n", pent->d_name, pent->d_stat.st_size);
        }
	}

	closedir(pdir);
    
    // Read first gmd
    char *level_data = read_file(sd_level_paths[level_id], &outsize);
    if (level_data) {
        snprintf(current_level_name, 255, "%s", get_level_name(level_data));
        free(level_data);
    }

    while (1) {
        WPAD_ScanPads();

        if (!MP3Player_IsPlaying()) {
            MP3Player_PlayBuffer(menuLoop_mp3, menuLoop_mp3_size, NULL);
        }
                    
        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_1) {
            level_id = 0;
            level_mode ^= 1;
        }
        
        if (level_mode == 0) {
            if (main_levels()) break;
        } else {
            if (sdcard_levels()) break;
        }

        
        if (WPAD_ButtonsHeld(WPAD_CHAN_0) & WPAD_BUTTON_HOME) {
            return TRUE;
        }

        GRRLIB_Render();
    }

    return FALSE;
}

int sdcard_levels() {
    GRRLIB_FillScreen(RGBA(0, 127, 0, 255));
            
    GRRLIB_PrintfTTF(0, 400, font, "Press 1 to switch to main levels.", 30, RGBA(255,255,255,255));
    
    if (sd_level_count > 0) {
        char text[269];
        snprintf(text, 269, "%d - %s", level_id + 1, current_level_name);
        GRRLIB_PrintfTTF(0, 20, font, text, 30, RGBA(255,255,255,255));

        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_LEFT) {
            level_id--;
            if (level_id < 0) level_id = sd_level_count - 1; 
            
            memset(current_level_name, 0, 255);

            char *level_data = read_file(sd_level_paths[level_id], &outsize);
            if (level_data) {
                snprintf(current_level_name, 255, "%s", get_level_name(level_data));
                free(level_data);
            }
        }

        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_RIGHT) {
            level_id++;
            if (level_id >= sd_level_count) level_id = 0;
                
            memset(current_level_name, 0, 255);
            
            char *level_data = read_file(sd_level_paths[level_id], &outsize);
            if (level_data) {
                snprintf(current_level_name, 255, "%s", get_level_name(level_data));
                free(level_data);
            }
        }

        if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A) {
            // Start level
            gameRoutine = ROUTINE_GAME;
            MP3Player_Stop();
            PlayOgg(playSound_01_ogg, playSound_01_ogg_size, 0, OGG_ONE_TIME);
            for (int i = 0; i < 90; i++) {
                WPAD_ScanPads();
                VIDEO_WaitVSync();
            }
            
            char *level = read_file(sd_level_paths[level_id], &outsize);
            load_level(level);
            free(level);
            return 1;
        }
    } else {
        GRRLIB_PrintfTTF(0, 20, font, "Put levels in a folder called \"levels\"", 30, RGBA(255,255,255,255));
        GRRLIB_PrintfTTF(0, 45, font, "in the root folder of the sdcard", 30, RGBA(255,255,255,255));
        GRRLIB_PrintfTTF(0, 70, font, "and put levels exported with", 30, RGBA(255,255,255,255));
        GRRLIB_PrintfTTF(0, 95, font, "the mod \"GDShare\" in that folder.", 30, RGBA(255,255,255,255));
    }
    return 0;
}

int main_levels() {
    GRRLIB_FillScreen(RGBA(0, 127, 255, 255));
            
    GRRLIB_PrintfTTF(0, 400, font, "Press 1 to switch to SD card levels.", 30, RGBA(255,255,255,255));
    
    char text[255];
    snprintf(text, 255, "%d - %s", level_id + 1, levels[level_id].level_name);
    GRRLIB_PrintfTTF(0, 20, font, text, 30, RGBA(255,255,255,255));

    if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_LEFT) {
        level_id--;
        if (level_id < 0) level_id = LEVEL_NUM - 1; 
    }

    if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_RIGHT) {
        level_id++;
        if (level_id >= LEVEL_NUM) level_id = 0;
    }
    
    if (WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A) {
        // Start level
        gameRoutine = ROUTINE_GAME;
        MP3Player_Stop();
        PlayOgg(playSound_01_ogg, playSound_01_ogg_size, 0, OGG_ONE_TIME);
        for (int i = 0; i < 90; i++) {
            WPAD_ScanPads();
            VIDEO_WaitVSync();
        }
        
        load_level((char *) levels[level_id].data_ptr);
        return 1;
    }
    return 0;
}