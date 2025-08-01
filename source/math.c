#include <math.h>
#include <stdlib.h>
#include <float.h>

#include "math.h"
#include "objects.h"
#include "game.h"
#include "player.h"

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

float ease_out(float current, float target, float smoothing) {
    return current + (target - current) * smoothing;
}

static guVector axis = (guVector){0.0f, 0.0f, 1.0f};

void set_texture(const GRRLIB_texImg *tex) {
    
    if (tex == NULL || tex->data == NULL)
        return;

    GXTexObj  texObj;
    GX_InitTexObj(&texObj, tex->data, tex->w, tex->h,
                  tex->format, GX_CLAMP, GX_CLAMP, GX_FALSE);

    if (GRRLIB_Settings.antialias == false) {
        GX_InitTexObjLOD(&texObj, GX_NEAR, GX_NEAR,
                         0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    }

    GX_LoadTexObj(&texObj,      GX_TEXMAP0);
}

void  custom_drawImg (const f32 xpos, const f32 ypos, const GRRLIB_texImg *tex, const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color) {
    Mtx       m, m1, m2, mv;

    guMtxIdentity  (m1);
    guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0f);
    guMtxRotAxisDeg(m2, &axis, degrees);
    guMtxConcat    (m2, m1, m);

    const f32 width  = tex->w * 0.5f;
    const f32 height = tex->h * 0.5f;

    guMtxTransApply(m, m,
        xpos +width  +tex->handlex
            -tex->offsetx +( scaleX *(-tex->handley *sin(-DegToRad(degrees))
                                      -tex->handlex *cos(-DegToRad(degrees))) ),
        ypos +height +tex->handley
            -tex->offsety +( scaleY *(-tex->handley *cos(-DegToRad(degrees))
                                      +tex->handlex *sin(-DegToRad(degrees))) ),
        0);
    guMtxConcat(GXmodelView2D, m, mv);

    GX_LoadPosMtxImm(mv, GX_PNMTX0);
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        GX_Position3f32(-width, -height, 0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(0, 0);

        GX_Position3f32(width, -height, 0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(1, 0);

        GX_Position3f32(width, height, 0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(1, 1);

        GX_Position3f32(-width, height, 0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(0, 1);
    GX_End();
}

void  custom_gxengine (const guVector v[], const u32 color[], const u16 n,
                       const u8 fmt) {
    GX_Begin(fmt, GX_VTXFMT0, n);
    for (u16 i = 0; i < n; i++) {
        GX_Position3f32(v[i].x, v[i].y, v[i].z);
        GX_Color1u32(color[i]);
    }
    GX_End();
}

void  custom_ellipse (const f32 x, const f32 y, const f32 radiusX,
                      const f32 radiusY, const u32 color, const u8 filled) {
    guVector v[36];
    u32 ncolor[36];
    const f32 G_DTOR = M_DTOR * 10;

    for (u32 a = 0; a < 36; a++) {
        const f32 ra = a * G_DTOR;

        v[a].x = cos(ra) * radiusX + x;
        v[a].y = sin(ra) * radiusY + y;
        v[a].z = 0.0f;
        ncolor[a] = color;
    }

    if (filled == false) {
        custom_gxengine(v, ncolor, 36, GX_LINESTRIP  );
    }
    else {
        custom_gxengine(v, ncolor, 36, GX_TRIANGLEFAN);
    }
}

void  custom_circle (const f32 x, const f32 y, const f32 radius,
                     const u32 color, const u8 filled) {
    custom_ellipse(x, y, radius, radius, color, filled);
}

void  custom_drawPart (const f32 xpos, const f32 ypos, const f32 partx, const f32 party, const f32 partw, const f32 parth, const GRRLIB_texImg *tex, const f32 degrees, const f32 scaleX, const f32 scaleY, const u32 color) {
    Mtx       m, m1, m2, mv;

    if (tex == NULL || tex->data == NULL)
        return;

    // The 0.001f/x is the frame correction formula by spiffen
    const f32 s1 = (partx / tex->w) + (0.001f / tex->w);
    const f32 s2 = ((partx + partw) / tex->w) - (0.001f / tex->w);
    const f32 t1 = (party / tex->h) + (0.001f / tex->h);
    const f32 t2 = ((party + parth) / tex->h) - (0.001f / tex->h);

    const f32 width  = partw * 0.5f;
    const f32 height = parth * 0.5f;

    guMtxIdentity  (m1);
    guMtxScaleApply(m1, m1, scaleX, scaleY, 1.0f);
    guMtxRotAxisDeg(m2, &axis, degrees);
    guMtxConcat    (m2, m1, m);

    guMtxTransApply(m, m,
        xpos +width  +tex->handlex
            -tex->offsetx +( scaleX *(-tex->handley *sin(-DegToRad(degrees))
                                      -tex->handlex *cos(-DegToRad(degrees))) ),
        ypos +height +tex->handley
            -tex->offsety +( scaleY *(-tex->handley *cos(-DegToRad(degrees))
                                      +tex->handlex *sin(-DegToRad(degrees))) ),
        0);

    guMtxConcat(GXmodelView2D, m, mv);

    GX_LoadPosMtxImm(mv, GX_PNMTX0);
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
        GX_Position3f32(-width, -height, 0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(s1, t1);

        GX_Position3f32(width, -height,  0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(s2, t1);

        GX_Position3f32(width, height,  0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(s2, t2);

        GX_Position3f32(-width, height,  0.0f);
        GX_Color1u32   (color);
        GX_TexCoord2f32(s1, t2);
    GX_End();
    GX_LoadPosMtxImm(GXmodelView2D, GX_PNMTX0);
}

void  custom_rectangle (const f32 x,      const f32 y,
                        const f32 width,  const f32 height,
                        const u32 color, const bool filled) {
    const f32 x2 = x + width;
    const f32 y2 = y + height;

    if (filled == true) {
        GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
            GX_Position3f32(x, y, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(x2, y, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(x2, y2, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(x, y2, 0.0f);
            GX_Color1u32(color);
        GX_End();
    }
    else {
        GX_Begin(GX_LINESTRIP, GX_VTXFMT0, 5);
            GX_Position3f32(x, y, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(x2, y, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(x2, y2, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(x, y2, 0.0f);
            GX_Color1u32(color);
            GX_Position3f32(x, y, 0.0f);
            GX_Color1u32(color);
        GX_End();
    }
}

float normalize_angle(float angle) {
    angle = fmodf(angle, 360.0f);
    if (angle < 0) angle += 360.0f;
    return angle;
}

bool is_effectively_integer(float x) {
    return fabsf(x - roundf(x)) < FLT_EPSILON;
}

float ip1_ceilf(float x) {
    float c = ceilf(x);
    if (is_effectively_integer(x)) {
        return c + 1.0f;
    }
    return c;
}