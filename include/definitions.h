#pragma once
#include "matrix.h"
#include "vector.h"

struct matrix_type {
    sz rows;
    sz cols;
    i16 *data;
};

struct vector_type {
    sz size;
    i16* data;
};
