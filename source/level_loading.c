#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <stdbool.h>

#include "objects.h"
#include "level_loading.h"

#include "test_gmd.h"

#include "mem_pool.h"

MemPool level_pool;
char level_pool_buffer[LEVEL_POOL_SIZE];

char *extract_base64(const char *data) {
    const char *start_tag = "<k>k4</k><s>";
    const char *end_tag = "</s>";

    printf("Searching for base64 data in input...\n");
    char *start = strstr(data, start_tag);
    if (!start) {
        printf("Could not find start tag '%s'\n", start_tag);
        return NULL;
    }
    start += strlen(start_tag);

    char *end = strstr(start, end_tag);
    if (!end) {
        printf("Could not find end tag '%s'\n", end_tag);
        return NULL;
    }

    int len = end - start;
    char *b64 = mempool_alloc(&level_pool, len + 1);
    strncpy(b64, start, len);
    b64[len] = '\0';
    return b64;
}

int b64_char(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    if ('0' <= c && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

void fix_base64_url(char *b64) {
    for (int i = 0; b64[i]; i++) {
        if (b64[i] == '-') b64[i] = '+';
        else if (b64[i] == '_') b64[i] = '/';
    }
}

int base64_decode(const char *in, unsigned char *out) {
    int len = 0;
    for (int i = 0; in[i] && in[i+1] && in[i+2] && in[i+3]; i += 4) {
        int a = b64_char(in[i]);
        int b = b64_char(in[i+1]);
        int c = in[i+2] == '=' ? 0 : b64_char(in[i+2]);
        int d = in[i+3] == '=' ? 0 : b64_char(in[i+3]);

        if (a == -1 || b == -1 || c == -1 || d == -1) {
            printf("Invalid base64 character at position %d\n", i);
            return -1;
        }

        out[len++] = (a << 2) | (b >> 4);
        if (in[i+2] != '=') out[len++] = (b << 4) | (c >> 2);
        if (in[i+3] != '=') out[len++] = (c << 6) | d;
    }
    printf("Decoded %d bytes from base64\n", len);
    return len;
}

uLongf get_gzip_uncompressed_size(unsigned char *data, int data_len) {
    if (data_len < 4) return 0;

    // GZIP footer stores original size in last 4 bytes, little-endian
    uint32_t size = data[data_len - 4]
                  | (data[data_len - 3] << 8)
                  | (data[data_len - 2] << 16)
                  | (data[data_len - 1] << 24);
    return (uLongf)size;
}


char *decompress_data(unsigned char *data, int data_len, uLongf *out_len) {
    printf("Decompressing with zlib inflate in GZIP mode...\n");

    z_stream strm = {0};
    strm.next_in = data;
    strm.avail_in = data_len;

    if (inflateInit2(&strm, 16 + MAX_WBITS) != Z_OK) {  // 16 + MAX_WBITS enables gzip decoding
        printf("Failed to initialize zlib stream for GZIP\n");
        return NULL;
    }

    // Allocate output buffer with some room; grow if needed
    size_t buffer_size = 8192;
    char *out = mempool_alloc(&level_pool, buffer_size);
    if (!out) {
        printf("malloc failed\n");
        inflateEnd(&strm);
        return NULL;
    }

    while (1) {
        if (strm.total_out >= buffer_size) {
            buffer_size *= 2;
            out = mempool_realloc(&level_pool, out, buffer_size);
            if (!out) {
                printf("realloc failed\n");
                inflateEnd(&strm);
                return NULL;
            }
        }

        strm.next_out = (Bytef *)(out + strm.total_out);
        strm.avail_out = buffer_size - strm.total_out;

        int ret = inflate(&strm, Z_NO_FLUSH);
        if (ret == Z_STREAM_END) break;
        if (ret != Z_OK) {
            printf("inflate failed with code %d\n", ret);
            mempool_free(&level_pool, out);
            inflateEnd(&strm);
            return NULL;
        }
    }

    *out_len = strm.total_out;
    inflateEnd(&strm);

    // Final shrink to fit
    out = mempool_realloc(&level_pool, out, *out_len + 1); // +1 for null terminator
    out[*out_len] = '\0';

    printf("Decompressed %lu bytes successfully\n", *out_len);
    return out;
}

char *get_metadata_value(const char *levelString, const char *key) {
    if (!levelString || !key) return NULL;

    // Find the first semicolon, which separates metadata from objects
    const char *end = strchr(levelString, ';');
    if (!end) return NULL;

    printf("Found metadata\n");

    // We'll scan only the metadata portion
    size_t metadataLen = end - levelString;
    char *metadata = mempool_alloc(&level_pool, metadataLen + 1);
    if (!metadata) return NULL;

    printf("Allocated metadata\n");

    strncpy(metadata, levelString, metadataLen);
    metadata[metadataLen] = '\0';

    
    printf("Copied metadata: %s\n", metadata);

    // Tokenize metadata by comma
    char *token = strtok(metadata, ",");
    while (token) {
        if (strcmp(token, key) == 0) {
            char *value = strtok(NULL, ",");  // get value after key
            if (!value) break;

            // Copy and return value
            char *result = strdup(value);
            mempool_free(&level_pool, metadata);
            return result;
        }
        token = strtok(NULL, ",");
    }

    mempool_free(&level_pool, metadata);
    return NULL;
}

char *decompress_level() {
    printf("Loading level data...\n");

    char *b64 = extract_base64((const char *) test_gmd);
    if (!b64) {
        printf("Could not extract base64 data\n");
        return NULL;
    }

    fix_base64_url(b64);

    unsigned char *decoded = mempool_alloc(&level_pool, strlen(b64));
    int decoded_len = base64_decode(b64, decoded);
    if (decoded_len <= 0) {
        printf("Failed to decode base64\n");
        mempool_free(&level_pool, b64);
        mempool_free(&level_pool, decoded);
        return NULL;
    }

    uLongf decompressed_len;
    char *decompressed = decompress_data(decoded, decoded_len, &decompressed_len);
    if (!decompressed) {
        printf("Decompression failed (check zlib error above)\n");
        mempool_free(&level_pool, decoded);
        mempool_free(&level_pool, b64);
        return NULL;
    }

    mempool_free(&level_pool, decoded);
    mempool_free(&level_pool, b64);
    
    return decompressed;
}

// I don't even know what this does
char **split_string(const char *str, char delimiter, int *outCount) {
    char **result = NULL;
    int count = 0;
    const char *start = str;
    const char *ptr = str;

    while (*ptr) {
        if (*ptr == delimiter) {
            int len = ptr - start;
            if (len > 0) {
                char *token = (char *)mempool_alloc(&level_pool, len + 1);
                strncpy(token, start, len);
                token[len] = '\0';

                result = (char **)mempool_realloc(&level_pool, result, sizeof(char*) * (count + 1));
                result[count++] = token;
            }
            start = ptr + 1;
        }
        ptr++;
    }
    if (ptr > start) {
        int len = ptr - start;
        char *token = (char *)mempool_alloc(&level_pool, len + 1);
        strncpy(token, start, len);
        token[len] = '\0';
        result = (char **)mempool_realloc(&level_pool, result, sizeof(char*) * (count + 1));
        result[count++] = token;
    }

    *outCount = count;
    return result;
}

void free_string_array(char **arr, int count) {
    for (int i = 0; i < count; i++) mempool_free(&level_pool, arr[i]);
    mempool_free(&level_pool, arr);
}


int parse_color_channels(const char *colorString, GDColorChannel **outArray) {
    if (!colorString || !outArray) return 0;

    int count = 0;
    char **entries = split_string(colorString, '|', &count);
    if (!entries) return 0;

    GDColorChannel *channels = mempool_alloc(&level_pool, sizeof(GDColorChannel) * count);
    if (!channels) {
        printf("Couldn't alloc color channels\n");
        free_string_array(entries, count);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        GDColorChannel channel = {0};  // Zero-initialize
        int kvCount = 0;
        char **kvs = split_string(entries[i], '_', &kvCount);

        for (int j = 0; j + 1 < kvCount; j += 2) {
            int key = atoi(kvs[j]);
            const char *valStr = kvs[j + 1];

            switch (key) {
                case 1:  channel.fromRed = atoi(valStr); break;
                case 2:  channel.fromGreen = atoi(valStr); break;
                case 3:  channel.fromBlue = atoi(valStr); break;
                case 4:  channel.playerColor = atoi(valStr); break;
                case 5:  channel.blending = atoi(valStr) != 0; break;
                case 6:  channel.channelID = atoi(valStr); break;
                case 7:  channel.fromOpacity = atof(valStr); break;
                case 8:  channel.toggleOpacity = atoi(valStr) != 0; break;
                case 9:  channel.inheritedChannelID = atoi(valStr); break;
                case 10: channel.hsv = atoi(valStr); break;
                case 11: channel.toRed = atoi(valStr); break;
                case 12: channel.toGreen = atoi(valStr); break;
                case 13: channel.toBlue = atoi(valStr); break;
                case 14: channel.deltaTime = atof(valStr); break;
                case 15: channel.toOpacity = atof(valStr); break;
                case 16: channel.duration = atof(valStr); break;
                case 17: channel.copyOpacity = atoi(valStr) != 0; break;
            }
        }

        channels[i] = channel;
        free_string_array(kvs, kvCount);
    }

    *outArray = channels;
    free_string_array(entries, count);
    return count;
}

GDValueType get_value_type_for_key(int key) {
    switch (key) {
        case 1:  return GD_VAL_INT;    // Object ID
        case 2:  return GD_VAL_FLOAT;  // X Position
        case 3:  return GD_VAL_FLOAT;  // Y Position
        case 4:  return GD_VAL_BOOL;   // Flipped Horizontally
        case 5:  return GD_VAL_BOOL;   // Flipped Vertically
        case 6:  return GD_VAL_FLOAT;  // Rotation
        case 7:  return GD_VAL_INT;    // Red (color)
        case 8:  return GD_VAL_INT;    // Green
        case 9:  return GD_VAL_INT;    // Blue
        case 10: return GD_VAL_FLOAT;  // Duration
        case 11: return GD_VAL_BOOL;   // Touch Triggered
        case 24: return GD_VAL_INT;    // Zlayer
        case 25: return GD_VAL_INT;    // Zorder
        case 31: return GD_VAL_STRING; // Text (base64)
        case 32: return GD_VAL_FLOAT;  // Scaling
        case 57: return GD_VAL_STRING; // Integer array - treat as string
        default:
            return GD_VAL_INT; // Default fallback
    }
}


// Parse bool from string ("1" = true, else false)
bool parse_bool(const char *str) {
    return (str[0] == '1' && str[1] == '\0');
}

__unused void print_prop(int key, GDValueType type, GDValue value) {
    printf("  Key %d, type %d, value = ", key, type);
    switch (type) {
        case GD_VAL_INT:
            printf("%d\n", value.i);
            break;
        case GD_VAL_FLOAT:
            printf("%f\n", value.f);
            break;
        case GD_VAL_BOOL:
            printf("%s\n", value.b ? "true" : "false");
            break;
        case GD_VAL_STRING:
            printf("\"%s\"\n", value.s);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

int parse_gd_object(const char *objStr, GDObject *obj) {
    int count = 0;
    char **tokens = split_string(objStr, ',', &count);
    if (count < 1) {
        free_string_array(tokens, count);
        return 0;
    }

    obj->propCount = 0;

    for (int i = 0; i + 1 < count && obj->propCount < 20; i += 2) {
        int key = atoi(tokens[i]);
        const char *valStr = tokens[i + 1];
        GDValueType type = get_value_type_for_key(key);

        obj->keys[obj->propCount] = key;
        obj->types[obj->propCount] = type;

        switch (type) {
            case GD_VAL_INT:
                obj->values[obj->propCount].i = atoi(valStr);
                break;
            case GD_VAL_FLOAT:
                obj->values[obj->propCount].f = atof(valStr);
                break;
            case GD_VAL_BOOL:
                obj->values[obj->propCount].b = parse_bool(valStr);
                break;
            case GD_VAL_STRING:
                obj->values[obj->propCount].s = strdup(valStr);
                break;
            default:
                obj->values[obj->propCount].i = atoi(valStr);
                break;
        }

        obj->propCount++;
    }

    free_string_array(tokens, count);
    return 1;
}

void free_gd_object(GDObject *obj) {
    for (int i = 0; i < obj->propCount; i++) {
        if (obj->types[i] == GD_VAL_STRING && obj->values[i].s) {
            mempool_free(&level_pool, obj->values[i].s);
        }
    }
}

GDObjectTyped *convert_to_typed(const GDObject *obj) {
    GDObjectTyped *typed = mempool_alloc(&level_pool, sizeof(GDObjectTyped));
    if (!typed) return NULL;

    // Initialize all fields to default values:
    memset(typed, 0, sizeof(GDObjectTyped));

    typed->id = obj->values[0].i;
    typed->x = obj->values[1].f;
    typed->y = obj->values[2].f;

    typed->zsheetlayer = objects[typed->id].spritesheet_layer;
    typed->zlayer = objects[typed->id].def_zlayer;
    typed->zorder = objects[typed->id].def_zorder;

    for (int i = 2; i < obj->propCount; i++) {
        int key = obj->keys[i];
        GDValueType type = obj->types[i];
        GDValue val = obj->values[i];

        switch (key) {
            case 4:  // FlippedH
                if (type == GD_VAL_BOOL) typed->flippedH = val.b;
                break;
            case 5:  // FlippedV
                if (type == GD_VAL_BOOL) typed->flippedV = val.b;
                break;
            case 6:  // Rotation
                if (type == GD_VAL_FLOAT) typed->rotation = val.f;
                break;
            case 7:  // Color R
                if (type == GD_VAL_INT) typed->trig_colorR = val.i;
                break;
            case 8:  // Color G
                if (type == GD_VAL_INT) typed->trig_colorG = val.i;
                break;
            case 9:  // Color B
                if (type == GD_VAL_INT) typed->trig_colorB = val.i;
                break;
            case 10: // Duration
                if (type == GD_VAL_FLOAT) typed->trig_duration = val.f;
                break;
            case 24: // Z layer
                if (type == GD_VAL_INT) typed->zlayer = val.i;
                break;
            case 25: // Z order
                if (type == GD_VAL_INT) typed->zorder = val.i;
                break;

            // Add more keys here as needed

            default:
                // Unknown keys ignored here
                break;
        }
    }

    return typed;
}

void free_typed_object(GDObjectTyped *obj) {
    if (!obj) return;
    //if (obj->text) mempool_free(&level_pool, obj->text);
    mempool_free(&level_pool, obj);
}

GDTypedObjectList *convert_all_to_typed(GDObjectList *objList) {
    if (!objList) return NULL;

    GDObjectTyped **typedArray = mempool_alloc(&level_pool, sizeof(GDObjectTyped *) * objList->objectCount);
    if (!typedArray) return NULL;

    for (int i = 0; i < objList->objectCount; i++) {
        typedArray[i] = convert_to_typed(&objList->objects[i]);
        if (!typedArray[i]) {
            printf("Failed to convert object %d\n", i);
            for (int j = 0; j < i; j++) {
                free_typed_object(typedArray[j]);
            }
            mempool_free(&level_pool, typedArray);
            return NULL;
        }
    }

    GDTypedObjectList *typedList = mempool_alloc(&level_pool, sizeof(GDTypedObjectList));
    if (!typedList) {
        printf("Failed to allocate the typed list");
        for (int i = 0; i < objList->objectCount; i++) {
            free_typed_object(typedArray[i]);
        }
        mempool_free(&level_pool, typedArray);
        return NULL;
    }

    typedList->count = objList->objectCount;
    typedList->objects = typedArray;

    return typedList;
}

void free_gd_object_list(GDObjectList *list) {
    for (int i = 0; i < list->objectCount; i++) {
        free_gd_object(&list->objects[i]);
    }
    mempool_free(&level_pool, list->objects);
    mempool_free(&level_pool, list);
}

GDObjectList *parse_string(const char *levelString) {
    int sectionCount = 0;
    char **sections = split_string(levelString, ';', &sectionCount);

    if (sectionCount < 3) {
        printf("Level string missing sections!\n");
        free_string_array(sections, sectionCount);
        return NULL;
    }

    int objectCount = sectionCount - 1;
    GDObject *objects = (GDObject *)mempool_alloc(&level_pool, sizeof(GDObject) * objectCount);

    for (int i = 1; i < sectionCount; i++) {
        if (!parse_gd_object(sections[i], &objects[i - 1])) {
            printf("Failed to parse object at section %d\n", i);
        }
    }

    free_string_array(sections, sectionCount);

    GDObjectList *objectList = mempool_alloc(&level_pool, sizeof(GDObjectList));
    if (!objectList) {
        printf("Memory allocation failed for objectList\n");
        mempool_free(&level_pool, objects);
        return NULL;
    }

    objectList->objectCount = objectCount;
    objectList->objects = objects;

    return objectList;
}

void free_typed_object_list(GDTypedObjectList *list) {
    if (!list) return;

    for (int i = 0; i < list->count; i++) {
        free_typed_object(list->objects[i]);
    }
    mempool_free(&level_pool, list->objects);
    mempool_free(&level_pool, list);
}

int compare_typed_objects(const void *a, const void *b) {
    GDObjectSortable *objA = (GDObjectSortable *)a;
    GDObjectSortable *objB = (GDObjectSortable *)b;

    int zlayerA = objA->obj->zlayer;
    int zlayerB = objB->obj->zlayer;

    if (zlayerA != zlayerB)
        return zlayerA - zlayerB; // Ascending
       
    int zsheetlayerA = objA->obj->zsheetlayer;
    int zsheetlayerB = objB->obj->zsheetlayer;

    if (zsheetlayerA != zsheetlayerB)
        return zsheetlayerB - zsheetlayerA; // Descending

    int zorderA = objA->obj->zorder;
    int zorderB = objB->obj->zorder;

    if (zorderA != zorderB)
        return zorderA - zorderB; // Ascending

    return objA->originalIndex - objB->originalIndex; // Stable fallback
}

int compare_sortable_layers(const void *a, const void *b) {
    GDLayerSortable *layerSortA = (GDLayerSortable *)a;
    GDLayerSortable *layerSortB = (GDLayerSortable *)b;

    struct ObjectLayer *layerA = layerSortA->layer->layer;
    struct ObjectLayer *layerB = layerSortB->layer->layer;

    GDObjectTyped *objA = layerSortA->layer->obj;
    GDObjectTyped *objB = layerSortB->layer->obj;

    int zlayerA = objA->zlayer + layerA->zlayer_offset;
    int zlayerB = objB->zlayer + layerB->zlayer_offset;

    if (zlayerA != zlayerB)
        return zlayerA - zlayerB; // Ascending

    int obj_idA = objA->id;
    int obj_idB = objB->id;

    int sheetA = objects[obj_idA].spritesheet_layer;
    int sheetB = objects[obj_idB].spritesheet_layer;

    if (sheetA != sheetB)
        return sheetB - sheetA; // Descending

    int zorderA = objA->zorder;
    int zorderB = objB->zorder;

    if (zorderA != zorderB)
        return zorderA - zorderB; // Ascending

    return layerSortA->originalIndex - layerSortB->originalIndex; // Stable fallback
}

// Me when this is like Java (using Comparable interface)
void sort_typed_objects_by_layer(GDTypedObjectList *list) {
    if (!list || list->count <= 1) return;

    printf("Sorting object list\n");

    // Wrap objects with indices
    GDObjectSortable *sortable = mempool_alloc(&level_pool, sizeof(GDObjectSortable) * list->count);

    if (sortable == NULL) {
        printf("Couldn't allocate sortable object\n");
        return;
    }

    for (int i = 0; i < list->count; i++) {
        sortable[i].obj = list->objects[i];
        sortable[i].originalIndex = i;
    }

    // Sort
    qsort(sortable, list->count, sizeof(GDObjectSortable), compare_typed_objects);

    // Rebuild the list
    for (int i = 0; i < list->count; i++) {
        list->objects[i] = sortable[i].obj;
    }

    mempool_free(&level_pool, sortable);
}

// Me when this is like Java (using Comparable interface)
void sort_layers_by_layer(GDObjectLayerList *list) {
    if (!list || list->count <= 1) return;

    printf("Sorting layer list\n");
    
    // Wrap objects with indices
    GDLayerSortable *sortable = mempool_alloc(&level_pool, sizeof(GDLayerSortable) * list->count);

    if (sortable == NULL) {
        printf("Couldn't allocate sortable layer\n");
        return;
    }

    for (int i = 0; i < list->count; i++) {
        sortable[i].layer = list->layers[i];
        sortable[i].originalIndex = i;

        // GD epicness
        if (sortable[i].layer->obj->id != PLAYER_OBJECT) {
            int zlayer = sortable[i].layer->obj->zlayer;
            bool blending = channels[sortable[i].layer->layer->col_channel].blending;
            if (blending ^ (zlayer % 2 == 0)) {
                sortable[i].layer->obj->zlayer--;
            }
        }
    }

    // Sort
    qsort(sortable, list->count, sizeof(GDLayerSortable), compare_sortable_layers);

    // Rebuild the list
    for (int i = 0; i < list->count; i++) {
        list->layers[i] = sortable[i].layer;
    }

    mempool_free(&level_pool, sortable);
}

void free_typed_object_array(GDObjectTyped **array, int count) {
    if (!array) return;
    for (int i = 0; i < count; i++) {
        free_typed_object(array[i]);
    }
    mempool_free(&level_pool, array); // Free the array of pointers itself
}

GDObjectLayerList *fill_layers_array(GDTypedObjectList *objList) {
    // Count layers
    int layerCount = 1; // Count player
    for (int i = 0; i < objList->count; i++) {
        GDObjectTyped *obj = objList->objects[i];

        int obj_id = obj->id;

        if (obj_id < OBJECT_COUNT)
            layerCount += objects[obj->id].num_layers;
    }

    printf("Allocating %d bytes for %d layers\n", sizeof(GDObjectLayer) * layerCount, layerCount);
    GDObjectLayer *layers = mempool_alloc(&level_pool, sizeof(GDObjectLayer) * layerCount);

    if (layers == NULL) {
        printf("Couldn't allocate layers\n");
        return NULL;
    }

    // Put player
    GDObjectTyped *obj = mempool_alloc(&level_pool, sizeof(GDObjectTyped));
    obj->id = PLAYER_OBJECT;
    obj->zlayer = LAYER_T1-1;
    obj->zorder = 0;
    obj->zsheetlayer = 0;
    layers[0].obj = obj;
    layers[0].layer = (struct ObjectLayer *) &objects[obj->id].layers[0];
    layers[0].layerNum = 0;

    printf("Allocated %d layers\n", layerCount);

    // Fill array
    int count = 1;
    for (int i = 1; i < objList->count; i++) {
        GDObjectTyped *obj = objList->objects[i];

        int obj_id = obj->id;

        if (obj_id < OBJECT_COUNT)
            for (int j = 0; j < objects[obj->id].num_layers; j++) {
                layers[count].layer = (struct ObjectLayer *) &objects[obj->id].layers[j];
                layers[count].obj = obj;
                layers[count].layerNum = j;
                count++;
            }
    }
    
    printf("Finished filling %d layers\n", count);

    printf("Allocating layer list\n");
    GDObjectLayerList *layerList = mempool_alloc(&level_pool, sizeof(GDObjectLayerList));
    
    if (layerList == NULL) {
        printf("Couldn't allocate layer list\n");
        mempool_free(&level_pool, layers);
        return NULL;
    }

    // Allocate array of pointers to GDObjectLayer
    layerList->layers = mempool_alloc(&level_pool, sizeof(GDObjectLayer *) * layerCount);

    if (layerList->layers == NULL) {
        printf("Couldn't allocate layer pointers\n");
        mempool_free(&level_pool, layers);
        mempool_free(&level_pool, layerList);
        return NULL;
    }

    for (int i = 0; i < layerCount; i++) {
        layerList->layers[i] = &layers[i];
    }

    layerList->count = layerCount;

    return layerList;
}

GDTypedObjectList *objectsArrayList = NULL;
GDObjectLayerList *layersArrayList = NULL;
int channelCount = 0;
GDColorChannel *colorChannels = NULL;

void load_level() {
    char *level_string = decompress_level();

    if (level_string == NULL) {
        printf("Failed decompressing the level.\n");
        return;
    }

    // Get colors
    char *metaStr = get_metadata_value(level_string, "kS38");
    channelCount = parse_color_channels(metaStr, &colorChannels);

    GDObjectList *objectsList = parse_string(level_string);

    mempool_free(&level_pool, level_string);

    if (objectsList == NULL) {
        printf("Failed parsing the objects.\n");
        return;
    }

    objectsArrayList = convert_all_to_typed(objectsList);
    free_gd_object_list(objectsList);

    if (objectsArrayList == NULL) {
        printf("Failed converting objects to typed structs.\n");
        return;
    }
    
    sort_typed_objects_by_layer(objectsArrayList);

    layersArrayList = fill_layers_array(objectsArrayList);

    if (layersArrayList == NULL) {
        printf("Couldn't sort layers\n");
        free_typed_object_list(objectsArrayList);
        return;
    }

    sort_layers_by_layer(layersArrayList);
    
    set_color_channels();
    memset(trigger_buffer, 0, sizeof(trigger_buffer));

    printf("Finished loading level\n");
}

void unload_level() {
    mempool_init(&level_pool, level_pool_buffer, LEVEL_POOL_SIZE);
}

void set_color_channels() {
    for (int i = 0; i < channelCount; i++) {
        GDColorChannel colorChannel = colorChannels[i];
        
        switch (colorChannel.channelID) {
            case 1000:
                channels[BG].color.r = colorChannel.fromRed;
                channels[BG].color.g = colorChannel.fromGreen;
                channels[BG].color.b = colorChannel.fromBlue;
                break;

            case 1001:
                channels[GROUND].color.r = colorChannel.fromRed;
                channels[GROUND].color.g = colorChannel.fromGreen;
                channels[GROUND].color.b = colorChannel.fromBlue;
                break;
        }
    }
}

void reload_level() {
    memset(trigger_buffer, 0, sizeof(trigger_buffer));
    set_color_channels();
}
