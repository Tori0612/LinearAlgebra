#include "definitions.h"
#include "vector.h"

Vector vector_create(Arena arena, sz size) {
    Vector v = PUSH_STRUCT(arena, struct vector_type, true);
    if (!v) terminate("Couldn't allocate vector.");

    v->size = size;
    v->data = PUSH_ARRAY(arena, i16, size, true);
    if (!v->data) terminate("Couldn't allocate vector array.");

    return v;
}

Vector vector_add(Arena arena, Vector a, Vector b) {
    if (a->size != b->size) terminate("Can't add vectors of different length.");
    Vector v = vector_create(arena, a->size);

    for (u8 i = 0; i < v->size; i++) {
        v->data[i] = a->data[i] + b->data[i];
    }

    return v;
}

Vector vector_multiply(Arena arena, Vector a, i16 k) {
    Vector v = vector_create(arena, a->size);
    for (u8 i = 0; i < v->size; i++) {
        v->data[i] *= k;
    }

    return v;
}

i16 inner_product(Vector a, Vector b) {
    i16 result = 0;
    for (sz i = 0; i < a->size; i++) {
        result += a->data[i] * b->data[i];
    }

    return result;
}

void vector_scale(Vector v, i16 scalar) {
    for (sz i = 0; i < v->size; i++) {
        v->data[i] *= scalar;
    }
}
