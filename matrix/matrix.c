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
    mat->width = vectors[0]->size;
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
            int num = get_element(col, mat->rows[row]);
            if (col == 0) {
                printf("|%d", num);
                _print_padding(column_widths[col] - _get_int_length(num));
                printf(" ");
            }
            else if (col < mat->width-1) {
                _print_padding(column_widths[col] - _get_int_length(num));
                printf("%d", num);
                printf(" ");
            }
            else if (col == mat->width-1) {
                _print_padding(column_widths[col] - _get_int_length(num));
                printf("%d", num);
                printf("|\n");
            }
        }
    }

    free(column_widths);
    column_widths = NULL;
}

void debug_matrix(Matrix* mat) {
    printf("Data:\n");
    print_matrix(mat); printf("\n");
    printf("Addr: %p\n", mat);
    printf("Height: %d\n", mat->height);
    printf("Width: %d\n", mat->width);
    printf("Capacity: %ld\n", mat->capacity);
}

bool _is_empty_vec_in_arr(Vector* rows[], unsigned int n_rows) {
    for (int i=0; i<n_rows; i++) {
        if (rows[i] == NULL || is_empty(rows[i])) {
            return true;
        }
    }

    return false;
}

bool _is_matrix_shape_valid(Vector* rows[], unsigned int n_rows) {
    unsigned int n_cols = get_len(rows[0]);
    for (int i=1; i<n_rows; i++) {
        if (n_cols != get_len(rows[i])) {
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

size_t _get_int_length(int num) {
    char str_buff[255];
    snprintf(str_buff, 255, "%d", num);

    return strlen(str_buff);
}

int* _get_columns_width(Matrix* mat) {
    int* column_widths = (int*)calloc(mat->width, sizeof(int));
    for (int col=0; col<mat->width; col++ ) {
        char str_buff[255];
        for (int row=0; row<mat->height; row++) {
            snprintf(str_buff, 255, "%d", get_element(col, mat->rows[row]));
            int current_width = strlen(str_buff);
            if (current_width > column_widths[col]) {
                column_widths[col] = current_width;
            }
        }
    }

    return column_widths;
}