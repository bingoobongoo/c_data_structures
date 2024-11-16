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
    mat->data_type = vectors[0]->data_type;
    return mat;
}

Matrix* zero_matrix(unsigned int n_rows, unsigned int n_cols) {
    Vector* zero_vec = zero_vector(n_cols, VEC_INT32);
    size_t mat_capacity = sizeof(Vector*) * n_rows;
    Vector** rows = (Vector**)malloc(mat_capacity);
    for (int row=0; row<n_rows; row++) {
        rows[row] = copy_vec(zero_vec);
    }

    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->height = n_rows;
    mat->width = n_cols;
    mat->size = n_rows * n_cols;
    mat->capacity = mat_capacity;
    mat->data_type = zero_vec->data_type;

     delete_vec(zero_vec);

    return mat;
}

Matrix* copy_matrix(Matrix* mat) {
    Vector* data[mat->height];
    for (int i=0; i<mat->height; i++) {
        data[i] = copy_vec(mat->rows[i]);
    }
    Matrix* copy = matrix(data, mat->height);
    for (int i=0; i<mat->height; i++) {
        delete_vec(data[i]);
    }

    return copy;
}

void delete_matrix(Matrix* mat) {
    for (int i=0; i<mat->height; i++) {
        delete_vec(mat->rows[i]);
    }
    free(mat->rows);
    free(mat);
    mat = NULL;
}

Matrix* add_matrix(Matrix* mat1, Matrix* mat2) {
    assert(mat1->data_type == mat2->data_type);
    Vector* new_rows[mat1->height];
    for (int row=0; row<mat1->height; row++) {
        new_rows[row] = add_vector(mat1->rows[row], mat2->rows[row]);
    }
    Matrix* sum = matrix(new_rows, mat1->height);
    _free_mat_data(new_rows, mat1->height);

    return sum;
}

Matrix* mul_matrix(Matrix* mat1, Matrix* mat2) {
    assert(mat1->data_type == mat2->data_type);
    assert(mat1->width == mat2->height);
    Matrix* mul_mat = zero_matrix(mat1->height, mat2->width);
    mul_mat->data_type = mat1->data_type;
    // TODO : add data type castring for vectors
    for (int i=0; i<mul_mat->height; i++) {
        mul_mat->rows[i]->data_type = mul_mat->data_type;
    }

    for (int row = 0; row < mul_mat->height; row++) {
        for (int col = 0; col < mul_mat->width; col++) {
            switch (mul_mat->data_type) {
            case VEC_INT32: {
                int sum = 0;
                for (int i = 0; i < mat1->width; i++) {
                    int elem1 = *(int*)get_mat_elem(mat1, row, i);
                    int elem2 = *(int*)get_mat_elem(mat2, i, col);
                    sum += elem1 * elem2;
                }
                int* result = malloc(sizeof(int));
                *result = sum;
                set_mat_elem(mul_mat, row, col, result);
                free(result);
                break;
            }
            case VEC_INT64: {
                long long sum = 0;
                for (int i = 0; i < mat1->width; i++) {
                    long long elem1 = *(long long*)get_mat_elem(mat1, row, i);
                    long long elem2 = *(long long*)get_mat_elem(mat2, i, col);
                    sum += elem1 * elem2;
                }
                long long* result = malloc(sizeof(long long));
                *result = sum;
                set_mat_elem(mul_mat, row, col, result);
                free(result);
                break;
            }
            case VEC_FLOAT: {
                float sum = 0.0f;
                for (int i = 0; i < mat1->width; i++) {
                    float elem1 = *(float*)get_mat_elem(mat1, row, i);
                    float elem2 = *(float*)get_mat_elem(mat2, i, col);
                    sum += elem1 * elem2;
                }
                float* result = malloc(sizeof(float));
                *result = sum;
                set_mat_elem(mul_mat, row, col, result);
                free(result);
                break;
            }
            case VEC_DOUBLE: {
                double sum = 0.0;
                for (int i = 0; i < mat1->width; i++) {
                    double elem1 = *(double*)get_mat_elem(mat1, row, i);
                    double elem2 = *(double*)get_mat_elem(mat2, i, col);
                    sum += elem1 * elem2;
                }
                double* result = malloc(sizeof(double));
                *result = sum;
                set_mat_elem(mul_mat, row, col, result);
                free(result);
                break;
            }
            }
        }
    }

    return mul_mat;
}

void transpose_matrix(Matrix* mat) {
    int new_height = mat->width;
    int new_width = mat->height;
    Vector** new_rows = malloc(new_height * sizeof(Vector*));
    for (int i=0; i<new_height; i++) {
        new_rows[i] = vector(NULL, 0, mat->rows[0]->data_type);
    }
    for (int i=0; i<new_width; i++) {
        for (int j=0; j<new_height; j++) {
            push(new_rows[j], get_mat_elem(mat, i, j));
        }
    }
    _free_mat_data(mat->rows, mat->height);
    free(mat->rows);

    mat->rows = new_rows;
    mat->height = new_height;
    mat->width = new_width;
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
    printf("Capacity: %ld Bytes\n\n", mat->capacity);
}

void set_mat_elem(Matrix* mat, unsigned int row, unsigned int col, void* value) {
    assert(row >=0 && row <mat->height);
    assert(col >=0 && col <mat->width);
    set_vec_elem(mat->rows[row], col, value);
}

void* get_mat_elem(Matrix* mat, unsigned int row, unsigned int col) {
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

void _free_mat_data(Vector** data, int len) {
    for (int i=0; i<len; i++) {
        delete_vec(data[i]);
    }
}