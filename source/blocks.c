#include <grrlib.h>
#include "game_bg_png.h"
#include "blocks.h"
#include "level_loading.h"
#include "stdio.h"
#include "object_includes.h"

struct ObjectDefinition objects[] = {
    { // Basic block
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = square_01_001_png
            }
        },
        .num_layers = 1
    },
    { // Checker edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = square_02_001_png
            }
        },
        .num_layers = 1
    },
    { // Checker corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = square_03_001_png
            }
        },
        .num_layers = 1
    },
    { // Checker inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = square_04_001_png
            }
        },
        .num_layers = 1
    },
    { // Checker filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = square_05_001_png
            }
        },
        .num_layers = 1
    },
    { // Checker pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = square_06_001_png
            }
        },
        .num_layers = 1
    },
    { // Checker pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = square_07_001_png
            }
        },
        .num_layers = 1
    },
    { // Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .texture = spike_01_001_png
            }
        },
        .num_layers = 1
    },
    { // GroundSpike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 4,
                .col_channel = BLACK,
                .texture = pit_01_001_png
            }
        },
        .num_layers = 1
    }
};

// Prepare Graphics
GRRLIB_texImg *bg;
GRRLIB_texImg *object_images[OBJECT_COUNT][MAX_OBJECT_LAYERS]; 

void load_spritesheet() {
    // Load Textures 
    bg = GRRLIB_LoadTexturePNG(game_bg_png);

    for (s32 object = 0; object < OBJECT_COUNT; object++) {
        for (s32 layer = 0; layer < objects[object].num_layers; layer++) {
            printf("Loading texture of object %d layer %d\n", object, layer);

            GRRLIB_texImg *image = GRRLIB_LoadTexturePNG((const u8 *) objects[object].layers[layer].texture);
            if (image == NULL || image->data == NULL) {
                printf("Couldn't load texture of object %d layer %d\n", object, layer);
            } else {
                object_images[object][layer] = image;
            }
        }
    }
}

void unload_spritesheet() {
    // Free all memory used by textures.
    GRRLIB_FreeTexture(bg);
    
    for (s32 object = 0; object < OBJECT_COUNT; object++) {
        for (s32 layer = 0; layer < objects[object].num_layers; layer++) {
            GRRLIB_FreeTexture(object_images[object][layer]);
        }
    }
}

void put_object(GDObjectTyped *obj, float x, float y) {
    struct ObjectDefinition object = objects[obj->id - 1];

    for (u32 i = 0; i < object.num_layers; i++) {
        struct ObjectLayer layer = object.layers[i];
        int x_offset = layer.x_offset;
        int y_offset = layer.y_offset;

        GRRLIB_texImg *image = object_images[obj->id - 1][i];

        int width = image->w;
        int height = image->h;

        int col_channel = layer.col_channel;
        u32 color = (col_channel == BLACK) ? RGBA(0,0,0,255) : RGBA(255,255,255,255);

        GRRLIB_SetHandle(image, (width/2) + x_offset, (height/2) + y_offset);
        GRRLIB_DrawImg(
            /* X        */ x + 6 - (width/2), 
            /* Y        */ y + 6 - (height/2),
            /* Texture  */ image, 
            /* Rotation */ obj->rotation, 
            /* Scale X  */ 0.73333333333333333333333333333333 * (obj->flippedH ? -1 : 1) * obj->scaling, 
            /* Scale Y  */ 0.73333333333333333333333333333333 * (obj->flippedV ? -1 : 1) * obj->scaling, 
            /* Color    */ color
        );
    }
}

void draw_background(f32 x, f32 y) {
    for (s32 i = 0; i < BG_DIMENSIONS; i++) {
        for (s32 j = 0; j < BG_DIMENSIONS; j++) {
            u32 calc_x = i*BG_CHUNK;
            u32 calc_y = j*BG_CHUNK;
            GRRLIB_DrawPart(
                x + calc_x, y + calc_y, 
                calc_x, calc_y,
                BG_CHUNK, BG_CHUNK,
                bg, 0, 1, 1, RGBA(56, 121, 255, 255)
            );
        }
    }
}

extern float camera_x;
extern float camera_y;

void handle_objects() {
    for (int i = 0; i < objectsArrayList->count; i++) {
        GDObjectTyped *obj = objectsArrayList->objects[i];

        float calc_x = (obj->x / 30.f * 44) - camera_x;
        float calc_y = VI_MAX_HEIGHT_NTSC - (obj->y / 30.f * 44) - camera_y;
        
        int object_id = obj->id - 1;

        if (object_id < OBJECT_COUNT) {
            if (calc_x > -30 && calc_x < VI_MAX_WIDTH_NTSC) {
                put_object(obj, calc_x, calc_y);
            }
        }
    }
}