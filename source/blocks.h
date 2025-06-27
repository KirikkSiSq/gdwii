#pragma once

#include <grrlib.h>
#include "level_loading.h"

#define MAX_OBJECT_LAYERS 4
#define BG_DIMENSIONS 4
#define BG_CHUNK (1024/BG_DIMENSIONS)

enum Objects {
    BASIC_BLOCK,
    CHECKER_EDGE,
    CHECKER_CORNER,
    CHECKER_INS_CORNER,
    CHECKER_FILLER,
    CHECKER_PILLAR_END,
    CHECKER_PILLAR,
    SPIKE,
    GROUND_SPIKE,
    BLUE_GRAVITY_PORTAL,
    YELLOW_GRAVITY_PORTAL,
    CUBE_PORTAL,
    SHIP_PORTAL,
    UNKNOWN,
    ROD_BIG,
    ROD_MEDIUM,
    ROD_SMALL,
    DECO_SPIKES_BIG,
    DECO_SPIKES_MEDIUM,
    DECO_SPIKES_SMALL,
    DECO_SPIKES_TINY,
    OBJECT_COUNT
};

enum ZLayers {
    LAYER_B3 = -1,
    LAYER_B2 = 1,
    LAYER_B1 = 3,
    LAYER_T1 = 5,
    LAYER_T2 = 7,
    LAYER_T3 = 9,
    LAYER_MAX
};

enum ColChannels {
    BG,
    GROUND,
    OBJ,
    BLACK,
    LBG,
    P1,
    P2,
    UNMODIFIABLE,
    COL_CHANNEL_COUNT
};

enum SpriteSheets {
    SHEET_BLOCKS,
    SHEET_PORTALS,
    SHEET_COUNT
};

struct ColorChannel {
    bool blending;
    u32 r:8;
    u32 b:8;
    u32 g:8;
};

struct ObjectLayer {
    u32 x_offset;
    u32 y_offset;
    u32 col_channel;
    s32 zlayer_offset;
    const u8 *texture;
};

typedef struct {
    struct ObjectLayer layers[MAX_OBJECT_LAYERS];
    s32 spritesheet_layer;
    s32 def_zlayer;
    s32 def_zorder;
    u32 num_layers;
} ObjectDefinition;

extern struct ColorChannel channels[COL_CHANNEL_COUNT];
extern const ObjectDefinition objects[];

void put_object_layer(GDObjectTyped *obj, float x, float y, GDObjectLayer *layer);
void draw_background(f32 x, f32 y);
void load_spritesheet();
void unload_spritesheet();
void handle_objects();