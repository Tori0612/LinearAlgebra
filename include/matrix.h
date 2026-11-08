#include "base.h"

typedef struct matrix_type *LMatrix;

sz get_index(sz cols, u8 i, u8 j);

LMatrix matrix_create(Arena arena, sz rows, sz cols);
void matrix_generate(LMatrix m);
void matrix_insert(LMatrix m);
LMatrix matrix_add(Arena arena, LMatrix a, LMatrix b);
LMatrix matrix_multiply(Arena arena, LMatrix a, LMatrix b);
void matrix_scale(LMatrix m, i16 scalar);
f32 matrix_determinant(Arena arena, LMatrix m);

LMatrix matrix_image(Arena arena, LMatrix m);
LMatrix matrix_kernel(Arena arena, LMatrix m);

void matrix_print(LMatrix m);
