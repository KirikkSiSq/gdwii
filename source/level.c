#include "level.h"

#include "level_includes.h"

LevelDefinition levels[] = {
    {
        .level_name = "STEREO MADNESS",
        .song_ptr  = StereoMadness_mp3,
        .song_size = StereoMadness_mp3_size,
        .data_ptr  = StereoMadness_gmd
    }, 
    {
        .level_name = "BACK ON TRACK",
        .song_ptr  = BackOnTrack_mp3,
        .song_size = BackOnTrack_mp3_size,
        .data_ptr  = BackOnTrack_gmd
    }, 
    {
        .level_name = "POLARGEIST",
        .song_ptr  = Polargeist_mp3,
        .song_size = Polargeist_mp3_size,
        .data_ptr  = Polargeist_gmd
    }, 
    {
        .level_name = "DRY OUT",
        .song_ptr  = DryOut_mp3,
        .song_size = DryOut_mp3_size,
        .data_ptr  = DryOut_gmd
    }, 
    {
        .level_name = "BASE AFTER BASE",
        .song_ptr  = BaseAfterBase_mp3,
        .song_size = BaseAfterBase_mp3_size,
        .data_ptr  = BaseAfterBase_gmd
    }, 
    {
        .level_name = "CANT LET GO",
        .song_ptr  = CantLetGo_mp3,
        .song_size = CantLetGo_mp3_size,
        .data_ptr  = CantLetGo_gmd
    }, 
    {
        .level_name = "JUMPER",
        .song_ptr  = Jumper_mp3,
        .song_size = Jumper_mp3_size,
        .data_ptr  = Jumper_gmd
    }, 
    {
        .level_name = "TIME MACHINE",
        .song_ptr  = TimeMachine_mp3,
        .song_size = TimeMachine_mp3_size,
        .data_ptr  = TimeMachine_gmd
    }, 
    {
        .level_name = "CYCLES",
        .song_ptr  = Cycles_mp3,
        .song_size = Cycles_mp3_size,
        .data_ptr  = Cycles_gmd
    }, 
    {
        .level_name = "LEVEL EASY",
        .song_ptr  = StereoMadness_mp3,
        .song_size = StereoMadness_mp3_size,
        .data_ptr  = LevelEasy_gmd
    },
    {
        .level_name = "THE NIGHTMARE",
        .song_ptr  = Polargeist_mp3,
        .song_size = Polargeist_mp3_size,
        .data_ptr  = TheNightmare_gmd
    },
    {
        .level_name = "DEMON PARK",
        .song_ptr  = TimeMachine_mp3,
        .song_size = TimeMachine_mp3_size,
        .data_ptr  = DemonPark_gmd
    }
};