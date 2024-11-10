#pragma once

#include <string.h>
#include "../vector/vector.h"

typedef struct Matrix {
    Vector** rows;
    unsigned int height;
    unsigned int width;
    unsigned int size;
    size_t capacity;
} Matrix;

Matrix* matrix(Vector* rows[], unsigned int n_rows);

Matrix* zero_matrix(unsigned int n_rows, unsigned int n_cols);

void delete_matrix(Matrix* mat);

Matrix* add_matrix(Matrix* mat1, Matrix* mat2);

void print_matrix(Matrix* mat);

void debug_matrix(Matrix* mat);

void set_mat_elem(int value, unsigned int row, unsigned int col, Matrix* mat);

int get_mat_elem(unsigned int row, unsigned int col, Matrix* mat);

bool _is_empty_vec_in_arr(Vector* rows[], unsigned int n_rows);

bool _is_matrix_shape_valid(Vector* rows[], unsigned int n_rows);

void _print_padding(int n);

size_t _get_int_length(int num);

int* _get_columns_width(Matrix* mat);