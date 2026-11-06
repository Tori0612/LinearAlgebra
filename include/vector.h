#include "base.h"

typedef struct vector_type *LVector;

LVector vector_create(Arena arena, sz size);
LVector vector_add(Arena arena, LVector a, LVector b);
LVector vector_multiply(Arena arena, LVector a, i16 k);
i16 inner_product(LVector a, LVector b);

void vector_scale(LVector v, i16 scalar);
