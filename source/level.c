#include "level.h"

#include "level_includes.h"

LevelDefinition levels[] = {
    {
        .level_name = "STEREO MADNESS",
        .data_ptr  = StereoMadness_gmd
    }, 
    {
        .level_name = "BACK ON TRACK",
        .data_ptr  = BackOnTrack_gmd
    }, 
    {
        .level_name = "POLARGEIST",
        .data_ptr  = Polargeist_gmd
    }, 
    {
        .level_name = "DRY OUT",
        .data_ptr  = DryOut_gmd
    }, 
    {
        .level_name = "BASE AFTER BASE",
        .data_ptr  = BaseAfterBase_gmd
    }, 
    {
        .level_name = "CANT LET GO",
        .data_ptr  = CantLetGo_gmd
    }, 
    {
        .level_name = "JUMPER",
        .data_ptr  = Jumper_gmd
    }, 
    {
        .level_name = "TIME MACHINE",
        .data_ptr  = TimeMachine_gmd
    }, 
    {
        .level_name = "CYCLES",
        .data_ptr  = Cycles_gmd
    }, 
    {
        .level_name = "XSTEP",
        .data_ptr = xStep_gmd
    },
    {
        .level_name = "LEVEL EASY",
        .data_ptr  = LevelEasy_gmd
    },
    {
        .level_name = "THE LIGHTNING ROAD",
        .data_ptr  = TheLightningRoad_gmd
    },
    {
        .level_name = "THE NIGHTMARE",
        .data_ptr  = TheNightmare_gmd
    },
    {
        .level_name = "DEMON PARK",
        .data_ptr  = DemonPark_gmd
    },
    {
        .level_name = "AUTO JUMPER",
        .data_ptr  = AutoJumper_gmd
    },
    {
        .level_name = "TEST",
        .data_ptr = Test_gmd
    }
};

SongDefinition songs[] = {
    {
        .song_ptr = StereoMadness_mp3,
        .song_size = StereoMadness_mp3_size,
        .tempo = 160
    },
    {
        .song_ptr = BackOnTrack_mp3,
        .song_size = BackOnTrack_mp3_size,
        .tempo = 142
    },
    {
        .song_ptr = Polargeist_mp3,
        .song_size = Polargeist_mp3_size,
        .tempo = 175
    },
    {
        .song_ptr = DryOut_mp3,
        .song_size = DryOut_mp3_size,
        .tempo = 145
    },
    {
        .song_ptr = BaseAfterBase_mp3,
        .song_size = BaseAfterBase_mp3_size,
        .tempo = 141
    },
    {
        .song_ptr = CantLetGo_mp3,
        .song_size = CantLetGo_mp3_size,
        .tempo = 170
    },
    {
        .song_ptr = Jumper_mp3,
        .song_size = Jumper_mp3_size,
        .tempo = 175
    },
    {
        .song_ptr = TimeMachine_mp3,
        .song_size = TimeMachine_mp3_size,
        .tempo = 143
    },
    {
        .song_ptr = Cycles_mp3,
        .song_size = Cycles_mp3_size,
        .tempo = 140
    },
    {
        .song_ptr = xStep_mp3,
        .song_size = xStep_mp3_size,
        .tempo = 130
    }
};

