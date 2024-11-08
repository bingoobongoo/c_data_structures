# Data Structures in C language

This project is my implementation of common Data Structures in C language.

## Vector

This library implements `Vector` which is a heap allocated integer array with handy functions.

```c
typedef struct Vector {
    unsigned int size;
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
Vector vector(int arr[], unsigned int arr_size)
```

Creates new Vector object, allocating `2 * arr_size * sizeof(int)` bytes of memory on heap. Returns created `Vector`.

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
Vector copy_vec(Vector* vec)
```

Creates copy of existing `vec` and returns it.

### pop

```c
int pop(unsigned int idx, Vector* vec)
```

Removes `vec` element at specified index `idx` and returns it.

### insert_num

```c
void insert_num(int num, unsigned int idx, Vector* vec)
```

Inserts `num` into the `vec` at the specified `idx`. Elements that are further in the array will be pushed one index to the right.

### push

```c
void push(int num, Vector* vec)
```

Appends `num` to the end of the `vec`.

### push_front

```c
void push_front(int num, Vector* vec)
```

Pushes `num` to the front of `vec`.

### count_vec

```c
unsigned int count_vec(int value, Vector* vec)
```

Returns number of occurances of `value` in `vec`.

### join_vec

```c
void join_vec(Vector* vec1, Vector* vec2)
```

Appends **copy** of `vec2` to the end of `vec1`. Memory allocated for `vec2` isn't freed. If you don't want to use `vec2` anymore, remember to use [**delete_vec**](#delete_vec) function.

### reverse_vec

```c
void reverse_vec(Vector* vec)
```

Reverses the order of the elements in `vec`.

### find_value

```c
int find_value(int value, Vector* vec)
```

Using linear search to find `value` in `vec`. Return an index of the first found `value` or -1 if `value` was not found.

### remove_value

```c
void remove_value(int value, Vector* vec)
```

Removes first element with spcified `value`. If element with `value` does not exist in `vec`, nothing happens.

### print_vec

```c
void print_vec(Vector* vec)
```

Prints formatted `vec` to the console.

### debug_vec

```c
void debug_vec(Vector* vec)
```

Prints formatted debug information about `vec`.

### is_empty

```c
bool is_empty(Vector* vec)
```

Returns **true** if `vec` has no elements.

### get_len

```c
unsigned int get_len(Vector* vec)
```

Returns length of `vec`.

### get_element

```c
int get_element(unsigned int idx, Vector* vec)
```

Returns element of `vec` from specified `idx`.

### get_first

```c
int get_first(Vector* vec)
```

Returns first element of `vec`.

### get_last

```c
int get_last(Vector* vec)
```

Returns last element of `vec`.

### get_slice

```c
Vector get_slice(unsigned int start, unsigned int stop, Vector* vec)
```

Return a `Vector`, that is created from a slice of `vec`, such that first element of new `Vector` is **vec[start]** and last one is **vec[stop-1]**.
