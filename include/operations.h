#pragma once
#include "base.h"

typedef union {
    struct { f32 x, y; };
    float e[2];
} Vec2;

typedef union {
    struct { f32 x, y, z; };
    float e[3];
} Vec3;

typedef struct {
    f32 e[4];
} Mat2;

typedef struct {
    f32 e[9];
} Mat3;

typedef struct {
    f32 e[16];
} Mat4;

static inline Vec3 mat3_transform_vec3(Mat3 m, Vec3 v) {
    Vec3 result = {0};
    return result;
}
