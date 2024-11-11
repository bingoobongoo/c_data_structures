# Vector

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

## vector

```c
Vector* vector(void* arr, int length, VecDataType data_type)
```

Creates new Vector object, allocating `2 * arr_size * elem_size` bytes of memory on heap.
Returns pointer to created `Vector`.

## vector_with_capacity

```c
Vector* vector_with_capacity(void* arr, int length, VecDataType dt, size_t cap)
```

Returns pointer to a `Vector`, that is created with `capacity` given by the user.

## zero_vector

```c
Vector* zero_vector(int length, VecDataType dt);
```

Returns a pointer to a `Vector` filled with 0 values with specified `dt` data type.

## clear_vec

```c
void clear_vec(Vector* vec)
```

Deletes all elements of `vec`. Frees memory allocated to a `data` array of `vec`.

## delete_vec

```c
void delete_vec(Vector* vec)
```

Deletes all elements of `vec`, and frees all memory allocated to a `vec` and it's members.

## copy_vec

```c
Vector* copy_vec(Vector* vec)
```

Creates copy of existing `vec` and returns pointer to it.

## assign_vec

```c
void assign_vec(Vector* old_vec, Vector* new_vec)
```

Frees all memory allocated to `old_vec` data and assigns all properties and data of `new_vec` to `old_vec`.
This works like [**copy_vec()**](#copy_vec), except no new heap memory is allocated.

## pop

```c
void pop(int idx, Vector* vec)
```

Removes `vec` element at specified index `idx` and returns it.

## insert_num

```c
void insert_num(Vector* vec, int idx, void* num)
```

Inserts `num` into the `vec` at the specified `idx`.
Elements that are further in the array will be pushed one index to the right.

## insert_vec

```c
void insert_vec(Vector* from, Vector* into, int idx)
```

Inserts contents of `from` into `into` vector at index `idx`.
Note, that `from` vector isn't freed and is still in memory.
Use [**delete_vec()**](#delete_vec) to free `from` memory if needed.

## push

```c
void push(Vector* vec, void* num)
```

Appends `num` to the end of the `vec`.

## push_front

```c
void push_front(Vector* vec, void* num)
```

Pushes `num` to the front of `vec`.

## count_vec

```c
int count_vec(Vector* vec, void* value)
```

Returns number of occurances of `value` in `vec`.

## join_vec

```c
void append_vec(Vector* vec, Vector* other)
```

Appends **copy** of `other` to the end of `vec1`.
Memory allocated for `other` isn't freed.
If you don't want to use `vec2` data anymore, remember to use [**delete_vec**](#delete_vec) function.

## reverse_vec

```c
void reverse_vec(Vector* vec)
```

Reverses the order of the elements in `vec`.

## find_value

```c
int find_value(Vector* vec, void* value);
```

Using linear search to find `value` in `vec`.
Return an index of the first found `value` or -1 if `value` was not found.

## remove_value

```c
void remove_value(Vector* vec, void* value)
```

Removes first element with spcified `value`.
If element with `value` does not exist in `vec`, nothing happens.

## compare_vec_elem

```c
bool compare_vec_elem(void* elem, void* value, int elem_size)
```

Takes pointers to 2 numbers and returns **true** if `elem` == `value`.

## print_vec

```c
void print_vec(Vector* vec)
```

Prints formatted `vec` to the console.

## debug_vec

```c
void debug_vec(Vector* vec)
```

Prints formatted debug information about `vec`.

## is_empty

```c
bool is_vec_empty(Vector* vec)
```

Returns **true** if `vec` has no elements.

## set_element

```c
void set_vec_elem(Vector* vec, int idx, void* value)
```

Sets value of `vec` element at index `idx` to `value`.

## get_len

```c
int get_vec_len(Vector* vec)
```

Returns length of `vec`.

## get_element

```c
void* get_vec_elem(Vector* vec, int idx)
```

Returns element of `vec` from specified `idx`.

## get_first

```c
void* get_vec_first(Vector* vec)
```

Returns first element of `vec`.

## get_last

```c
void* get_vec_last(Vector* vec)
```

Returns last element of `vec`.

## get_slice

```c
Vector* get_slice(Vector* vec, int start, int stop)
```

Return a pointer to the `Vector`, that is created from a slice of `vec`,
such that first element of new `Vector` is `vec`[start] and last one is `vec`[stop-1].
