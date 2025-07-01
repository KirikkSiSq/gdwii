#include <math.h>
#include "math.h"
#include "objects.h"
#include <stdlib.h>

float positive_fmod(float n, float divisor) {
    float value = fmod(n, divisor);
    return value + (value < 0 ? divisor : 0);
}

Color color_lerp(Color color1, Color color2, float fraction) {
    u8 r1 = color1.r;
    u8 r2 = color2.r;
    u8 g1 = color1.g;
    u8 g2 = color2.g;
    u8 b1 = color1.b;
    u8 b2 = color2.b;

    Color returned;
    returned.r = (r2 - r1) * fraction + r1;
    returned.g = (g2 - g1) * fraction + g1;
    returned.b = (b2 - b1) * fraction + b1;

    return returned;
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

float approachf(float current, float target, float speed, float smoothing) {
    float diff = target - current;
    float step = diff * smoothing; // smoothing in [0,1], e.g. 0.1 for gentle, 0.5 for fast
    if (fabsf(diff) < speed)
        return target;
    return current + step + (diff > 0 ? speed : -speed);
}

void rotate_point_around_center(
    float x, float y,               // anchor position on screen
    float offset_x, float offset_y, // object position (pre-rotation)
    float center_x, float center_y, // pivot center in the object
    float width, float height,      // size of the object
    float rotation_deg,             // rotation angle in degrees
    float *output_x, float *output_y // output screen position
) {
    float rot = DegToRad(rotation_deg);
    float sin_theta = sinf(rot);
    float cos_theta = cosf(rot);

    // Relative position to rotation center
    float relative_x = offset_x - center_x + (width / 2.0f);
    float relative_y = offset_y - center_y + (height / 2.0f);

    // Apply rotation
    float rotated_x = (relative_x * cos_theta) - (relative_y * sin_theta);
    float rotated_y = (relative_y * cos_theta) + (relative_x * sin_theta);

    // Final screen position
    *output_x = x + (center_x - (width / 2.0f)) + rotated_x;
    *output_y = y + (center_y - (height / 2.0f)) + rotated_y;
}

float random_float(float min, float max) {
    return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}