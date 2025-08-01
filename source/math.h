#pragma once
#include <grrlib.h>

#define SAME_SIGN(v1,v2) (v1>=0)==(v2>=0)
#define DIFFERENT_SIGN(v1,v2) (v1>=0)!=(v2>=0)

typedef struct {
    float x, y;
} Vec2D;

typedef struct {
    u8 r;
    u8 b;
    u8 g;
} Color;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} ColorAlpha;

extern Mtx                 GXmodelView2D;

Vec2D rotate(Vec2D point, float angle, Vec2D origin);
float maxf(float a, float b);
float positive_fmod(float n, float divisor);
Color color_lerp(Color color1, Color color2, float fraction);
float approachf(float current, float target, float speed, float smoothing);
void rotate_point_around_center_gfx(
    float x, float y,               // anchor position on screen
    float offset_x, float offset_y, // object position (pre-rotation)
    float center_x, float center_y, // pivot center in the object
    float width, float height,      // size of the object
    float rotation_deg,             // rotation angle in degrees
    float *output_x, float *output_y // output screen position
);

void rotate_point_around_center(float cx, float cy, float angle, float x, float y, float *out_x, float *out_y);

float adjust_angle(float angle, int flipX, int flipY);
float adjust_angle_x(float angle, int flipX);
float adjust_angle_y(float angle, int flipY);
float randomf();
float random_float(float min, float max);
int random_int(int min, int max);
float map_range(float val, float min1, float max1, float min2, float max2);

float square_distance(float xa, float ya, float xb, float yb);

float clampf(float d, float min, float max);
float slerp(float a, float b, float ratio);
float lerp(float from, float to, float alpha);
float iLerp(float a, float b, float ratio, float dt);
float iSlerp(float a, float b, float ratio, float dt);
float ease_out(float current, float target, float smoothing);

void  custom_drawImg (const f32 xpos, const f32 ypos, const GRRLIB_texImg *tex, const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color);
void  custom_drawPart (const f32 xpos, const f32 ypos, const f32 partx, const f32 party, const f32 partw, const f32 parth, const GRRLIB_texImg *tex, const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color);
void  custom_circle (const f32 x, const f32 y, const f32 radius,
                     const u32 color, const u8 filled);
void  custom_rectangle (const f32 x,      const f32 y,
    const f32 width,  const f32 height,
    const u32 color, const bool filled);
void set_texture(const GRRLIB_texImg *tex);
float normalize_angle(float angle);
float ip1_ceilf(float x);