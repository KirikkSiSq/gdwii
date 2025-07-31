#include "object_includes.h"
#include "objects.h"

const ObjectHitbox gamemode_portal_hitbox = {
    .width = 34,
    .height = 86,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox gravity_portal_hitbox = {
    .width = 25,
    .height = 75,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox mirror_portal_hitbox = {
    .width = 44,
    .height = 92,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox size_portal_hitbox = {
    .width = 31,
    .height = 90,
    .type = HITBOX_SPECIAL
};

const ObjectHitbox no_hitbox = {
    .width = 0,
    .height = 0,
    .type = HITBOX_NONE
};

const ObjectDefinition unknown = {
    .layers = {},
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = 0,
    .def_zorder = 0,
    .num_layers = 0,  
};

const ObjectDefinition trigger = {
    .layers = {},
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = 0,
    .def_zorder = 0,
    .num_layers = 0,  
    .is_trigger = TRUE
};


const struct ObjectLayer player_layer = {
    .col_channel = WHITE,
    .zlayer_offset = 0,
    .texture = NULL
};

const ObjectDefinition player_object = {
    .layers = { player_layer },
    .hitbox = no_hitbox,
    .spritesheet_layer = SHEET_BLOCKS,
    .def_zlayer = LAYER_T1-1,
    .def_zorder = 9999999,
    .num_layers = 1,  
    .is_trigger = TRUE
};

const ObjectDefinition objects[] = {
    player_object,
    { // Basic block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Checker pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Checker pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_07_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = spike_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_01_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ground spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_01_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_02_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_03_001_png
            }
        },
        .hitbox = {
            .width = 9,
            .height = 10.8,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Blue portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_01_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_01_front_001_png
            }
        },
        .hitbox = gravity_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Yellow portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_02_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_02_front_001_png
            }
        },
        .hitbox = gravity_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Cube portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_03_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_03_front_001_png
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Ship portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_04_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_04_front_001_png
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 14
    { // Big rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = rod_01_001_png
            },
            {
                .x_offset = 0,
                .y_offset = -50,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = rod_ball_01_001_png
            },
            {
                .x_offset = 0,
                .y_offset = -50,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = rod_ball_02_001_png
            },
            {
                .x_offset = 0,
                .y_offset = -50,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = rod_ball_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Medium rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = rod_02_001_png
            },
            {
                .x_offset = 0,
                .y_offset = -40,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = rod_ball_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Small rod
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = rod_03_001_png
            },
            {
                .x_offset = 0,
                .y_offset = -30,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = rod_ball_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Deco Spikes big 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes medium 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes small 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Spikes tiny 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikes_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    trigger, // 22
    trigger, // 23
    trigger, // 24
    trigger, // 25
    trigger, // 26
    trigger, // 27
    trigger, // 28
    trigger, // 29
    trigger, // 30
    unknown, // 31
    trigger, // 32
    trigger, // 33
    unknown, // 34
    { // Yellow pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = bump_01_001_png
            }
        },
        .hitbox = {
            .width = 25,
            .height = 4,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Yellow orb
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = ring_01_001_png
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    unknown, // 37
    unknown, // 38
    { // Half spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = spike_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_02_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 5.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = plank_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = plank_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = chain_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    unknown, // 42
    unknown, // 43
    unknown, // 44
    { // Orange mirror portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_05_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_05_front_001_png
            }
        },
        .hitbox = mirror_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Blue mirror portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_06_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_06_front_001_png
            }
        },
        .hitbox = mirror_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Ball portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_07_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_07_front_001_png
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    { // Deco Cloud big 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_cloud_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Deco Cloud small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_cloud_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing circle
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing circunference
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing heart
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing diamond
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing star
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    trigger, //55
    trigger, //56
    trigger, //57
    trigger, //58
    trigger, //59
    { // Pulsing note
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_06_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Ground spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_04_001_png
            }
        },
        .hitbox = {
            .width = 9,
            .height = 7.2,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Slab 1.3
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_b_01_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Slab 1.3 corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_b_02_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Slab 1.3 inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_b_03_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_06_001_png
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Slab 1.3 right edge
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_b_04_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Slab 1.3 left edge
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_b_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Blue pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = gravbump_01_001_png
            }
        },
        .hitbox = {
            .width = 25,
            .height = 6,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Slab 1.3 unit
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 10,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_b_06_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 10,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 16,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_c_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_c_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_c_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_c_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_c_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.3 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_c_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.3 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_c_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_05b_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_alt_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_d_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_01_001_alt_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_alt_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_d_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_alt_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_alt_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_d_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_03_001_alt_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 78
    { // 1.4 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_d_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.4 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_alt_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_d_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_04_001_alt_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.4 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_alt_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_d_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_05b_001_alt_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Checker full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_08_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Blue orb
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = gravring_01_001_png
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Saw deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_cogwheel_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Saw deco medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_cogwheel_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Saw deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_cogwheel_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Sawblade big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = sawblade_01_001_png
            }
        },
        .hitbox = {
            .radius = 32.3,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Sawblade medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = sawblade_02_001_png
            }
        },
        .hitbox = {
            .radius = 21.6,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Black tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Black tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Black tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_05b_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Saw deco tiny
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_cogwheel_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Sawblade small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = sawblade_03_001_png
            }
        },
        .hitbox = {
            .radius = 12,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Big portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_08_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_08_front_001_png
            }
        },
        .hitbox = size_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 100
    { // Mini portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_09_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_09_front_001_png
            }
        },
        .hitbox = size_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 102
    { // Medium Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = spike_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = spike_03_001_png
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    trigger,
    trigger,
    { // 1.5 Big P2 Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_02_chain_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // 1.5 Small P2 Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_02_chain_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    unknown, // 108
    unknown, // 109
    { // 1.5 Small P1 Chains
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_chain_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Ufo portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = -1,
                .texture = portal_10_back_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = portal_10_front_001_png
            }
        },
        .hitbox = gamemode_portal_hitbox,
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 10,
        .num_layers = 2
    },
    unknown, // 112
    { // Square Deco Spikes big 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_brick_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Square Deco Spikes medium 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_brick_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Square Deco Spikes small 
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_brick_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // 1.5 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_f_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_f_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_f_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_f_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.5 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_f_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.5 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_f_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.5 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_f_07_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Thorn 1
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_thorn_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 2
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_thorn_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_thorn_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_thorn_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 5
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_thorn_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Thorn 6
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_thorn_06_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Cloud deco medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_cloud_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Cloud deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_cloud_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Cloud deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_cloud_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Arrow
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_arrow_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Exclamation mark
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_exmark_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Diamond deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_art_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Bush ground spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_b_01_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_b_02_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_b_03_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_b_04_001_png
            }
        },
        .hitbox = {
            .width = 14.1,
            .height = 20,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Question mark
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_qmark_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Wheel deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_wheel_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Wheel deco medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_wheel_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Wheel deco small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_wheel_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Pink pad
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = bump_03_001_png
            }
        },
        .hitbox = {
            .width = 25,
            .height = 5,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Pink orb
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = ring_03_001_png
            }
        },
        .hitbox = {
            .width = 36,
            .height = 36,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 12,
        .num_layers = 1
    },
    { // Coin
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = secretCoin_01_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = secretCoin_01_002_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = secretCoin_01_003_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = secretCoin_01_004_png
            }
        },
        .hitbox = {
            .width = 40,
            .height = 40,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Breakable block
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = brick_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = brick_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_BREAKABLE_BLOCK
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = invis_spike_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = invis_spike_01_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading Medium Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = invis_spike_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = invis_spike_03_001_png
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = invis_square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = invis_square_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading Slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = invis_plank_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = invis_plank_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
   },
   { // Pulsing square
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_07_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing triangle
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_ball_08_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pulsing cross
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_cross_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 10,
        .num_layers = 1
    },
    { // Spikeart big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikeart_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spikeart medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikeart_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spikeart small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikeart_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Spikewheel big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikewheel_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Spikewheel medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikewheel_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Spikewheel small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_spikewheel_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Wave center
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_wave_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Wave left
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_wave_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Wave right
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_wave_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // 1.6 tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_05_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_03_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_04_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset edge without line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_06_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_07_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_05b_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset double inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_002_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_08_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_06_002_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset block alt 1
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_09_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 tileset block alt 2
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_10_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 edge
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 edge 2
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 corner
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 inside corner
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_05_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_05_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 slab block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 small slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_07_001_png
            }
        },
        .hitbox = {
            .width = 14,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ice Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = iceSpike_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = iceSpike_01_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ice Half Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = iceSpike_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = iceSpike_02_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 6.4,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Ice Medium Spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = iceSpike_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = iceSpike_03_001_png
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Cartwheel big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_cartwheel_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Cartwheel medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_cartwheel_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Cartwheel small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_cartwheel_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Spike blade big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = blade_b_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blade_b_01_001_png
            }
        },
        .hitbox = {
            .radius = 15.48,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = blade_b_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blade_b_02_001_png
            }
        },
        .hitbox = {
            .radius = 20.4,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = blade_b_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blade_b_03_001_png
            }
        },
        .hitbox = {
            .radius = 3,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade alt big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = blade_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blade_01_001_png
            }
        },
        .hitbox = {
            .radius = 32.3,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade alt medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = blade_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blade_02_001_png
            }
        },
        .hitbox = {
            .radius = 21.96,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    { // Spike blade alt small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = blade_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blade_03_001_png
            }
        },
        .hitbox = {
            .radius = 12.6,
            .is_circular = TRUE,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .is_saw = TRUE,
        .num_layers = 2
    },
    unknown, // 189
    { // Diamond deco big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_art_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Fake spike big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = fakeSpike_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -4,
        .num_layers = 1
    },
    { // 1.6 slab single
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_08_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // 1.6 tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_g_11_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // 1.6 slab inside corner small
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_09_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_09_001_png
            }
        },
        .hitbox = {
            .width = 21,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Mini block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_small_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_01_small_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_01_small_001_png
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Mini slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = plank_01_small_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = plank_01_small_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = plank_01_small_001_png
            }
        },
        .hitbox = {
            .width = 15,
            .height = 8,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // 1.6 slab medium
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_10_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = square_h_10_001_png
            }
        },
        .hitbox = {
            .width = 22,
            .height = 21,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fake half spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = fakeSpike_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -4,
        .num_layers = 1
    },
    { // Fake medium spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = fakeSpike_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -4,
        .num_layers = 1
    },
    { // Slow speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = boost_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = boost_01_001_png
            },
        },
        .hitbox = {
            .width = 34,
            .height = 44,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Normal speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = boost_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = boost_02_001_png
            },
        },
        .hitbox = {
            .width = 33,
            .height = 56,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Fast speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = boost_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = boost_03_001_png
            },
        },
        .hitbox = {
            .width = 51,
            .height = 56,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Faster speed portal
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = boost_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = WHITE,
                .zlayer_offset = 0,
                .texture = boost_04_001_png
            },
        },
        .hitbox = {
            .width = 65,
            .height = 56,
            .type = HITBOX_SPECIAL
        },
        .spritesheet_layer = SHEET_PORTALS,
        .def_zlayer = LAYER_B1,
        .def_zorder = -6,
        .num_layers = 2
    },
    { // Fading Mini Slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = invis_plank_01_small_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = invis_plank_01_small_001_png
            }
        },
        .hitbox = {
            .width = 15,
            .height = 8,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading half spike
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = invis_spike_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = invis_spike_02_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 5.6,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Fading mini block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = LBG_NO_LERP,
                .zlayer_offset = 0,
                .texture = invis_square_01_small_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = invis_square_01_small_001_png
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .fades = TRUE,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 2
    },
    { // Colored tileset block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 1,
        .num_layers = 1
    },
    { // Colored tileset pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored tileset pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_01_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = blockOutline_05b_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 214
    { // Colored slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_h_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = colorPlank_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = plank_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 14,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 1,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = spike_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = colorSpike_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = colorSpike_01_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 12,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored half spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = spike_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = colorSpike_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = colorSpike_02_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 5.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored medium spike
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = spike_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = colorSpike_03_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = colorSpike_03_001_png
            }
        },
        .hitbox = {
            .width = 4,
            .height = 7.6,
            .type = HITBOX_SPIKE
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored mini slab
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = plank_01_small_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = colorPlank_01_small_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = colorPlank_01_small_001_png
            }
        },
        .hitbox = {
            .width = 15,
            .height = 8,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Mini block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_small_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = colorSquare_01_small_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = colorSquare_01_small_001_png
            }
        },
        .hitbox = {
            .width = 15,
            .height = 15,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    trigger, 
    { // Round cloud big
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_roundCloud_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Round cloud medium
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_roundCloud_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Round cloud small
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_roundCloud_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .is_saw = TRUE,
        .num_layers = 1
    },
    { // Round swirve line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_swirve_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Round swirve corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_swirve_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pentagon deco edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_bar_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pentagon deco corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_bar_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Hexagon line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_bar_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Hexagon corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_bar_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_smallbar_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_smallbar_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG bricks block
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_square_03_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_square_03_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG half brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_square_03_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Big pulsing circunference
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P2,
                .zlayer_offset = 0,
                .texture = d_circle_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link line
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_link_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_link_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link triple
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_link_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_link_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Link end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = P1,
                .zlayer_offset = 0,
                .texture = d_link_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Pentagon deco inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_bar_07_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Wavy pit right
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_04_02_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 7.2,
            .type = HITBOX_SPIKE,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Wavy pit left
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = pit_04_03_001_png
            }
        },
        .hitbox = {
            .width = 6,
            .height = 6.8,
            .type = HITBOX_SPIKE,
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 1
    },
    { // Brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_f_brick01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Half brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = BLACK,
                .zlayer_offset = 0,
                .texture = square_f_brick02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored checker block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_03_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_04_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_05_color_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored checker pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_06_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_07_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_07_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored checker double inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_002_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_02_08_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_08_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_03_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_03_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_03_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_03_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_03_01_color_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored 1.3 pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_03_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.3 pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_03_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_07_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 162
    { // Colored 1.4 block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_04_05_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_04_05_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_04_05_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_04_05_color_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored 1.4 pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_04_05_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored 1.4 pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_04_05_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_07_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick block
        .layers = {
            {
                .x_offset = 0.5,
                .y_offset = 0.5,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_01_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_05_01_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_01_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick edge
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_02_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_05_02_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_02_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_03_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_05_03_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_03_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick inside corner
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_04_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_05_04_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_04_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick filler
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_05_05_color_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B2,
        .def_zorder = -7,
        .num_layers = 1
    },
    { // Colored brick pillar end
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_06_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_05_06_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_06_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    { // Colored brick pillar
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ_BLENDING,
                .zlayer_offset = 0,
                .texture = square_07_glow_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = lightsquare_05_07_color_001_png
            },
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = OBJ,
                .zlayer_offset = 0,
                .texture = lightsquare_02_07_001_png
            }
        },
        .hitbox = {
            .width = 30,
            .height = 30,
            .type = HITBOX_SOLID
        },
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_T1,
        .def_zorder = 2,
        .num_layers = 3
    },
    unknown, // 276
    { // Colored brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = d_square_03_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Colored half brick
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = 1,
                .zlayer_offset = 0,
                .texture = d_square_03_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG plain
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_square_01_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG checker
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_square_02_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG 1.4
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_square_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // LBG 1.3
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_square_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon triple
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_smallbar_03_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon full
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_smallbar_04_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
    { // Mini hexagon single
        .layers = {
            {
                .x_offset = 0,
                .y_offset = 0,
                .col_channel = LBG,
                .zlayer_offset = 0,
                .texture = d_smallbar_05_001_png
            }
        },
        .hitbox = no_hitbox,
        .spritesheet_layer = SHEET_BLOCKS,
        .def_zlayer = LAYER_B1,
        .def_zorder = 9,
        .num_layers = 1
    },
};