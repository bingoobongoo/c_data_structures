#pragma once

#include <string.h>
#include "../vector/vector.h"

typedef struct Matrix {
    Vector** rows;
    unsigned int height;
    unsigned int width;
    size_t capacity;
} Matrix;

Matrix* matrix(Vector* rows[], unsigned int n_rows);

void delete_matrix(Matrix* mat);

void print_matrix(Matrix* mat);

void debug_matrix(Matrix* mat);

bool _is_empty_vec_in_arr(Vector* rows[], unsigned int n_rows);

bool _is_matrix_shape_valid(Vector* rows[], unsigned int n_rows);

void _print_padding(int n);

size_t _get_int_length(int num);

int* _get_columns_width(Matrix* mat);