# Matrix

```c
typedef struct Matrix {
    Vector** rows;
    unsigned int height;
    unsigned int width;
    unsigned int size;
    size_t capacity;
} Matrix;
```

## matrix

```c
Matrix* matrix(Vector* rows[], unsigned int n_rows)
```

Constructor function for `Matrix`. Returns a pointer to a created matrix.

## zero_matrix

```c
Matrix* zero_matrix(unsigned int n_rows, unsigned int n_cols)
```

Creates a `Matrix` with only zero values. Returns a pointer to a created matrix.

## delete_matrix

```c
void delete_matrix(Matrix* mat)
```

Frees memory allocated by all `mat` fields, as well as `mat` itself.

## debug_matrix

```c
void debug_matrix(Matrix* mat)
```

Prints all debugging information about `mat`.

## set_mat_elem

```c
void set_mat_elem(Matrix* mat, unsigned int row, unsigned int col, void* value)
```

Sets `mat` element at specified position to a `value`.

## get_mat_elem

```c
void* get_mat_elem(Matrix* mat, unsigned int row, unsigned int col)
```

Returns pointer to a `mat` element at specified position.
