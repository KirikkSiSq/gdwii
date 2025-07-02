#include <grrlib.h>
#include "game_bg_png.h"
#include "game_ground_png.h"
#include "objects.h"
#include "level_loading.h"
#include "stdio.h"
#include "object_includes.h"
#include "ground_line_png.h"
#include "main.h"
#include "math.h"
#include <math.h>

#include "particles.h"
#include "particle_png.h"

struct ColorChannel channels[COL_CHANNEL_COUNT] = {
    // BG
    {
        .color = {
            .r = 56,
            .g = 121,
            .b = 255,
        },
        .blending = FALSE
    },
    // Ground
    {
        .color = {
            .r = 56,
            .g = 121,
            .b = 255,
        },
        .blending = FALSE
    },
    // Obj
    {
        .color = {
            .r = 255,
            .g = 255,
            .b = 255,
        },
        .blending = FALSE
    },
    // Line
    {
        .color = {
            .r = 255,
            .g = 255,
            .b = 255,
        },
        .blending = TRUE
    },
    // Black
    {
        .color = {
            .r = 0,
            .g = 0,
            .b = 0,
        },
        .blending = FALSE
    },
    // LBG -- add later
    {
        .color = {
            .r = 0,
            .g = 0,
            .b = 0,
        },
        .blending = FALSE
    },
    // P1
    {
        .color = {
            .r = 0,
            .g = 255,
            .b = 0,
        },
        .blending = TRUE
    },
    // P2
    {
        .color = {
            .r = 0,
            .g = 255,
            .b = 255,
        },
        .blending = TRUE
    },
    // Unmodifiable (white)
    {
        .color = {
            .r = 255,
            .g = 255,
            .b = 255,
        },
        .blending = FALSE
    }
};


const ObjectHitbox gamemode_portal_hitbox = {
    .width = 34,
    .height = 86,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox gravity_portal_hitbox = {
    .width = 25,
    .height = 75,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox no_hitbox = {
    .width = 0,
    .height = 0,
    .type = HITBOX_NONE
};

const ObjectDefinition unknown = {
    .layers = {},
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = 0,
    .def_zorder = 0,
    .num_layers = 0,  
};

const ObjectDefinition trigger = {
    .layers = {},
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = 0,
    .def_zorder = 0,
    .num_layers = 0,  
    .is_trigger = TRUE
};


const struct ObjectLayer player_layer = {
    .col_channel = UNMODIFIABLE,
    .zlayer_offset = 0,
    .texture = NULL
};

const ObjectDefinition player_object = {
    .layers = { player_layer },
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = LAYER_T1-1,
    .def_zorder = 9999999,
    .num_layers = 1,  
    .is_trigger = TRUE
};

const ObjectDefinition objects[] = {
    player_object,
    { // Basic block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
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
        .hitbox = no_hitbox,
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
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_07_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_01_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
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
        .hitbox = {
            .width = 9,
            .height = 10.8,
            .type = HITBOX_SPIKE
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
        .hitbox = gravity_portal_hitbox,
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
        .hitbox = gravity_portal_hitbox,
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
        .hitbox = gamemode_portal_hitbox,
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
        .hitbox = gamemode_portal_hitbox,
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
        .hitbox = no_hitbox,
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
        .hitbox = no_hitbox,
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
        .hitbox = no_hitbox,
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
        .hitbox = no_hitbox,
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
        .hitbox = no_hitbox,
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
        .hitbox = no_hitbox,
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
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    // 1.0 TRIGGERS -- add later
    trigger, // 22
    trigger, // 23
    trigger, // 24
    trigger, // 25
    trigger, // 26
    trigger, // 27
    trigger, // 28
    trigger, // 29
    trigger, // 30
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
        .hitbox = {
            .width = 25,
            .height = 4,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Yellow orb
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = UNMODIFIABLE,
                .zlayer_offset = 0,
                .texture = ring_01_001_png
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
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
                .texture = spike_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_02_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 5.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_01_glow_001_png
            },
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
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
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
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
};

// Prepare Graphics
GRRLIB_texImg *bg;
GRRLIB_texImg *ground;
GRRLIB_texImg *ground_line;
GRRLIB_texImg *object_images[OBJECT_COUNT][MAX_OBJECT_LAYERS]; 

int current_fading_effect = FADE_NONE;

struct TriggerBuffer trigger_buffer[COL_CHANNEL_COUNT];

void load_spritesheet() {
    // Load Textures 
    bg = GRRLIB_LoadTexturePNG(game_bg_png);
    ground = GRRLIB_LoadTexturePNG(game_ground_png);
    ground_line = GRRLIB_LoadTexturePNG(ground_line_png);
    particleTex = GRRLIB_LoadTexturePNG(particle_png);

    for (s32 object = 1; object < OBJECT_COUNT; object++) {
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

    load_icons();
}

void unload_spritesheet() {
    // Free all memory used by textures.
    GRRLIB_FreeTexture(bg);
    GRRLIB_FreeTexture(ground);
    GRRLIB_FreeTexture(ground_line);
    GRRLIB_FreeTexture(particleTex);

    for (s32 object = 0; object < OBJECT_COUNT; object++) {
        for (s32 layer = 0; layer < objects[object].num_layers; layer++) {
            GRRLIB_FreeTexture(object_images[object][layer]);
        }
    }
    
    unload_icons();
}

int get_fade_value(float x, int right_edge) {
    #define FADE_WIDTH 60
    if (x < 0 || x > right_edge)
        return 0;
    else if (x < FADE_WIDTH)
        return (int)(255.0f * (x / FADE_WIDTH));
    else if (x > right_edge - FADE_WIDTH)
        return (int)(255.0f * ((right_edge - x) / FADE_WIDTH));
    else
        return 255;
}

int get_xy_fade_offset(float x, int right_edge) {
    int fade = get_fade_value(x, right_edge);
    return (255 - fade) / 2;
}

float get_in_scale_fade(float x, int right_edge) {
    int fade = get_fade_value(x, right_edge);
    return (fade / 255.f);
}

float get_out_scale_fade(float x, int right_edge) {
    int fade = 255 - get_fade_value(x, right_edge);
    return 1 + ((fade / 255.f) / 2);
}

void put_object_layer(GDObjectTyped *obj, float x, float y, GDObjectLayer *layer) {
    int obj_id = obj->id;

    int layer_index = layer->layerNum;

    int x_flip_mult = (obj->flippedH ? -1 : 1);
    int y_flip_mult = (obj->flippedV ? -1 : 1);

    struct ObjectLayer *objectLayer = layer->layer;
    float x_offset = objectLayer->x_offset * x_flip_mult;
    float y_offset = objectLayer->y_offset * y_flip_mult;

    GRRLIB_texImg *image = object_images[obj_id][layer_index];

    int width = image->w;
    int height = image->h;

    int col_channel = objectLayer->col_channel;

    if (channels[col_channel].blending) {
        GRRLIB_SetBlend(GRRLIB_BLEND_ADD);
    } else {
        GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
    }
    
    int opacity = get_fade_value(x, screenWidth);
    
    u32 color = RGBA(channels[col_channel].color.r, channels[col_channel].color.g, channels[col_channel].color.b, opacity);
        
    float angle_rad = obj->rotation * (M_PI / 180.0f); // Convert degrees to radians
    float cos_a = cosf(angle_rad);
    float sin_a = sinf(angle_rad);

    float x_off_rot = x_offset * cos_a - y_offset * sin_a;
    float y_off_rot = x_offset * sin_a + y_offset * cos_a;

    int fade_x = 0;
    int fade_y = 0;

    float fade_scale = 1.f;

    switch (current_fading_effect) {
        case FADE_NONE:
            break;
        case FADE_UP:
            fade_y = get_xy_fade_offset(x, screenWidth);
            break;
        case FADE_DOWN:
            fade_y = -get_xy_fade_offset(x, screenWidth);
            break;
        case FADE_RIGHT:
            fade_x = get_xy_fade_offset(x, screenWidth);
            break;
        case FADE_LEFT:
            fade_x = -get_xy_fade_offset(x, screenWidth);
            break;
        case FADE_SCALE_IN:
            fade_scale = get_in_scale_fade(x, screenWidth);
            break;
        case FADE_SCALE_OUT:
            fade_scale = get_out_scale_fade(x, screenWidth);
            break;
    }

    GRRLIB_SetHandle(image, (width/2), (height/2));
    GRRLIB_DrawImg(
        /* X        */ x + 6 - (width/2) + x_off_rot + fade_x,
        /* Y        */ y + 6 - (height/2) + y_off_rot + fade_y,
        /* Texture  */ image, 
        /* Rotation */ obj->rotation, 
        /* Scale X  */ 0.73333333333333333333333333333333 * x_flip_mult * fade_scale, 
        /* Scale Y  */ 0.73333333333333333333333333333333 * y_flip_mult * fade_scale, 
        /* Color    */ color
    );
}

void draw_background_image(f32 x, f32 y, bool vflip) {
    for (s32 i = 0; i < BG_DIMENSIONS; i++) {
        u32 calc_x = i*BG_CHUNK;
        for (s32 j = 0; j < BG_DIMENSIONS; j++) {
            u32 calc_y = j*BG_CHUNK;
            
            GRRLIB_SetHandle(bg, 512, 512);
            GRRLIB_DrawPart(
                x + calc_x, 
                y + (vflip ? 768 - calc_y : calc_y), 
                calc_x, 
                calc_y,
                BG_CHUNK, 
                BG_CHUNK,
                bg, 0, 1, (vflip ? -1 : 1), RGBA(channels[BG].color.r, channels[BG].color.g, channels[BG].color.b, 255)
            );
        }
    }
}

void draw_background(f32 x, f32 y) {
    float big_calc_y = positive_fmod(y, 2048);

    float calc_x = positive_fmod(x, 1024);
    float calc_y = positive_fmod(y, 1024);

    int flip = big_calc_y >= 1024;

    draw_background_image(-calc_x, -calc_y, FALSE ^ flip);

    if (-calc_x + 1024 < screenWidth) {
        draw_background_image(-calc_x + 1024, -calc_y, FALSE ^ flip);
    }

    if (-calc_y + 1024 < screenHeight) {
        draw_background_image(-calc_x, -calc_y + 1024, TRUE ^ flip);
    }  

    if (-calc_y + 1024 < screenHeight && -calc_x + 1024 < screenWidth) {
        draw_background_image(-calc_x + 1024, -calc_y + 1024, TRUE ^ flip);
    }
}

#define GROUND_SIZE 176 // pixels
#define LINE_SCALE 0.5f

void draw_ground(f32 y, bool is_ceiling) {
    int mult = (is_ceiling ? -1 : 1);

    float calc_x = 0 - positive_fmod(render_state->camera_x * SCALE, GROUND_SIZE);
    float calc_y = screenHeight - ((y - render_state->camera_y) * SCALE);

    for (float i = -GROUND_SIZE; i < screenWidth + GROUND_SIZE; i += GROUND_SIZE) {
        GRRLIB_DrawImg(
            calc_x + i + 6, 
            calc_y + 6,    
            ground,
            0, 1.375, 1.375 * mult,
            RGBA(channels[GROUND].color.r, channels[GROUND].color.g, channels[GROUND].color.b, 255) 
        );
    }

    if (channels[LINE].blending) {
        GRRLIB_SetBlend(GRRLIB_BLEND_ADD);
    }

    int line_width = ground_line->w;
    
    GRRLIB_DrawImg(
        (screenWidth / 2) - (line_width / (2 / LINE_SCALE)),
        calc_y + (is_ceiling ? 4 : 6),
        ground_line,
        0, LINE_SCALE, 0.75,
        RGBA(channels[LINE].color.r, channels[LINE].color.g, channels[LINE].color.b, 255)
    );
    
    if (channels[LINE].blending) {
        GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
    }
}

int layersDrawn = 0;

void draw_all_object_layers() {
    if (layersArrayList == NULL) return;

    float screen_x_max = screenWidth + 90.0f;
    float screen_y_max = screenHeight + 90.0f;

    for (int i = 0; i < layersArrayList->count; i++) {
        GDObjectTyped *obj = layersArrayList->layers[i]->obj;

        int obj_id = obj->id;

        if (obj_id == PLAYER_OBJECT) {
            draw_particles(CUBE_DRAG);
            draw_particles(SHIP_TRAIL);
            draw_particles(HOLDING_SHIP_TRAIL);
            draw_player();
            draw_particles(SHIP_DRAG);
        } else if (obj_id < OBJECT_COUNT) {
            float calc_x = ((obj->x - render_state->camera_x) * SCALE);
            float calc_y = screenHeight - ((obj->y - render_state->camera_y) * SCALE);

            if (calc_x > -90 && calc_x < screen_x_max) {        
                if (calc_y > -90 && calc_y < screen_y_max) {        
                    layersDrawn++;
                    
                    GDObjectLayer *layer = layersArrayList->layers[i];
                    put_object_layer(obj, calc_x, calc_y, layer);
                }
            }
        }
    }
}

void handle_col_triggers() {
    for (int chan = 0; chan < COL_CHANNEL_COUNT; chan++) {
        struct TriggerBuffer *buffer = &trigger_buffer[chan];

        if (buffer->active) {
            Color lerped_color;

            if (buffer->seconds > 0) {
                float multiplier = buffer->time_run / buffer->seconds;
                lerped_color = color_lerp(buffer->old_color, buffer->new_color, multiplier);
            } else {
                lerped_color = buffer->new_color;
            }

            channels[chan].color = lerped_color;

            buffer->time_run += dt;

            if (buffer->time_run > buffer->seconds) {
                buffer->active = FALSE;
            }
        }
    }
}

void handle_triggers(int i) {
    GDObjectTyped *obj = objectsArrayList->objects[i];

    int obj_id = obj->id;

    struct TriggerBuffer *buffer = NULL;

    if (objects[obj_id].is_trigger) {
        if (obj->x < gameplay_state->player.x && obj->x > gameplay_state->old_player.x) {
            switch (obj_id) {
                case TRIGGER_FADE_NONE:
                    current_fading_effect = FADE_NONE;
                    break;
                    
                case TRIGGER_FADE_UP:
                    current_fading_effect = FADE_UP;
                    break;
                    
                case TRIGGER_FADE_DOWN:
                    current_fading_effect = FADE_DOWN;
                    break;
                    
                case TRIGGER_FADE_RIGHT:
                    current_fading_effect = FADE_RIGHT;
                    break;
                    
                case TRIGGER_FADE_LEFT:
                    current_fading_effect = FADE_LEFT;
                    break;
                    
                case TRIGGER_FADE_SCALE_IN:
                    current_fading_effect = FADE_SCALE_IN;
                    break;
                    
                case TRIGGER_FADE_SCALE_OUT:
                    current_fading_effect = FADE_DOWN;
                    break;

                case BG_TRIGGER:
                    buffer = &trigger_buffer[BG];
                    buffer->active = TRUE;
                    buffer->old_color = channels[BG].color;
                    buffer->new_color.r = obj->trig_colorR;
                    buffer->new_color.g = obj->trig_colorG;
                    buffer->new_color.b = obj->trig_colorB;
                    buffer->seconds = obj->trig_duration;
                    buffer->time_run = 0;
                    break;
                
                case GROUND_TRIGGER:
                    buffer = &trigger_buffer[GROUND];
                    buffer->active = TRUE;
                    buffer->old_color = channels[GROUND].color;
                    buffer->new_color.r = obj->trig_colorR;
                    buffer->new_color.g = obj->trig_colorG;
                    buffer->new_color.b = obj->trig_colorB;
                    buffer->seconds = obj->trig_duration;
                    buffer->time_run = 0;
                    break;
            }
        }
    }
}

void handle_objects() {
    for (int i = 0; i < objectsArrayList->count; i++) {
        handle_triggers(i);
    }
    handle_col_triggers();
}