#include "base.h"

typedef struct matrix_type *LMatrix;

LMatrix matrix_create(Arena arena, sz rows, sz cols);
void matrix_generate(LMatrix m);
void matrix_insert(LMatrix m);
LMatrix matrix_add(Arena arena, LMatrix a, LMatrix b);
LMatrix matrix_multiply(Arena arena, LMatrix a, LMatrix b);
void matrix_scale(LMatrix m, i16 scalar);

void matrix_print(LMatrix m);
