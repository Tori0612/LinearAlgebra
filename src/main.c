#include "base.h"
#include "definitions.h"
#include "operations.h"
// #include <stdio.h>

int main(void) {
    Arena arena = arena_create(MiB(5));
    LMatrix m = matrix_create(arena, 3, 3);
    matrix_generate(m);
    matrix_print(m);
    return 0;
}
