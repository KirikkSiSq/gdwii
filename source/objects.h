#pragma once

#include <grrlib.h>
#include "level_loading.h"
#include "player.h"

#define MAX_OBJECT_LAYERS 4
#define BG_DIMENSIONS 4
#define BG_CHUNK (1024/BG_DIMENSIONS)

enum Objects {
    PLAYER_OBJECT,
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
    UNKNOWN_42,
    UNKNOWN_43,
    UNKNOWN_44,
    ORANGE_MIRROR_PORTAL,
    BLUE_MIRROR_PORTAL,
    BALL_PORTAL,
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

enum JumpType {
    JUMP_YELLOW_PAD,
    JUMP_YELLOW_ORB
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

typedef struct {
    u8 r;
    u8 b;
    u8 g;
} Color;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} ColorAlpha;

struct ColorChannel {
    Color color;
    bool blending;
};

struct TriggerBuffer {
    bool active;
    Color old_color;
    Color new_color;
    float seconds;
    float time_run;
};

enum HitboxTypes {
    HITBOX_NONE,
    HITBOX_SOLID,
    HITBOX_SPIKE,
    HITBOX_SPECIAL,
    HITBOX_TYPES
};

typedef struct {
    float width;
    float height;
    float radius;
    bool is_circular;
    int type;
} ObjectHitbox;

struct ObjectLayer {
    float x_offset;
    float y_offset;
    u32 col_channel;
    s32 zlayer_offset;
    const u8 *texture;
};

typedef struct {
    struct ObjectLayer layers[MAX_OBJECT_LAYERS];
    int spritesheet_layer;
    int def_zlayer;
    int def_zorder;
    u8 num_layers;
    u8 is_trigger;
    ObjectHitbox hitbox;
} ObjectDefinition;

#define BLOCK_SIZE_PX 44.f
#define SCALE (BLOCK_SIZE_PX / 30.0f)

extern const struct ObjectLayer player_layer;
extern int current_fading_effect;

extern struct ColorChannel channels[COL_CHANNEL_COUNT];
extern const ObjectDefinition objects[];

extern GRRLIB_texImg *object_images[OBJECT_COUNT][MAX_OBJECT_LAYERS];

extern struct TriggerBuffer trigger_buffer[COL_CHANNEL_COUNT];

extern int layersDrawn;

void get_fade_vars(float x, int *fade_x, int *fade_y, float *fade_scale);
int get_fade_value(float x, int right_edge);

void handle_special_hitbox(Player *player, GDObjectTyped *obj, ObjectHitbox *hitbox);
float get_mirror_x(float x, float factor);

void draw_all_object_layers();
void put_object_layer(GDObjectTyped *obj, float x, float y, GDObjectLayer *layer);
void draw_background(f32 x, f32 y);
void draw_ground(f32 x, bool is_ceiling);
void load_spritesheet();
void unload_spritesheet();
void handle_objects();