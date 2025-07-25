#pragma once

typedef enum {
    GD_VAL_INT,
    GD_VAL_FLOAT,
    GD_VAL_BOOL,
    GD_VAL_UNKNOWN
} GDValueType;

typedef union {
    int i;
    float f;
    bool b;
    char *s; // For base64 text strings or others
} GDValue;

typedef struct {
    int id;          // key 1
    float x;         // key 2
    float y;         // key 3
    bool flippedH;   // key 4
    bool flippedV;   // key 5
    float rotation;  // key 6
    u8 trig_colorR;      // key 7
    u8 trig_colorG;      // key 8
    u8 trig_colorB;      // key 9
    float trig_duration;  // key 10
    bool touchTriggered; // key 11
    int zsheetlayer; // no key has this, but used internally
    int zlayer;      // key 24
    int zorder;      // key 25

    int random; // random number assigned to this object
    bool activated; // if it has been activated
    unsigned int hitbox_counter; // number of times the player has entered the hitbox
    bool collided; // if the object just started being touched
    float ampl_scaling; // the amplitude scaling for pulsing objects
    u8 transition_applied;
} GDObjectTyped;

typedef struct {
    int keys[20];
    GDValue values[20];
    GDValueType types[20];
    int propCount;
} GDObject;

typedef struct {
    GDObject *objects;
    int objectCount;
} GDObjectList;

typedef struct {
    int count;
    GDObjectTyped **objects;
} GDTypedObjectList;

typedef struct {
    GDObjectTyped *obj;
    int originalIndex;
} GDObjectSortable;

typedef struct {
    GDObjectTyped *obj;
    struct ObjectLayer *layer;
    int layerNum;
} GDObjectLayer;

typedef struct {
    GDObjectLayer *layer;
    int originalIndex;
    int layerNum;
} GDLayerSortable;

typedef struct {
    int count;
    GDObjectLayer **layers;
} GDObjectLayerList;

typedef struct {
    int fromRed;
    int fromGreen;
    int fromBlue;
    int playerColor;
    bool blending;
    int channelID;
    float fromOpacity;
    bool toggleOpacity;
    int inheritedChannelID;
    int hsv; // convert to struct
    int toRed;
    int toGreen;
    int toBlue;
    float deltaTime;
    float toOpacity;
    float duration;
    bool copyOpacity;
} GDColorChannel;

struct LoadedLevelInfo {
    float last_obj_x;
    float wall_x;
    int pulsing_type;
    int song_id;
    bool completing;
};

#define SECTION_HASH_SIZE 600

#define SECTION_SIZE 128
#define GFX_SECTION_SIZE 128

typedef struct Section {
    GDObjectTyped **objects;
    int object_count;
    int object_capacity;

    int x, y; // Section coordinates
    struct Section *next; // For chaining in hash map
} Section;

typedef struct GFXSection {
    GDLayerSortable **layers;
    int layer_count;
    int layer_capacity;

    int x, y; // Section coordinates
    struct GFXSection *next; // For chaining in hash map
} GFXSection;

extern Section *section_hash[SECTION_HASH_SIZE];
extern GFXSection *section_gfx_hash[SECTION_HASH_SIZE];
unsigned int section_hash_func(int x, int y);
Section *get_or_create_section(int x, int y);
GFXSection *get_or_create_gfx_section(int x, int y);
void free_sections(void);

char *get_level_name(char *data_ptr);
int compare_sortable_layers(const void *a, const void *b);

extern struct LoadedLevelInfo level_info;

extern GDTypedObjectList *objectsArrayList;
extern GDObjectLayerList *layersArrayList;

extern GDLayerSortable gfx_player_layer;

void free_typed_object_list(GDTypedObjectList *list);
void free_typed_object_array(GDObjectTyped **array, int count);
void load_level(char *data);
void unload_level();
void reload_level();
void reset_color_channels();
void set_color_channels();