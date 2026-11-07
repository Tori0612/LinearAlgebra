#pragma once
#include "matrix.h"
#include "vector.h"

struct matrix_type {
    sz rows;
    sz cols;
    f32 *data;
};

struct vector_type {
    sz size;
    f32* data;
};
