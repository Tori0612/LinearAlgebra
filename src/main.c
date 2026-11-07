#include "base.h"
#include "definitions.h"
#include "operations.h"
#include <stdio.h>

int main(void) {
    Arena arena = arena_create(MiB(5));
    do_determinant(arena);
    return 0;
}
