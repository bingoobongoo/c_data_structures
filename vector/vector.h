#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef enum VecDataType {
    VEC_INT32,
    VEC_INT64,
    VEC_FLOAT,
    VEC_DOUBLE,
} VecDataType;

typedef struct Vector {
    void* data;
    VecDataType data_type;
    int elem_size;
    int length;
    size_t capacity;
} Vector;

Vector* vector(void* arr, int length, VecDataType data_type);

Vector* vector_with_capacity(void* arr, int length, VecDataType dt, size_t cap);

Vector* zero_vector(int length, VecDataType dt);

void clear_vec(Vector* vec);

void delete_vec(Vector* vec);

Vector* copy_vec(Vector* vec);

void assign_vec(Vector* old_vec, Vector* new_vec);

void pop(int idx, Vector* vec);

void insert_num(Vector* vec, int idx, void* num);

void insert_vec(Vector* from, Vector* into, int idx);

void push(Vector* vec, void* num);

void push_front(Vector* vec, void* num);

int count_vec(Vector* vec, void* value);

void append_vec(Vector* vec, Vector* other);

void reverse_vec(Vector* vec);

int find_value(Vector* vec, void* value);

void remove_value(Vector* vec, void* value);

bool compare_vec_elem(void* elem, void* value, int elem_size);

void print_vec(Vector* vec);

void debug_vec(Vector* vec);

bool is_vec_empty(Vector* vec);

void set_vec_elem(Vector* vec, int idx, void* value);

int get_vec_len(Vector* vec);

void* get_vec_elem(Vector* vec, int idx);

void* get_vec_first(Vector* vec);

void* get_vec_last(Vector* vec);

Vector* get_slice(Vector* vec, int start, int stop);

void _copy_data(void* data_from, void* data_to, int length, int elem_size);

void* _get_data_elem(void* data, int idx, int elem_size);

void _set_data_elem(void* data, int idx, void* value, int elem_size);