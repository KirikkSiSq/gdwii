#pragma once

#include "blocks.h"
#include "mem_pool.h"

typedef enum {
    GD_VAL_INT,
    GD_VAL_FLOAT,
    GD_VAL_BOOL,
    GD_VAL_STRING,
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
    int colorR;      // key 7
    int colorG;      // key 8
    int colorB;      // key 9
    float duration;  // key 10
    bool touchTriggered; // key 11
    int zsheetlayer; // no key has this, but used internally
    int zlayer;      // key 24
    int zorder;      // key 25
    char *text;      // key 31 (base64 string)
    float scaling;   // key 32
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

extern GDTypedObjectList *objectsArrayList;
extern GDObjectLayerList *layersArrayList;

#define LEVEL_POOL_SIZE 16 * 1024 * 1024

extern MemPool level_pool;
extern char level_pool_buffer[LEVEL_POOL_SIZE];

void free_typed_object_list(GDTypedObjectList *list);
void free_typed_object_array(GDObjectTyped **array, int count);
void load_level();