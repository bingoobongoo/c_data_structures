#include "matrix.h"

Matrix* matrix(Vector* rows[], unsigned int n_rows) {
    assert(rows != NULL);
    assert(!_is_empty_vec_in_arr(rows, n_rows));
    assert(_is_matrix_shape_valid(rows, n_rows));

    size_t mat_capacity = sizeof(Vector*) * n_rows;
    Vector** vectors = (Vector**)malloc(mat_capacity);
    for (int i=0; i<n_rows; i++) {
        vectors[i] = copy_vec(rows[i]);
    }

    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = vectors;
    mat->height = n_rows;
    mat->width = get_vec_len(vectors[0]);
    mat->size = mat->height * mat->width;
    mat->capacity = mat_capacity;

    return mat;
}

Matrix* zero_matrix(unsigned int n_rows, unsigned int n_cols) {
    Vector* zero_vec = zero_vector(n_cols, VEC_INT32);
    size_t mat_capacity = sizeof(Vector*) * n_rows;
    Vector** rows = (Vector**)malloc(mat_capacity);
    for (int row=0; row<n_rows; row++) {
        rows[row] = copy_vec(zero_vec);
    }
    delete_vec(zero_vec);

    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->height = n_rows;
    mat->width = n_cols;
    mat->size = n_rows * n_cols;
    mat->capacity = mat_capacity;

    return mat;
}

void delete_matrix(Matrix* mat) {
    for (int i=0; i<mat->height; i++) {
        delete_vec(mat->rows[i]);
    }
    free(mat->rows);
    free(mat);
    mat = NULL;
}

void print_matrix(Matrix* mat) {
    int* column_widths = _get_columns_width(mat);
    for (int row=0; row<mat->height; row++) {
        for (int col=0; col<mat->width; col++) {
            void* num = get_vec_elem(mat->rows[row], col);
            size_t num_length = _get_num_length(num, mat->rows[row]->data_type);
            if (col == 0) {
                printf("|");
                _print_mat_elem(num, mat->rows[row]->data_type);
                _print_padding(column_widths[col] - num_length);
                printf(" ");
            }
            else if (col < mat->width-1) {
                _print_padding(column_widths[col] - num_length);
                _print_mat_elem(num, mat->rows[row]->data_type);
                printf(" ");
            }
            else if (col == mat->width-1) {
                _print_padding(column_widths[col] - num_length);
                _print_mat_elem(num, mat->rows[row]->data_type);
                printf("|\n");
            }
        }
    }

    free(column_widths);
    column_widths = NULL;
}

void debug_matrix(Matrix* mat) {
    printf("Data:\n");
    print_matrix(mat);
    printf("Dismensions: [%dx%d]\n", mat->height, mat->width);
    printf("Size: %d\n", mat->size);
    printf("Addr: %p\n", mat);
    printf("Capacity: %ld\n\n", mat->capacity);
}

void set_mat_elem(void* value, unsigned int row, unsigned int col, Matrix* mat) {
    assert(row >=0 && row <mat->height);
    assert(col >=0 && col <mat->width);
    set_vec_elem(mat->rows[row], col, value);
}

void* get_mat_elem(unsigned int row, unsigned int col, Matrix* mat) {
    assert(row >=0 && row < mat->height);
    assert(col >=0 && col < mat->width);
    return get_vec_elem(mat->rows[row], col);
}

bool _is_empty_vec_in_arr(Vector* rows[], unsigned int n_rows) {
    for (int i=0; i<n_rows; i++) {
        if (is_vec_empty(rows[i])) {
            return true;
        }
    }

    return false;
}

bool _is_matrix_shape_valid(Vector* rows[], unsigned int n_rows) {
    unsigned int n_cols = get_vec_len(rows[0]);
    for (int i=1; i<n_rows; i++) {
        if (n_cols != get_vec_len(rows[i])) {
            return false;
        }
    }

    return true;
}

void _print_padding(int n) {
    for (int i=0; i<n; i++) {
        printf(" ");
    }
}

size_t _get_num_length(void* num, VecDataType dt) {
    char str_buff[255];
    switch (dt)
    {
    case VEC_INT32:
        snprintf(str_buff, 255, "%d", *(int*)num);
        break;
    case VEC_INT64:
        snprintf(str_buff, 255, "%lld", *(long long*)num);
        break;
    case VEC_FLOAT:
        snprintf(str_buff, 255, "%f", *(float*)num);
        break;
    case VEC_DOUBLE:
        snprintf(str_buff, 255, "%lf", *(double*)num);
        break;
    }

    return strlen(str_buff);
}

int* _get_columns_width(Matrix* mat) {
    int* column_widths = (int*)calloc(mat->width, sizeof(int));
    for (int col=0; col<mat->width; col++ ) {
        char str_buff[255];
        for (int row=0; row<mat->height; row++) {
            void* elem = get_vec_elem(mat->rows[row], col);
            size_t elem_len = _get_num_length(elem, mat->rows[row]->data_type);
            int current_width = elem_len;
            if (current_width > column_widths[col]) {
                column_widths[col] = current_width;
            }
        }
    }

    return column_widths;
}

void _print_mat_elem(void* elem, VecDataType dt) {
    switch(dt) {
    case VEC_INT32:
        printf("%d", *(int*)elem);
        break;
    case VEC_INT64:
        printf("%lld", *(long long*)elem);
        break;
    case VEC_FLOAT:
        printf("%0.2f", *(float*)elem);
        break;
    case VEC_DOUBLE:
        printf("%0.2lf", *(double*)elem);
        break;
    }
}