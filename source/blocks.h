#include <grrlib.h>

#define MAX_OBJECT_LAYERS 4
#define BG_DIMENSIONS 4
#define BG_CHUNK (1024/BG_DIMENSIONS)

enum Objects {
    BASIC_BLOCK,
    OBJECT_COUNT
};

struct ObjectLayer {
    u32 sheet_x;
    u32 sheet_y;
    u32 sheet_w;
    u32 sheet_h;
};

struct ObjectDefinition {
    struct ObjectLayer layers[MAX_OBJECT_LAYERS];
    u32 num_layers;
};

void put_object(u32 id, f32 x, f32 y, f32 angle);
void draw_background(f32 x, f32 y);
void load_spritesheet();
void unload_spritesheet();