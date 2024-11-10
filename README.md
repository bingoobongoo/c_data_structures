# Data Structures in C language

This project is my implementation of common Data Structures in C language.

## Vector

This library implements `Vector` which is a heap allocated integer array with handy functions.

```c
typedef struct Vector {
    int* data;
    unsigned int size;
    size_t capacity;
} Vector;
```

Vector has 3 fields:

* `data` - pointer to a heap allocated array in which actual vector's data is stored
* `size` - number of elements in vector
* `capacity` - memory (in bytes) is currently allocated for `data`

See the documentation for Vector [here](vector/VECTOR.md).
