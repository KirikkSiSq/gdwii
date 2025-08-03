#pragma once

typedef struct {
    char *level_name;
    const unsigned char *data_ptr;
} LevelDefinition;

typedef struct {
    const char *song_name;
    int song_size;
    int tempo;
} SongDefinition;

#define LEVEL_NUM 21
#define SONG_NUM 16

extern int level_id;

extern LevelDefinition levels[LEVEL_NUM];
extern SongDefinition songs[SONG_NUM];