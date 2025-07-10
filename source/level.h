#pragma once

typedef struct {
    char *level_name;
    const unsigned char *song_ptr;
    int song_size;
    const unsigned char *data_ptr;
} LevelDefinition;

#define LEVEL_NUM 9

extern int level_id;

extern LevelDefinition levels[LEVEL_NUM];