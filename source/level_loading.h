#pragma once

#include "objects.h"

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
    int zsheetlayer; // no key has this, but used internally
    int zlayer;      // key 24
    int zorder;      // key 25
    int random; // random number assigned to this object
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

extern int pulsing_type;

extern GDTypedObjectList *objectsArrayList;
extern GDObjectLayerList *layersArrayList;

void free_typed_object_list(GDTypedObjectList *list);
void free_typed_object_array(GDObjectTyped **array, int count);
void load_level();
void unload_level();
void reload_level();
void set_color_channels();