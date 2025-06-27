#include <grrlib.h>
#include "game_bg_png.h"
#include "blocks.h"
#include "level_loading.h"
#include "stdio.h"
#include "object_includes.h"

struct ColorChannel channels[COL_CHANNEL_COUNT] = {
    // BG
    {
        .r = 56,
        .g = 121,
        .b = 255,
        .blending = FALSE
    },
    // Ground
    {
        .r = 56,
        .g = 121,
        .b = 255,
        .blending = FALSE
    },
    // Obj
    {
        .r = 255,
        .g = 255,
        .b = 255,
        .blending = FALSE
    },
    // Black
    {
        .r = 0,
        .g = 0,
        .b = 0,
        .blending = FALSE
    },
    // LBG -- add later
    {
        .r = 0,
        .g = 0,
        .b = 0,
        .blending = FALSE
    },
    // P1
    {
        .r = 0,
        .g = 255,
        .b = 0,
        .blending = TRUE
    },
    // P2
    {
        .r = 0,
        .g = 255,
        .b = 255,
        .blending = TRUE
    },
    // Unmodifiable (white)
    {
        .r = 255,
        .g = 255,
        .b = 255,
        .blending = FALSE
    }
};

const ObjectDefinition unknown = {
    .layers = {},
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = 0,
    .def_zorder = 0,
    .num_layers = 0,  
};

const ObjectDefinition objects[] = {
    { // Basic block
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Checker edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_02_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Checker corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_03_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Checker inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_04_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Checker filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_05_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Checker pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_06_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Checker pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_07_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Ground spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Blue portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = -1,
                .texture = portal_01_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = portal_01_front_001_png
            }
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Yellow portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = -1,
                .texture = portal_02_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = portal_02_front_001_png
            }
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Cube portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = -1,
                .texture = portal_03_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = portal_03_front_001_png
            }
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Ship portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = -1,
                .texture = portal_04_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = portal_04_front_001_png
            }
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 14
    { // Big rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = rod_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Medium rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = rod_02_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Small rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = rod_03_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 1
    },
    { // Deco Spikes big 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes medium 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_02_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes small 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_03_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes tiny 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_04_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    // 1.0 TRIGGERS -- add later
    unknown, // 22
    unknown, // 23
    unknown, // 24
    unknown, // 25
    unknown, // 26
    unknown, // 27
    unknown, // 28
    unknown, // 29
    unknown, // 30
    unknown, // 31
    unknown, // 32
    unknown, // 33
    unknown, // 34
    { // Yellow pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = bump_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Yellow pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = ring_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    unknown, // 37
    unknown, // 38
    { // Half spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_02_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Slab
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = plank_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = plank_01_001_png
            },
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = chain_01_001_png
            }
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
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

void put_object_layer(GDObjectTyped *obj, float x, float y, GDObjectLayer *layer) {
    int obj_id = obj->id - 1;

    int layer_index = layer->layerNum;

    int x_flip_mult = (obj->flippedH ? -1 : 1);
    int y_flip_mult = (obj->flippedV ? -1 : 1);

    struct ObjectLayer *objectLayer = layer->layer;
    int x_offset = objectLayer->x_offset * x_flip_mult;
    int y_offset = objectLayer->y_offset * y_flip_mult;

    GRRLIB_texImg *image = object_images[obj_id][layer_index];

    int width = image->w;
    int height = image->h;

    int col_channel = objectLayer->col_channel;

    if (channels[col_channel].blending) {
        GRRLIB_SetBlend(GRRLIB_BLEND_ADD);
    } else {
        GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
    }
    
    u32 color = RGBA(channels[col_channel].r, channels[col_channel].g, channels[col_channel].b, 255);

    GRRLIB_SetHandle(image, (width/2) + x_offset, (height/2) + y_offset);
    GRRLIB_DrawImg(
        /* X        */ x + 6 - (width/2), 
        /* Y        */ y + 6 - (height/2),
        /* Texture  */ image, 
        /* Rotation */ obj->rotation, 
        /* Scale X  */ 0.73333333333333333333333333333333 * x_flip_mult * obj->scaling, 
        /* Scale Y  */ 0.73333333333333333333333333333333 * y_flip_mult * obj->scaling, 
        /* Color    */ color
    );
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
                bg, 0, 1, 1, RGBA(channels[BG].r, channels[BG].g, channels[BG].b, 255)
            );
        }
    }
}

extern float camera_x;
extern float camera_y;

void draw_all_object_layers() {
    for (int i = 0; i < layersArrayList->count; i++) {
        GDObjectTyped *obj = layersArrayList->layers[i]->obj;

        int obj_id = obj->id - 1;

        if (obj_id < OBJECT_COUNT) {
            GDObjectLayer *layer = layersArrayList->layers[i];

            float calc_x = (obj->x / 30.f * 44) - camera_x;
            float calc_y = VI_MAX_HEIGHT_NTSC - (obj->y / 30.f * 44) - camera_y;

            if (calc_x > -30 && calc_x < VI_MAX_WIDTH_NTSC) {        
                put_object_layer(obj, calc_x, calc_y, layer);
            }
        }
    }
}

void handle_objects() {
    draw_all_object_layers();
    
    // for (int i = 0; i < objectsArrayList->count; i++) {
    //     ;;
    // }
}