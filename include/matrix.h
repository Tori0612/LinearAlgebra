#include "base.h"

typedef struct matrix_type *LMatrix;

sz get_index(sz cols, u8 i, u8 j);

LMatrix matrix_create(Arena arena, sz rows, sz cols);
void matrix_generate(LMatrix m);
void matrix_insert(LMatrix m);
void matrix_copy(LMatrix dst, const LMatrix src);
void matrix_clear(LMatrix m);

LMatrix matrix_add(Arena arena, const LMatrix a, const LMatrix b);
LMatrix matrix_multiply(Arena arena, const LMatrix a, const LMatrix b,
        b8 zero_out, b32 transpose_a, b32 transpose_b);
void matrix_scale(LMatrix m, i16 scalar);

f32 matrix_determinant(Arena arena, LMatrix m);

LMatrix matrix_image(Arena arena, const LMatrix m);
LMatrix matrix_kernel(Arena arena, const LMatrix m);

void matrix_print(LMatrix m);
