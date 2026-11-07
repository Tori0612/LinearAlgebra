#include "systems.h"
#include "base.h"
#include "definitions.h"
#include <math.h>

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

LVector matrix_solve_system(Arena arena, LMatrix m) {
    if (m->cols != m->rows + 1) {
        terminate("Matrix must be an augmented matrix (cols == rows + 1).");
    }

    sz n = m->rows;

    LMatrix clone = matrix_create(arena, m->rows, m->cols);
    for (sz i = 0; i < m->rows * m->cols; i++) {
        clone->data[i] = m->data[i];
    }

    for (sz i = 0; i < n; i++) {
        sz max_row = i;
        f32 max_val = fabs(clone->data[get_index(clone->cols, i, i)]);

        for (sz k = i +1; k < n; k++) {
            f32 current_val = fabs(clone->data[get_index(clone->cols, k, i)]);
            if (current_val > max_val) {
                max_val = current_val;
                max_row = k;
            }
        }
        if (max_val < 1e-6) {
            terminate("Matrix is singular (no unique solution).");
        }

        swap_rows(clone, i, max_row);

        f32 pivot = clone->data[get_index(clone->cols, i, i)];
        for (sz j = i; j < clone->cols; j++) {
            clone->data[get_index(clone->cols, i, j)] /= pivot;
        }

        for (sz j = 0; j < n; j++) {
            if (j != i) {
                f32 factor = clone->data[get_index(clone->cols, j, i)];
                for (sz k = i; k < clone->cols; k++) {
                    f32 pivot_row_val = clone->data[get_index(clone->cols, i, k)];
                    clone->data[get_index(clone->cols, j, k)] -= factor * pivot_row_val;
                }
            }
        }
    }
    LVector solutions = vector_create(arena, n);

    for (sz i = 0; i < n; i++) {
        sz last_col_idx = get_index(clone->cols, i, clone->cols - 1);
        solutions->data[i] = clone->data[last_col_idx];
    }

    return solutions;
}
