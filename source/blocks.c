#include <grrlib.h>
#include "GJ_GameSheet_png.h"
#include "game_bg_png.h"
#include "blocks.h"

struct ObjectDefinition objects[] = {
    { // Basic block
        .layers = {
            {
                .sheet_x = 156,
                .sheet_y = 732,
                .sheet_w = 32,
                .sheet_h = 32
            }
        },
        .num_layers = 1
    }
};

// Prepare Graphics
GRRLIB_texImg *bg;
GRRLIB_texImg *GFX_Sheet;

void load_spritesheet() {
    // Load Textures
    GFX_Sheet = GRRLIB_LoadTexturePNG(GJ_GameSheet_png);
    bg = GRRLIB_LoadTexturePNG(game_bg_png);
}

void unload_spritesheet() {
    // Free all memory used by textures.
    GRRLIB_FreeTexture(GFX_Sheet);
    GRRLIB_FreeTexture(bg);
}

void put_object(u32 id, f32 x, f32 y, f32 angle) {
    struct ObjectDefinition object = objects[id];

    for (u32 i = 0; i < object.num_layers; i++) {
        struct ObjectLayer layer = object.layers[i];
        
        GRRLIB_SetHandle(GFX_Sheet, 512, 512);
        GRRLIB_DrawPart(x + 6, y + 6, layer.sheet_x, layer.sheet_y, layer.sheet_w, layer.sheet_h, GFX_Sheet, angle, 1.375, 1.375, RGBA(255, 255, 255, 255));
    }
}

void draw_background(f32 x, f32 y) {
    for (s32 i = 0; i < BG_DIMENSIONS; i++) {
        for (s32 j = 0; j < BG_DIMENSIONS; j++) {
            u32 calc_x = i*BG_CHUNK;
            u32 calc_y = j*BG_CHUNK;
            GRRLIB_DrawPart(x + calc_x, y + calc_y, 
            calc_x, calc_y,
            BG_CHUNK, BG_CHUNK,
            bg, 0, 1, 1, RGBA(56, 121, 255, 255));
        }
    }
}