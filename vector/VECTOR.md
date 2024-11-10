# Vector

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

## vector

```c
Vector* vector(int arr[], unsigned int arr_size)
```

Creates new Vector object, allocating `2 * arr_size * sizeof(int)` bytes of memory on heap. Returns pointer to created `Vector`.

## vector_with_capacity

```c
Vector* vector_with_capacity(int arr[], unsigned int arr_size, size_t capacity)
```

Returns pointer to a `Vector`, that is created with `capacity` given by the user.

## clear_vec

```c
void clear_vec(Vector* vec)
```

Deletes all elements of `vec`. Frees memory allocated to a `data` array of `vec`.

## delete_vec

```c
void delete_vec(Vector* vec)
```

Deletes all elements of `vec`, and frees all memory allocated by `vec` and it's members.

## copy_vec

```c
Vector* copy_vec(Vector* vec)
```

Creates copy of existing `vec` and returns pointer to it.

## pop

```c
int pop(unsigned int idx, Vector* vec)
```

Removes `vec` element at specified index `idx` and returns it.

## insert_num

```c
void insert_num(int num, unsigned int idx, Vector* vec)
```

Inserts `num` into the `vec` at the specified `idx`. Elements that are further in the array will be pushed one index to the right.

## insert_vec

```c
void insert_vec(Vector* from, Vector* into, int idx)
```

Inserts contents of `from` into `into` vector at index `idx`. Note, that `from` vector isn't freed and is still in memory. Use [**delete_vec**](#delete_vec) to free `from` memory if needed.

## push

```c
void push(int num, Vector* vec)
```

Appends `num` to the end of the `vec`.

## push_front

```c
void push_front(int num, Vector* vec)
```

Pushes `num` to the front of `vec`.

## count_vec

```c
unsigned int count_vec(int value, Vector* vec)
```

Returns number of occurances of `value` in `vec`.

## join_vec

```c
void join_vec(Vector* vec1, Vector* vec2)
```

Appends **copy** of `vec2` to the end of `vec1`. Memory allocated for `vec2` isn't freed. If you don't want to use `vec2` data anymore, remember to use [**delete_vec**](#delete_vec) function.

## reverse_vec

```c
void reverse_vec(Vector* vec)
```

Reverses the order of the elements in `vec`.

## find_value

```c
int find_value(int value, Vector* vec)
```

Using linear search to find `value` in `vec`. Return an index of the first found `value` or -1 if `value` was not found.

## remove_value

```c
void remove_value(int value, Vector* vec)
```

Removes first element with spcified `value`. If element with `value` does not exist in `vec`, nothing happens.

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
bool is_empty(Vector* vec)
```

## set_element

```c
void set_element(int value, unsigned int idx, Vector* vec)
```

Sets value of `vec` element at index `idx` to `value`.

Returns **true** if `vec` has no elements.

## get_len

```c
unsigned int get_len(Vector* vec)
```

Returns length of `vec`.

## get_element

```c
int get_element(unsigned int idx, Vector* vec)
```

Returns element of `vec` from specified `idx`.

## get_first

```c
int get_first(Vector* vec)
```

Returns first element of `vec`.

## get_last

```c
int get_last(Vector* vec)
```

Returns last element of `vec`.

## get_slice

```c
Vector* get_slice(unsigned int start, unsigned int stop, Vector* vec)
```

Return a pointer to the`Vector`, that is created from a slice of `vec`, such that first element of new `Vector` is **vec[start]** and last one is **vec[stop-1]**.
