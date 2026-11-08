#include "base.h"
#include "definitions.h"
#include "operations.h"
// #include <stdio.h>

int main(void) {
    Arena arena = arena_create(MiB(5));

    LMatrix m = matrix_create(arena, 2, 2);
    matrix_insert(m);
    LMatrix image = matrix_image(arena, m);
    matrix_print(image);

    arena_print_usage(arena);
    arena_destroy(arena);
    return 0;
}
