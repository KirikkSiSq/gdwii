#pragma once

#include <grrlib.h>
#include "player.h"
#include "math.h"
#include "level_loading.h"

#define MAX_OBJECT_LAYERS 4

#define BACKGROUND_SCALE 0.9
#define BG_DIMENSIONS 4
#define BG_CHUNK ((1024/BG_DIMENSIONS) * BACKGROUND_SCALE)

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

    D_CLOUD_BIG,
    D_CLOUD_SMALL,

    PULSING_CIRCLE,
    PULSING_CIRCUNFERENCE,
    PULSING_HEART,
    PULSING_DIAMOND,
    PULSING_STAR,

    TRIGGER_FADE_CIRCLE,
    TRIGGER_FADE_LEFT_SEMICIRCLE,
    TRIGGER_FADE_RIGHT_SEMICIRCLE,
    TRIGGER_FADE_INWARDS,
    TRIGGER_FADE_OUTWARDS,

    PULSING_NOTE,

    WAVY_GROUND_SPIKE,

    S13_SLAB,
    S13_CORNER,
    S13_INSIDE_CORNER,
    S13_RIGHT_EDGE,
    S13_LEFT_EDGE,

    BLUE_PAD,

    S13_UNIT,

    B13_FULL,
    B13_EDGE,
    B13_CORNER,
    B13_INS_CORNER,
    B13_FILLER,
    B13_PILLAR_END,
    B13_PILLAR,

    B14_FULL,
    B14_EDGE,
    B14_CORNER,
    B14_INS_CORNER, // Actually unused slot in the game
    B14_FILLER,
    B14_PILLAR_END,
    B14_PILLAR,

    CHECKER_FULL,
    BLUE_ORB,

    SAW_DECO_BIG,
    SAW_DECO_MEDIUM,
    SAW_DECO_SMALL,

    SAW_BIG,
    SAW_MEDIUM,

    BLACK_FULL,
    BLACK_EDGE,
    BLACK_CORNER,
    BLACK_INS_CORNER,
    BLACK_FILLER,
    BLACK_PILLAR_END,
    BLACK_PILLAR,

    SAW_DECO_TINY,
    SAW_SMALL,

    BIG_PORTAL,
    UNKNOWN_100,
    MINI_PORTAL,
    UNKNOWN_102,

    MEDIUM_SPIKE,

    LINE_TRIGGER,
    OBJ_TRIGGER,

    C15_P2_BIG,
    C15_P2_SMALL,
    UNKNOWN_108,
    UNKNOWN_109,
    C15_P1_SMALL,
    
    UFO_PORTAL,

    UNKNOWN_112,

    SQUARE_SPIKES_BIG,
    SQUARE_SPIKES_MEDIUM,
    SQUARE_SPIKES_SMALL,

    BRICKS_FULL,
    BRICKS_EDGE,
    BRICKS_CORNER,
    BRICKS_INS_CORNER,
    BRICKS_FILLER,
    BRICKS_PILLAR_END,
    BRICKS_PILLAR,

    THORN_01,
    THORN_02,
    THORN_03,
    THORN_04,
    THORN_05,
    THORN_06,

    CLOUD_DECO_MEDIUM,
    CLOUD_DECO_BIG,
    CLOUD_DECO_SMALL,

    D_ARROW,
    D_EXMARK,
    DIAMOND_DECO_SMALL,
    BUSH_GROUND_SPIKE,
    D_QMARK,
    
    WHEEL_BIG,
    WHEEL_MEDIUM,
    WHEEL_SMALL,

    PINK_PAD,
    PINK_ORB,

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
    JUMP_YELLOW_ORB,
    JUMP_BLUE_PAD,
    JUMP_BLUE_ORB,
    JUMP_PINK_PAD,
    JUMP_PINK_ORB,
    JUMP_TYPES_COUNT
};

enum ColChannels {
    BG = 1000,
    GROUND,
    LINE,
    THREEDL,
    OBJ,
    P1,
    P2,
    LBG,
    OBJ_BLENDING,
    G2,
    BLACK,
    WHITE,
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
    FADE_INWARDS,
    FADE_OUTWARDS,
    FADE_CIRCLE_LEFT,
    FADE_CIRCLE_RIGHT,
    FADE_UP_SLOW,
    FADE_DOWN_SLOW,
    FADE_UP_STATIONARY,
    FADE_DOWN_STATIONARY,
    FADE_COUNT
};

enum SpriteSheets {
    SHEET_BLOCKS,
    SHEET_PORTALS,
    SHEET_COUNT
};

struct ColorChannel {
    Color color;
    bool blending;
    int copy_color_id;
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
    u8 is_saw;
    ObjectHitbox hitbox;
} ObjectDefinition;

#define BLOCK_SIZE_PX 44.f
#define SCALE (BLOCK_SIZE_PX / 30.0f)

#define MAX_VISIBLE_LAYERS 4096

extern const struct ObjectLayer player_layer;
extern int current_fading_effect;
extern bool p1_trail;

extern struct ColorChannel channels[COL_CHANNEL_COUNT];
extern const ObjectDefinition objects[];

extern GRRLIB_texImg *object_images[OBJECT_COUNT][MAX_OBJECT_LAYERS];

extern struct TriggerBuffer trigger_buffer[COL_CHANNEL_COUNT];

extern int layersDrawn;

extern int beat_pulse;

extern GRRLIB_texImg *prev_tex;

void update_beat();
void draw_end_wall();

void get_fade_vars(GDObjectTyped *obj, float x, int *fade_x, int *fade_y, float *fade_scale);
int get_fade_value(float x, int right_edge);

void handle_special_hitbox(Player *player, GDObjectTyped *obj, ObjectHitbox *hitbox);
float get_mirror_x(float x, float factor);

void draw_all_object_layers();
void draw_background(f32 x, f32 y);
void draw_ground(f32 x, bool is_ceiling);
void load_spritesheet();
void unload_spritesheet();
void handle_objects();