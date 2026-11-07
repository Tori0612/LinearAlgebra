#include "transformation.h"
#include "definitions.h"

LMatrix vec_to_mat(Arena arena, LVector v) {
    LMatrix m = matrix_create(arena, v->size, v->size);
    for (sz i = 0; i < m->rows; i++) {
        m->data[get_index(m->cols, i, 0)] = v->data[i];
    }
    return m;
}

LVector mat_to_vec(Arena arena, LMatrix m) {
    LVector vec = vector_create(arena, m->rows);
    for (sz i = 0; i < vec->size; i++) {
        vec->data[i] = m->data[get_index(m->cols, i, 0)];
    }
    return vec;
}

LVector lin_transform(Arena arena, LMatrix t, LVector vec) {
    LMatrix resulting = matrix_create(arena, vec->size, 1);
    LMatrix mat = vec_to_mat(arena, vec);
    resulting = matrix_multiply(arena, t, mat);
    LVector final = mat_to_vec(arena, resulting);

    return final;
}
