#pragma once
#include <stdbool.h>

bool intersect(float x1, float y1, float w1, float h1, float angle1, float x2, float y2, float w2, float h2, float angle2);
bool intersect_one_way(float x1, float y1, float w1, float h1, float angle1, float x2, float y2, float w2, float h2, float angle2);
bool intersect_rect_circle(float rx, float ry, float rw, float rh, float rangle,
                          float cx, float cy, float cradius);
bool circle_rect_collision(float cx, float cy, float radius,
    float x1, float y1, float x2, float y2);