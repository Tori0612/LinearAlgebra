#include "definitions.h"
#include "matrix.h"

static sz get_index(sz cols, u8 i, u8 j) {
    return i * cols + j;
}

Matrix matrix_create(Arena arena, sz rows, sz cols) {
    Matrix m = PUSH_STRUCT(arena, struct matrix_type, true);

    if (!m) terminate("Couldn't allocate matrix.");

    m->rows = rows;
    m->cols = cols;

    m->data = PUSH_ARRAY(arena, i16, rows * cols, true);
    if (!m->data) terminate("Couldn't allocate matrix array.");
    return m;
}

static void matrix_modify(Matrix m, u8 row, u8 col, i16 value) {
    u8 index = get_index(m->cols, row, col);
    m->data[index] = value;
}

void matrix_generate(Matrix m) {
    for (u8 i = 0; i < m->rows; i++) {
        for (u8 j = 0; j < m->cols; j++) {
            u8 index = get_index(m->cols, i, j);
            m->data[index] = (rand() % 20) + j * (i - 1);
        }
    }
}

void matrix_insert(Matrix m) {
    printf("Enter values for a %zu x %zu matrix:\n", m->rows, m->cols);

    for (u8 i = 0; i < m->rows; i++) {
        printf("Row %u (enter %zu values separated by space): ", i+1, m->cols);
        for (u8 j = 0; j < m->cols; j++) {
            sz index = get_index(m->cols, i, j);
            scanf("%hd", &m->data[index]);
        }
    }
}

Matrix matrix_add(Arena arena, Matrix a, Matrix b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        terminate("You cant add matrices of different dimensions.");
    }
    Matrix m = matrix_create(arena, a->rows, a->cols);
    for (u8 i = 0; i < a->rows; i++) {
        for (u8 j = 0; j < a->cols; j++) {
            u8 index = get_index(m->cols, i, j);
            m->data[index] = a->data[index] + b->data[index];
        }
    }
    return m;
}

Matrix matrix_multiply(Arena arena, Matrix a, Matrix b) {
    if (a->cols != b->rows) terminate("The number of cols of A should be equal to the number of rows of B");
    Matrix m = matrix_create(arena, a->rows, b->cols);
    for (u8 i = 0; i < m->rows; i++) {
        for (u8 j = 0; j < m->cols; j++) {
            u8 m_index = get_index(m->cols, i, j);
            for (u8 k = 0; k < b-> rows; k++) {
                u8 a_index = get_index(a->cols, i, k);
                u8 b_index = get_index(b->cols, k, j);
                m->data[m_index] += a->data[a_index] * b->data[b_index];
            }
        }
    }
    return m;
}

void matrix_scale(Matrix m, i16 scalar) {
    sz total_elements = m->rows * m->cols;
    for (sz i = 0; i < total_elements; i++) {
        m->data[i] *= scalar;
    }
}

void matrix_print(Matrix m) {
    for (u8 i = 0; i < m->rows; i++) {
        for (u8 j = 0; j < m->cols; j++) {
            u8 index = get_index(m->cols, i, j);
            printf("%d ", m->data[index]);
        }
        printf("\n");
    }
    printf("\n");
}
