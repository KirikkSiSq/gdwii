#pragma once

typedef struct {
    float x, y;
} Vec2D;

Vec2D rotate(Vec2D point, float angle, Vec2D origin);
float maxf(float a, float b);
float positive_fmod(float n, float divisor);
int color_lerp(int color1, int color2, float fraction);
float approachf(float current, float target, float speed, float smoothing);