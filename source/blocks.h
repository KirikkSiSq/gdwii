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
    OBJECT_COUNT
};

enum ColChannels {
    BG,
    GROUND,
    OBJ,
    BLACK,
    LBG,
    COL_CHANNEL_COUNT
};

enum SpriteSheets {
    SHEET_BLOCKS,
    SHEET_PORTALS,
    SHEET_COUNT
};

struct ObjectLayer {
    u32 x_offset;
    u32 y_offset;
    u32 col_channel;
    const u8 *texture;
};

struct ObjectDefinition {
    struct ObjectLayer layers[MAX_OBJECT_LAYERS];
    u32 num_layers;
};

void put_object(GDObjectTyped *obj, float x, float y);
void draw_background(f32 x, f32 y);
void load_spritesheet();
void unload_spritesheet();
void handle_objects();