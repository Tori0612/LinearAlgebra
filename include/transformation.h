#include "base.h"
#include "definitions.h"

LMatrix vec_to_mat(Arena arena, LVector v);
LVector mat_to_vec(Arena arena, LMatrix m);
LVector lin_transform(Arena arena, LMatrix t, LVector vec);
LVector* lin_kernel(Arena arena, LMatrix m);
LVector* lin_image(Arena arena, LMatrix m);

