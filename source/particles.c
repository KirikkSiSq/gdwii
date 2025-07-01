#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "main.h"
#include "particles.h"

GRRLIB_texImg *particleTex = NULL;

void spawn_particle(float x, float y, float vx, float vy, float ax, float ay, float scale, float vscale, ColorAlpha color, float life) {
    Particle *particles = gameplay_state->particles;
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!gameplay_state->particles[i].active) {
            particles[i].x = x;
            particles[i].y = y;
            particles[i].vx = vx / dt;
            particles[i].vy = vy / dt;
            particles[i].ax = ax / dt;
            particles[i].ay = ay / dt;
            particles[i].life = life / dt;
            particles[i].scale = scale;
            particles[i].vscale = vscale / dt;
            particles[i].color = color;
            particles[i].active = true;
            break;
        }
    }
}

void update_particles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle *particles = gameplay_state->particles;
        if (particles[i].active) {
            particles[i].x += particles[i].vx * dt;
            particles[i].y += particles[i].vy * dt;
            particles[i].vx += particles[i].ax;
            particles[i].vy += particles[i].ay;
            particles[i].scale += particles[i].vscale * dt;
            particles[i].life -= dt;
            if (particles[i].life <= 0 || particles[i].scale <= 0) {
                particles[i].active = false;
            }
        }
    }
}

// Call this in your render loop
void draw_particles() {
    GRRLIB_SetBlend(GRRLIB_BLEND_ADD);
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle *particles = render_state->particles;

        float calc_x = ((particles[i].x - render_state->camera_x) * SCALE);
        float calc_y = screenHeight - ((particles[i].y - render_state->camera_y) * SCALE);
        
        if (particles[i].active) {
            GRRLIB_DrawImg(
                calc_x,
                calc_y,
                particleTex,
                0,
                particles[i].scale,
                particles[i].scale,
                RGBA(particles[i].color.r, particles[i].color.g, particles[i].color.b, particles[i].color.a)
            );
        }
    }
    GRRLIB_SetBlend(GRRLIB_BLEND_ALPHA);
}