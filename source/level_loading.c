#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <stdbool.h>

#include "blocks.h"
#include "level_loading.h"

#include "test_gmd.h"

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
    char *b64 = malloc(len + 1);
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
    char *out = malloc(buffer_size);
    if (!out) {
        printf("malloc failed\n");
        inflateEnd(&strm);
        return NULL;
    }

    while (1) {
        if (strm.total_out >= buffer_size) {
            buffer_size *= 2;
            out = realloc(out, buffer_size);
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
            free(out);
            inflateEnd(&strm);
            return NULL;
        }
    }

    *out_len = strm.total_out;
    inflateEnd(&strm);

    // Final shrink to fit
    out = realloc(out, *out_len + 1); // +1 for null terminator, if you want it as string
    out[*out_len] = '\0';

    printf("Decompressed %lu bytes successfully\n", *out_len);
    return out;
}

char *decompress_level() {
    printf("Loading level data...\n");

    char *b64 = extract_base64((const char *) test_gmd);
    if (!b64) {
        printf("Could not extract base64 data\n");
        return NULL;
    }

    fix_base64_url(b64);

    unsigned char *decoded = malloc(strlen(b64));
    int decoded_len = base64_decode(b64, decoded);
    if (decoded_len <= 0) {
        printf("Failed to decode base64\n");
        free(b64);
        free(decoded);
        return NULL;
    }

    uLongf decompressed_len;
    char *decompressed = decompress_data(decoded, decoded_len, &decompressed_len);
    if (!decompressed) {
        printf("Decompression failed (check zlib error above)\n");
        free(decoded);
        free(b64);
        return NULL;
    }

    free(decoded);
    free(b64);
    
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
                char *token = (char *)malloc(len + 1);
                strncpy(token, start, len);
                token[len] = '\0';

                result = (char **)realloc(result, sizeof(char*) * (count + 1));
                result[count++] = token;
            }
            start = ptr + 1;
        }
        ptr++;
    }
    if (ptr > start) {
        int len = ptr - start;
        char *token = (char *)malloc(len + 1);
        strncpy(token, start, len);
        token[len] = '\0';
        result = (char **)realloc(result, sizeof(char*) * (count + 1));
        result[count++] = token;
    }

    *outCount = count;
    return result;
}

void free_string_array(char **arr, int count) {
    for (int i = 0; i < count; i++) free(arr[i]);
    free(arr);
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

    //printf("Object: props=%d\n", obj->propCount);

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

        //print_prop(obj->keys[obj->propCount], obj->types[obj->propCount], obj->values[obj->propCount]);

        obj->propCount++;
    }

    free_string_array(tokens, count);
    return 1;
}

void free_gd_object(GDObject *obj) {
    for (int i = 0; i < obj->propCount; i++) {
        if (obj->types[i] == GD_VAL_STRING && obj->values[i].s) {
            free(obj->values[i].s);
        }
    }
}

GDObjectTyped *convert_to_typed(const GDObject *obj) {
    GDObjectTyped *typed = malloc(sizeof(GDObjectTyped));
    if (!typed) return NULL;

    // Initialize all fields to default values:
    memset(typed, 0, sizeof(GDObjectTyped));
    typed->text = NULL;
    typed->scaling = 1.0f;

    for (int i = 0; i < obj->propCount; i++) {
        int key = obj->keys[i];
        GDValueType type = obj->types[i];
        GDValue val = obj->values[i];

        switch (key) {
            case 1:  // ID
                if (type == GD_VAL_INT) typed->id = val.i;
                break;
            case 2:  // X
                if (type == GD_VAL_FLOAT) typed->x = val.f;
                break;
            case 3:  // Y
                if (type == GD_VAL_FLOAT) typed->y = val.f;
                break;
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
                if (type == GD_VAL_INT) typed->colorR = val.i;
                break;
            case 8:  // Color G
                if (type == GD_VAL_INT) typed->colorG = val.i;
                break;
            case 9:  // Color B
                if (type == GD_VAL_INT) typed->colorB = val.i;
                break;
            case 10: // Duration
                if (type == GD_VAL_FLOAT) typed->duration = val.f;
                break;
            case 11: // Touch Triggered
                if (type == GD_VAL_BOOL) typed->touchTriggered = val.b;
                break;
            case 24: // Z layer
                if (type == GD_VAL_INT) typed->zlayer = val.i;
                break;
            case 25: // Z order
                if (type == GD_VAL_INT) typed->zorder = val.i;
                break;
            case 31: // Text (string)
                if (type == GD_VAL_STRING && val.s) {
                    typed->text = strdup(val.s);
                }
                break;
            case 32: // Scaling
                if (type == GD_VAL_FLOAT) typed->scaling = val.f;
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
    if (obj->text) free(obj->text);
    free(obj);
}

GDTypedObjectList *convert_all_to_typed(GDObjectList *objList) {
    if (!objList) return NULL;

    GDObjectTyped **typedArray = malloc(sizeof(GDObjectTyped *) * objList->objectCount);
    if (!typedArray) return NULL;

    for (int i = 0; i < objList->objectCount; i++) {
        typedArray[i] = convert_to_typed(&objList->objects[i]);
        if (!typedArray[i]) {
            printf("Failed to convert object %d\n", i);
            for (int j = 0; j < i; j++) {
                free_typed_object(typedArray[j]);
            }
            free(typedArray);
            return NULL;
        }
    }

    GDTypedObjectList *typedList = malloc(sizeof(GDTypedObjectList));
    if (!typedList) {
        printf("Failed to allocate the typed list");
        for (int i = 0; i < objList->objectCount; i++) {
            free_typed_object(typedArray[i]);
        }
        free(typedArray);
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
    free(list->objects);
    free(list);
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
    GDObject *objects = (GDObject *)malloc(sizeof(GDObject) * objectCount);

    for (int i = 1; i < sectionCount; i++) {
        if (!parse_gd_object(sections[i], &objects[i - 1])) {
            printf("Failed to parse object at section %d\n", i);
        }
    }

    free_string_array(sections, sectionCount);

    GDObjectList *objectList = malloc(sizeof(GDObjectList));
    if (!objectList) {
        printf("Memory allocation failed for objectList\n");
        free(objects);
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
    free(list->objects);
    free(list);
}

int compare_typed_objects(const void *a, const void *b) {
    GDObjectSortable *objA = (GDObjectSortable *)a;
    GDObjectSortable *objB = (GDObjectSortable *)b;

    int zlayerA = objA->obj->zlayer;
    int zlayerB = objB->obj->zlayer;

    if (zlayerA != zlayerB)
        return zlayerB - zlayerA; // Descending

    int zorderA = objA->obj->zorder;
    int zorderB = objB->obj->zorder;

    if (zorderA != zorderB)
        return zorderB - zorderA; // Descending

    return objA->originalIndex - objB->originalIndex; // Stable fallback
}

// Me when this is like Java (using Comparable interface)
void sort_typed_objects_by_layer(GDTypedObjectList *list) {
    if (!list || list->count <= 1) return;

    // Wrap objects with indices
    GDObjectSortable *sortable = malloc(sizeof(GDObjectSortable) * list->count);
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

    free(sortable);
}

void free_typed_object_array(GDObjectTyped **array, int count) {
    if (!array) return;
    for (int i = 0; i < count; i++) {
        free_typed_object(array[i]);
    }
    free(array); // Free the array of pointers itself
}

GDTypedObjectList *objectsArrayList = NULL;

void load_level() {
    char *level_string = decompress_level();

    if (level_string == NULL) {
        printf("Failed decompressing the level.\n");
        return;
    }

    GDObjectList *objectsList = parse_string(level_string);
    free(level_string);

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
}
