#pragma once

#include "objects.h"

#define MAX_PARTICLES 256

typedef struct {
    float x, y;
    float vx, vy;
    float ax, ay;
    float life;
    bool active;
    ColorAlpha color;
    float scale;
    float vscale;
} Particle;

extern GRRLIB_texImg *particleTex;

void spawn_particle(float x, float y, float vx, float vy, float ax, float ay, float scale, float vscale, ColorAlpha color, float life);
void update_particles();
void draw_particles();
