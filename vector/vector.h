#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Vector {
    unsigned int size;
    size_t capacity;
    int* data;
} Vector;

Vector vector(int arr[], unsigned int arr_size);

void delete_vec(Vector* vec);

void clear_vec(Vector* vec);

Vector copy_vec(Vector* vec);

int pop(unsigned int idx, Vector* vec);

void insert_num(int num, unsigned int idx, Vector* vec);

void push(int num, Vector* vec);

void push_front(int num, Vector* vec);

unsigned int count_vec(int value, Vector* vec);

void join_vec(Vector* vec1, Vector* vec2);

void reverse_vec(Vector* vec);

int find_value(int value, Vector* vec);

void remove_value(int value, Vector* vec);

void print_vec(Vector* vec);

void debug_vec(Vector* vec);

bool is_empty(Vector* vec);

unsigned int get_len(Vector* vec);

int get_element(unsigned int idx, Vector* vec);

int get_first(Vector* vec);

int get_last(Vector* vec);

Vector get_slice(unsigned int start, unsigned int stop, Vector* vec);