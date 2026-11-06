#include "base.h"

typedef struct matrix_type *Matrix;

Matrix matrix_create(Arena arena, sz rows, sz cols);
void matrix_generate(Matrix m);
void matrix_insert(Matrix m);
Matrix matrix_add(Arena arena, Matrix a, Matrix b);
Matrix matrix_multiply(Arena arena, Matrix a, Matrix b);
void matrix_scale(Matrix m, i16 scalar);

void matrix_print(Matrix m);
