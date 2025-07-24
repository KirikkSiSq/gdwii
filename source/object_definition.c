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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
                .col_channel = OBJ,
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
};