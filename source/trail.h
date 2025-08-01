// Adapted from OpenGD

#ifndef MOTION_TRAIL_H
#define MOTION_TRAIL_H

#include <gccore.h>
#include <grrlib.h>

#include "objects.h"

#define MAX_TRAIL_POINTS 64
#define TRAIL_CLEAR_DISTANCE 30.f

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    float u, v;
} Tex2F;

typedef struct {
    bool appendNewPoints;
    bool fastMode;
    bool startingPositionInitialized;

    int nuPoints;
    int previousNuPoints;
    int maxPoints;

    float fadeDelta;
    float minSeg;
    float stroke;

    Vec2 positionR;
    Color displayedColor;

    GRRLIB_texImg *texture;

    float pointState[MAX_TRAIL_POINTS];
    Vec2 pointVertexes[MAX_TRAIL_POINTS];
    Vec2 vertices[MAX_TRAIL_POINTS * 2];
    u8 colorPointer[MAX_TRAIL_POINTS * 8]; // RGBA * 2 per point
    Tex2F texCoords[MAX_TRAIL_POINTS * 2];

    Vec2 lastStopPosition;
    bool wasStopped;

} MotionTrail;

extern MotionTrail trail;

void MotionTrail_Init(MotionTrail* trail, float fade, float minSeg, float stroke, Color color, GRRLIB_texImg *tex);
void MotionTrail_Update(MotionTrail* trail, float delta);
void MotionTrail_ResumeStroke(MotionTrail* trail);
void MotionTrail_StopStroke(MotionTrail* trail);
void MotionTrail_Draw(MotionTrail* trail);

#endif