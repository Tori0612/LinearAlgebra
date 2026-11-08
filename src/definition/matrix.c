#include "base.h"
#include "definitions.h"
#include "random.h"
#include <math.h>
#include "matrix.h"

sz get_index(sz cols, u8 i, u8 j) {
    return i * cols + j;
}

static void swap_rows(LMatrix m, sz row1, sz row2) {
    if (row1 == row2) return;
    for (sz j = 0; j < m->cols; j++) {
        sz idx1 = get_index(m->cols, row1, j);
        sz idx2 = get_index(m->cols, row2, j);

        f32 tmp = m->data[idx1];
        m->data[idx1] = m->data[idx2];
        m->data[idx2] = tmp;
    }
}

static LMatrix matrix_rref(Arena arena, LMatrix m) {
    LMatrix rref = matrix_create(arena, m->rows, m->cols);
    for (sz i = 0; i < m->rows * m->cols; i++) {
        rref->data[i] = m->data[i];
    }

    sz r = 0;
    sz c = 0;

    while (r < rref->rows && c < rref->cols) {
        sz max_r = r;
        f32 max_val = fabs(rref->data[get_index(rref->cols, r, c)]);

        for (sz i = r + 1; i < rref->rows; i++) {
            f32 val = fabs(rref->data[get_index(rref->cols, i, c)]);
            if (val > max_val) {
                max_val = val;
                max_r = i;
            }
        }
        if (max_val < 1e-6) {
            c++;
            continue;
        }

        if (max_r != r) { swap_rows(rref, r, max_r); }

        f32 pivot = rref->data[get_index(rref->cols, r, c)];
        for (sz j = c; j < rref->cols; j++) {
            rref->data[get_index(rref->cols, r, j)] /= pivot;
        };

        for (sz i = 0; i < rref->rows; i++) {
            if (i == r) continue;

            f32 factor = rref->data[get_index(rref->cols, i, c)];
            for (sz j = c; j < rref->cols; j++) {
                rref->data[get_index(rref->cols, i, j)] -= factor * rref->data[get_index(rref->cols, r, j)];
            }
        }
        r++;
        c++;
    }
    return rref;
}

LMatrix matrix_create(Arena arena, sz rows, sz cols) {
    LMatrix m = PUSH_STRUCT(arena, struct matrix_type, true);

    if (!m) terminate("Couldn't allocate matrix.");

    m->rows = rows;
    m->cols = cols;

    m->data = PUSH_ARRAY(arena, f32, rows * cols, true);
    if (!m->data) terminate("Couldn't allocate matrix array.");
    return m;
}

// static void matrix_modify(LMatrix m, u8 row, u8 col, i16 value) {
//     u8 index = get_index(m->cols, row, col);
//     m->data[index] = value;
// }

void matrix_generate(LMatrix m) {
    for (u8 i = 0; i < m->rows; i++) {
        for (u8 j = 0; j < m->cols; j++) {
            m->data[get_index(m->cols, i, j)] = (prng_rand() % 30)/* \* ((i - j) \* -1)*/;
        }
    }
}

void matrix_insert(LMatrix m) {
    printf("Enter values for a %zu x %zu matrix:\n", m->rows, m->cols);

    for (u8 i = 0; i < m->rows; i++) {
        printf("Row %u (enter %zu values separated by space): ", i+1, m->cols);
        for (u8 j = 0; j < m->cols; j++) {
            sz index = get_index(m->cols, i, j);
            scanf("%f", &m->data[index]);
        }
    }
}

LMatrix matrix_add(Arena arena, LMatrix a, LMatrix b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        terminate("You cant add matrices of different dimensions.");
    }
    LMatrix m = matrix_create(arena, a->rows, a->cols);
    for (u8 i = 0; i < a->rows; i++) {
        for (u8 j = 0; j < a->cols; j++) {
            u8 index = get_index(m->cols, i, j);
            m->data[index] = a->data[index] + b->data[index];
        }
    }
    return m;
}

LMatrix matrix_multiply(Arena arena, LMatrix a, LMatrix b) {
    if (a->cols != b->rows) terminate("The number of cols of A should be equal to the number of rows of B");
    LMatrix m = matrix_create(arena, a->rows, b->cols);
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

void matrix_scale(LMatrix m, i16 scalar) {
    sz total_elements = m->rows * m->cols;
    for (sz i = 0; i < total_elements; i++) {
        m->data[i] *= scalar;
    }
}

f32 matrix_determinant(Arena arena, LMatrix m) {
    if (m->rows != m->cols) terminate("Determinant can only be calculated for square matrices.");

    sz n = m->rows;

    if (n == 2) {
        return m->data[0] * m->data[3] - (m->data[1] * m->data[2]);
    }
    if (n == 3) {
        return m->data[0] * (m->data[4] * m->data[8] - (m->data[5] * m->data[7])) -
               m->data[1] * (m->data[3] * m->data[8] - (m->data[5] * m->data[6])) +
               m->data[2] * (m->data[3] * m->data[7] - (m->data[4] * m->data[6]));
    }

    LMatrix clone = matrix_create(arena, m->rows, m->cols);
    for (sz i = 0; i < n * n; i ++) {
        clone->data[i] = m->data[i];
    }
    f32 det = 1.0f;

    for (sz i = 0; i < n; i++) {
        sz max_row = i;
        f32 max_val = fabs(clone->data[get_index(clone->cols, i, i)]);
        for (sz k = i + 1; k < n; k++) {
            f32 curr_val = fabs(clone->data[get_index(clone->cols, k, i)]);
            if (curr_val > max_val) {
                max_val = curr_val;
                max_row = k;
            }
        }
        if (max_val < 1e-6) {
            return 0.0f;
        }

        if (max_row != i) {
            det *= -1.0f;
            swap_rows(clone, i, max_row);
        }
        
        f32 pivot = clone->data[get_index(clone->cols, i, i)];

        for (sz j = i + 1; j < n; j++) {
            f32 factor = clone->data[get_index(clone->cols, j, i)] / pivot;
            for (sz k = i; k < n; k++) {
                sz target_idx = get_index(clone->cols, j, k);
                sz pivot_idx = get_index(clone->cols, i, k);
                clone->data[target_idx] -= factor * clone->data[pivot_idx];
            }
        }
    }
    for (sz i = 0; i < n; i++) {
        det *= clone->data[get_index(clone->cols, i, i)];
    }
    return det;
}

LMatrix matrix_image(Arena arena, LMatrix m) {
    LMatrix rref = matrix_rref(arena, m);

    b32* is_pivot_col = PUSH_ARRAY(arena, b32, m->cols, true);
    sz rank = 0;

    for (sz i = 0; i < rref->rows; i++) {
        for (sz j = 0; j < rref->cols; j++) {
            if (fabs(rref->data[get_index(rref->cols, i, j)]) > 1e-6) {
                is_pivot_col[j] = 1;
                rank++;
                break;
            }
        }
    }
    if (rank == 0) {
        return matrix_create(arena, m->rows, 0);
    }

    LMatrix image = matrix_create(arena, m->rows, rank);
    sz current_img_col = 0;

    for (sz j = 0; j < m->cols; j++) {
        if (is_pivot_col[j]) {
            for (sz i = 0; i < m->rows; i++) {
                image->data[get_index(image->cols, i, current_img_col)] = m->data[get_index(m->cols, i, j)];
            }
            current_img_col++;
        }
    }
    return image;
}

LMatrix matrix_kernel(Arena arena, LMatrix m) {
    LMatrix rref = matrix_rref(arena, m);

    b32* is_pivot_col = PUSH_ARRAY(arena, b32, m->cols, true);
    sz* pivot_row_for_col = PUSH_ARRAY(arena, sz, m->cols, true);
    sz rank = 0;

    for (sz i = 0; i < rref->rows; i++) {
        for (sz j = 0; j < rref->cols; j++) {
            if (fabs(rref->data[get_index(rref->cols, i, j)]) > 1e-6) {
                is_pivot_col[j] = 1;
                pivot_row_for_col[j] = i;
                rank++;
                break;
            }
        }
    }

    sz nullity = m->cols - rank;

    if (nullity == 0) {
        return matrix_create(arena, m->cols, 1);
    }

    LMatrix kernel = matrix_create(arena, m->cols, nullity);
    sz current_free_idx = 0;

    for (sz j = 0; j < m->cols; j++) {
        if (!is_pivot_col[j]) {
            kernel->data[get_index(kernel->cols, j, current_free_idx)] = 1.0f;

            for (sz p = 0; p < m->cols; p++) {
                if (is_pivot_col[p]) {
                    sz pivot_row = pivot_row_for_col[p];
                    f32 val = -rref->data[get_index(rref->cols, pivot_row, j)];
                    kernel->data[get_index(kernel->cols, p, current_free_idx)] = val;
                }
            }
            current_free_idx++;
        }
    }
    return kernel;
}

void matrix_print(LMatrix m) {
    for (u8 i = 0; i < m->rows; i++) {
        for (u8 j = 0; j < m->cols; j++) {
            u8 index = get_index(m->cols, i, j);
            printf("%.2f  ", m->data[index]);
        }
        printf("\n");
    }
    printf("\n");
}

