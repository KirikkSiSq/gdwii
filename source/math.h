#pragma once
#include "objects.h"

typedef struct {
    float x, y;
} Vec2D;

Vec2D rotate(Vec2D point, float angle, Vec2D origin);
float maxf(float a, float b);
float positive_fmod(float n, float divisor);
Color color_lerp(Color color1, Color color2, float fraction);
float approachf(float current, float target, float speed, float smoothing);
void rotate_point_around_center(
    float x, float y,               // anchor position on screen
    float offset_x, float offset_y, // object position (pre-rotation)
    float center_x, float center_y, // pivot center in the object
    float width, float height,      // size of the object
    float rotation_deg,             // rotation angle in degrees
    float *output_x, float *output_y // output screen position
);
float random_float(float min, float max);