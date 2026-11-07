#include "operations.h"
#include <stdio.h>

void do_cross(Arena arena) {
    LVector u =  vector_create(arena, 3);
    vector_insert(u);
    LVector v =  vector_create(arena, 3);
    vector_insert(v);

    LVector vec = vector_cross(arena, u, v);
    vector_print(vec);
}

void do_systems(Arena arena) {
    sz vars;
    printf("Enter the number of variables: ");
    scanf("%zu", &vars);

    LMatrix m = matrix_create(arena, vars, vars+1);
    matrix_insert(m);
    LVector vec =  matrix_solve_system(arena, m);
    vector_print(vec);

}

void do_determinant(Arena arena) {
    sz dim;
    printf("Enter the matrix dimensions (e.g. 2): ");
    scanf("%zu", &dim);
    LMatrix matrix = matrix_create(arena, dim, dim);
    matrix_insert(matrix);
    f32 det = matrix_determinant(arena, matrix);
    printf("Det: %.2f", det);
}
