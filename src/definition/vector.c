#include "base.h"
#include "definitions.h"
#include <stdio.h>
#include "vector.h"

LVector vector_create(Arena arena, sz size) {
    LVector v = PUSH_STRUCT(arena, struct vector_type, true);
    if (!v) terminate("Couldn't allocate vector.");

    v->size = size;
    v->data = PUSH_ARRAY(arena, f32, size, true);
    if (!v->data) terminate("Couldn't allocate vector array.");

    return v;
}

void vector_insert(LVector v) {
    printf("Enter values for a size %zu vector:\n", v->size);
    for (sz i = 0; i < v->size; i ++) {
        scanf("%f", &v->data[i]);
    }
}

LVector vector_add(Arena arena, LVector a, LVector b) {
    if (a->size != b->size) terminate("Can't add vectors of different length.");
    LVector v = vector_create(arena, a->size);

    for (u8 i = 0; i < v->size; i++) {
        v->data[i] = a->data[i] + b->data[i];
    }

    return v;
}

LVector vector_multiply(Arena arena, LVector a, i16 k) {
    LVector v = vector_create(arena, a->size);
    for (u8 i = 0; i < v->size; i++) {
        v->data[i] *= k;
    }

    return v;
}

f32 inner_product(LVector a, LVector b) {
    f32 result = 0.0;
    for (sz i = 0; i < a->size; i++) {
        result += a->data[i] * b->data[i];
    }

    return result;
}

LVector vector_cross(Arena arena, LVector u, LVector v) {
    if (u->size != 3 || v->size != 3) terminate("Standard cross product is only defined for 3D vectors.");

    LVector result = vector_create(arena, 3);

    result->data[0] = u->data[1] * v->data[2] - u->data[2] * v->data[1];
    result->data[1] = u->data[2] * v->data[0] - u->data[0] * v->data[2];
    result->data[2] = u->data[0] * v->data[1] - u->data[1] * v->data[0];

    return result;
}

void vector_scale(LVector v, i16 scalar) {
    for (sz i = 0; i < v->size; i++) {
        v->data[i] *= scalar;
    }
}

void vector_print(LVector v) {
    for (sz i = 0; i < v->size; i++) {
        printf("%.2f ", v->data[i]);
    }
    printf("\n");
}
