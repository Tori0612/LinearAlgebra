#include "base.h"

typedef struct vector_type *LVector;

LVector vector_create(Arena arena, sz size);
void vector_insert(LVector v);
LVector vector_add(Arena arena, LVector a, LVector b);
LVector vector_multiply(Arena arena, LVector a, i16 k);
f32 inner_product(LVector a, LVector b);
LVector vector_cross(Arena arena, LVector u, LVector v);
void vector_scale(LVector v, i16 scalar);

void vector_print(LVector v, char c);
