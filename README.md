# Data Structures in C language

This project is my implementation of common Data Structures in C language.

## Vector

This library implements `Vector` which is a heap allocated array with handy functions.

```c
typedef struct Vector {
    void* data;
    VecDataType data_type;
    int elem_size;
    int length;
    size_t capacity;
} Vector;;
```

Vector has 5 fields:

* `data` - pointer to a heap allocated array in which actual vector's data is stored
* `data_type` - enum that stores information about type of data stored in vector
* `elem_size` - auxiliary field that stores size of stored data type used for pointer arithmetic
* `size` - number of elements in vector
* `capacity` - memory (in bytes) is currently allocated for `data`

Along with `Vector`, there is also `VecDataType`, which is custom enum that stores information about type of stored data in `Vector`.

```c
typedef enum VecDataType {
    VEC_INT32,
    VEC_INT64,
    VEC_FLOAT,
    VEC_DOUBLE,
} VecDataType;
```

Every enum value corresponds to existing C basic data type:

* `VEC_INT32` - int
* `VEC_INT64` - long long int
* `VEC_FLOAT` - float
* `VEC_DOUBLE` - double

See the documentation for Vector [here](vector/VECTOR.md).
