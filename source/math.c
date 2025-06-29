#include <math.h>
#include "math.h"

float positive_fmod(float n, float divisor) {
    float value = fmod(n, divisor);
    return value + (value < 0 ? divisor : 0);
}

int color_lerp(int color1, int color2, float fraction) {
        unsigned char   r1 = (color1 >> 24) & 0xff;
        unsigned char   r2 = (color2 >> 24) & 0xff;
        unsigned char   g1 = (color1 >> 16) & 0xff;
        unsigned char   g2 = (color2 >> 16) & 0xff;
        unsigned char   b1 = (color1 >> 8) & 0xff;
        unsigned char   b2 = (color2 >> 8) & 0xff;

        return (int) ((r2 - r1) * fraction + r1) << 24 |
                (int) ((g2 - g1) * fraction + g1) << 16 |
                (int) ((b2 - b1) * fraction + b1) << 8 | 255;
}

Vec2D rotate(Vec2D point, float angle, Vec2D origin) {
    
    float s = sinf(angle);
    float c = cosf(angle);
    point.x -= origin.x;
    point.y -= origin.y;
    Vec2D rotated = {
        point.x * c - point.y * s + origin.x,
        point.x * s + point.y * c + origin.y
    };
    return rotated;
}

float maxf(float a, float b) {
    return a > b ? a : b;
}