#include "base.h"
#include "matrix.h"
#include "vector.h"

int main(void) {
    Arena arena = arena_create(MiB(5));
    Matrix m = matrix_create(arena, 2, 3);
    matrix_insert(m);
    Matrix n = matrix_create(arena, 3, 2);
    matrix_insert(n);

    Matrix r = matrix_multiply(arena, m, n);
    matrix_print(m);
    matrix_print(n);
    matrix_print(r);
    return 0;
}
