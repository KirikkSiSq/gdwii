#include <math.h>
#include "math.h"
#include "objects.h"
#include <stdlib.h>
#include "game.h"

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


// This one only works for drawing
void rotate_point_around_center_gfx(
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

void rotate_point_around_center(float cx, float cy, float angle, float x, float y, float *out_x, float *out_y) {
    float s = sinf(DegToRad(-angle));
    float c = cosf(DegToRad(-angle));

    x -= cx;
    y -= cy;

    float xnew = x * c - y * s;
    float ynew = x * s + y * c;

    *out_x = xnew + cx;
    *out_y = ynew + cy;
}

float randomf() {
    return (float)rand() / RAND_MAX;
}

float random_float(float min, float max) {
    return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

int random_int(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

float map_range(float val, float min1, float max1, float min2, float max2) {
    return min2 + ((max2 - min2) / (max1 - min1)) * (val - min1);
}

float adjust_angle(float angle, int flipX, int flipY) {
    // Normalize to [0, 360)
    angle = positive_fmod(angle, 360);

    if (flipX && flipY) {
        angle = fmodf(angle + 180.0f, 360.0f);
    } else if (flipX) {
        angle = 180.0f - angle;
    } else if (flipY) {
        angle = -angle;
    }

    // Normalize again
    angle = positive_fmod(angle, 360);

    return angle;
}

float adjust_angle_x(float angle, int flipX) {
    angle = positive_fmod(angle, 360);

    if (flipX) {
        angle = 180.0f - angle;
    } 

    angle = positive_fmod(angle, 360);

    return angle;
}

float adjust_angle_y(float angle, int flipY) {
    angle = positive_fmod(angle, 360);

    if (flipY) {
        angle = angle + 180;
    }

    angle = positive_fmod(angle, 360);

    return angle;
}

float square_distance(float xa, float ya, float xb, float yb) {
	return ((xb - xa) * (xb - xa)) + ((yb - ya) * (yb - ya));
}

float clampf(float d, float min, float max) {
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

float repeat(float a, float length) {
	return clampf(a - floorf(a / length) * length, 0.0f, length);
}

float slerp(float a, float b, float ratio) {
	float delta = repeat((b - a), 360.f);
	if (delta > 180.f)
		delta -= 360.f;
	return a + delta * clampf(ratio, 0.f, 1.f);
}

float lerp(float from, float to, float alpha) {
    return from * (1.0f - alpha) + to * alpha;
}

float iLerp(float a, float b, float ratio, float dt) {
	const float rDelta = dt / STEPS_DT;
	const float s	  = 1.f - ratio;

	float iRatio = 1.f - powf(s, rDelta);

	return lerp(a, b, iRatio);
}

float iSlerp(float a, float b, float ratio, float dt) {
	const float rDelta = dt / STEPS_DT;
	const float s	  = 1.f - ratio;

	float iRatio = 1.f - powf(s, rDelta);

	return slerp(a, b, iRatio);
}