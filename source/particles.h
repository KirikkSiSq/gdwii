#pragma once

#include "objects.h"

#define MAX_PARTICLES 512

typedef struct {
    int group_id;
    GDObjectTyped *parent_obj;
    float x, y;
    float vx, vy;
    float ax, ay;
    float gravity_x, gravity_y;
    float rotation;
    float life;
    bool active;
    ColorAlpha color, start_color, end_color;
    ColorAlpha color_delta;
    float scale, start_scale, end_scale, scale_delta;
    float vscale;
    float velocity_angle; 
    float velocity_magnitude;
    float rotate_per_second;
    int texture_id;
    bool blending;
} Particle;

typedef struct {
    float angle, angleVar;
    float speed, speedVar;
    float gravity_x, gravity_y;
    float life, lifeVar;
    float start_scale, start_scaleVar;
    float end_scale, end_scaleVar;
    ColorAlpha start_color, start_colorVar;
    ColorAlpha end_color, end_colorVar;
    bool blending;
    float sourcePosVarX, sourcePosVarY;
    float rotatePerSecond;
    float rotatePerSecondVariance;
    float rotationStart;
    float rotationStartVariance;
    float rotationEnd;
    float rotationEndVariance;
    float minRadius;
    float maxRadius;
    int texture_id;
} ParticleTemplate;

enum ParticleTextures {
    PARTICLE_SQUARE,
    PARTICLE_CIRCLE,
    PARTICLE_CIRCUNFERENCE,
    PARTICLE_P1_TRAIL,
};

enum ParticleGroupID {
    CUBE_DRAG,
    SHIP_TRAIL,
    HOLDING_SHIP_TRAIL,
    SHIP_DRAG,
    ORB_PARTICLES,
    PAD_PARTICLES,
    GLITTER_EFFECT,
    PORTAL_PARTICLES,
    USE_EFFECT,
    ORB_HITBOX_EFFECT,
    P1_TRAIL,
    UFO_JUMP,
    UFO_TRAIL,
};

extern ParticleTemplate particle_templates[];
extern GRRLIB_texImg *particleCircleTex;
extern GRRLIB_texImg *particleTex;

void spawn_particle(int group_id, float x, float y, GDObjectTyped *parent_obj);
void update_particles();
void draw_particles(int group_id);
void draw_obj_particles(int group_id, GDObjectTyped *parent_obj);
