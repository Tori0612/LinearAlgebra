#include "definitions.h"
#include "vector.h"

LVector vector_create(Arena arena, sz size) {
    LVector v = PUSH_STRUCT(arena, struct vector_type, true);
    if (!v) terminate("Couldn't allocate vector.");

    v->size = size;
    v->data = PUSH_ARRAY(arena, i16, size, true);
    if (!v->data) terminate("Couldn't allocate vector array.");

    return v;
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

i16 inner_product(LVector a, LVector b) {
    i16 result = 0;
    for (sz i = 0; i < a->size; i++) {
        result += a->data[i] * b->data[i];
    }

    return result;
}

void vector_scale(LVector v, i16 scalar) {
    for (sz i = 0; i < v->size; i++) {
        v->data[i] *= scalar;
    }
}
