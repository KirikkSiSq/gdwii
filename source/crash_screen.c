#include <ogc/system.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <grrlib.h>

#include "pusab_ttf.h"

void crash_handler(frame_context *ctx) {
    struct GRRLIB_Font *font = GRRLIB_LoadTTF(pusab_ttf, pusab_ttf_size);

    while (1) {
        GRRLIB_FillScreen(0x000000FF); // Clear black

        int y = 40;
        char line[128];

        // Header
        GRRLIB_PrintfTTF(40, y, font, "!! CRASH DETECTED !!", 28, 0xFF0000FF);
        y += 40;

        // Exception info
        snprintf(line, sizeof(line), "Exception: %d", ctx->EXCPT_Number);
        GRRLIB_PrintfTTF(40, y, font, line, 20, 0xFFFFFFFF);
        y += 30;

        snprintf(line, sizeof(line), "PC (SRR0): 0x%08X", ctx->SRR0);
        GRRLIB_PrintfTTF(40, y, font, line, 20, 0xFFFFFFFF);
        y += 30;

        snprintf(line, sizeof(line), "LR: 0x%08X", ctx->LR);
        GRRLIB_PrintfTTF(40, y, font, line, 20, 0xFFFFFFFF);
        y += 30;

        // Display a few GPRs (optional: print all 32 if you want)
        for (int i = 0; i < 8; i++) {
            snprintf(line, sizeof(line), "GPR[%2d]: 0x%08X", i, ctx->GPR[i]);
            GRRLIB_PrintfTTF(40, y, font, line, 20, 0xFFFFFFFF);
            y += 24;
        }

        GRRLIB_PrintfTTF(40, y + 20, font, "Game has crashed. Press POWER to exit.", 20, 0xFFFFFF00);

        GRRLIB_Render();
    }
}