#include "base.h"

typedef struct vector_type *Vector;

Vector vector_create(Arena arena, sz size);
Vector vector_add(Arena arena, Vector a, Vector b);
Vector vector_multiply(Arena arena, Vector a, i16 k);
i16 inner_product(Vector a, Vector b);

void vector_scale(Vector v, i16 scalar);
