#include "base.h"
#include "definitions.h"
#include "operations.h"

int main(void) {
    Arena arena = arena_create(MiB(5));

    do_cross(arena);

    arena_print_usage(arena);
    arena_destroy(arena);
    return 0;
}
