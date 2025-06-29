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
    UNKNOWN_14,
    ROD_BIG,
    ROD_MEDIUM,
    ROD_SMALL,
    DECO_SPIKES_BIG,
    DECO_SPIKES_MEDIUM,
    DECO_SPIKES_SMALL,
    DECO_SPIKES_TINY,
    TRIGGER_FADE_NONE,
    TRIGGER_FADE_UP,
    TRIGGER_FADE_DOWN,
    TRIGGER_FADE_LEFT,
    TRIGGER_FADE_RIGHT,
    TRIGGER_FADE_SCALE_IN,
    TRIGGER_FADE_SCALE_OUT,
    BG_TRIGGER,
    GROUND_TRIGGER,
    START_POS,
    ENABLE_TRAIL,
    DISABLE_TRAIL,
    FAKE_STARTPOS,
    YELLOW_PAD,
    YELLOW_ORB,
    UNKNOWN_37,
    UNKNOWN_38,
    HALF_SPIKE,
    SLAB,
    CHAINS,
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
    LINE,
    BLACK,
    LBG,
    P1,
    P2,
    UNMODIFIABLE,
    COL_CHANNEL_COUNT
};

enum FadingEffects {
    FADE_NONE,
    FADE_UP,
    FADE_DOWN,
    FADE_RIGHT,
    FADE_LEFT,
    FADE_SCALE_IN,
    FADE_SCALE_OUT,
    FADE_COUNT
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
    float x_offset;
    float y_offset;
    u32 col_channel;
    s32 zlayer_offset;
    const u8 *texture;
};

typedef struct {
    struct ObjectLayer layers[MAX_OBJECT_LAYERS];
    s8 spritesheet_layer;
    s8 def_zlayer;
    s8 def_zorder;
    u8 num_layers;
    u8 is_trigger;
} ObjectDefinition;

extern struct ColorChannel channels[COL_CHANNEL_COUNT];
extern const ObjectDefinition objects[];

extern int layersDrawn;

void draw_all_object_layers();
void put_object_layer(GDObjectTyped *obj, float x, float y, GDObjectLayer *layer);
void draw_background(f32 x, f32 y);
void draw_ground(f32 x);
void load_spritesheet();
void unload_spritesheet();
void handle_objects();