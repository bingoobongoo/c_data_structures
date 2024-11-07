# Data Structures in C language

This project is my implementation of common Data Structures in C language.

## Vector

This library implements `Vector` which is a heap allocated integer array with handy functions.

```c
typedef struct Vector {
    size_t size;
    size_t capacity;
    int* data;
} Vector;
```

Vector has 3 fields:

* `size` - number of elements in vector
* `capacity` - memory (in bytes) is currently allocated for `data`
* `data` - pointer to a heap allocated array in which actual vector's data is stored

### vector

```c
Vector* vector(int arr[], int arr_size)
```

Creates new Vector object, allocating `2 * arr_size * sizeof(int)` bytes of memory on heap. Returns pointer to created `Vector`.

### delete_vec

```c
void delete_vec(Vector* vec)
```

Frees all memory allocated to all `vec` fields, as well as the memory allocated do `data` array.

### clear_vec

```c
void clear_vec(Vector* vec)
```

Deletes all elements of `vec`. Frees memory allocated to a `data` array of `vec`.

### copy_vec

```c
Vector* copy_vec(Vector* vec)
```

Creates copy of existing `vec`.

### pop

```c
int pop(unsigned int idx, Vector* vec)
```

Removes `vec` element at specified index `idx` and returns it.