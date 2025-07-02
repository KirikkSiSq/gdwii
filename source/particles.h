#pragma once

#include "objects.h"

#define MAX_PARTICLES 256

typedef struct {
    int group_id;
    float x, y;
    float vx, vy;
    float ax, ay;
    float life;
    bool active;
    ColorAlpha color;
    float scale;
    float vscale;
    bool blending;
} Particle;

enum ParticleGroupID {
    CUBE_DRAG,
    SHIP_TRAIL,
    HOLDING_SHIP_TRAIL,
    SHIP_DRAG
};

extern GRRLIB_texImg *particleTex;

void spawn_particle(int group_id, float x, float y, float vx, float vy, float ax, float ay, float scale, float vscale, ColorAlpha color, float life, bool blending);
void update_particles();
void draw_particles(int group_id);
