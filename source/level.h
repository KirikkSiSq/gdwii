#pragma once

typedef struct {
    char *level_name;
    const unsigned char *data_ptr;
} LevelDefinition;

typedef struct {
    const unsigned char *song_ptr;
    int song_size;
    int tempo;
} SongDefinition;

#define LEVEL_NUM 17
#define SONG_NUM 11

extern int level_id;

extern LevelDefinition levels[LEVEL_NUM];
extern SongDefinition songs[SONG_NUM];