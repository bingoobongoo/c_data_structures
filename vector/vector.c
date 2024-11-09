#include "vector.h"

Vector* vector(int arr[], unsigned int arr_size) {
    size_t capacity = 2 * arr_size * sizeof(int);
    int* data = (int*)malloc(capacity);
    if (arr_size == 0) {
        data = NULL;
    }
    else {
        for (int i=0; i<arr_size; i++) {
            data[i] = arr[i];
        }
    }

    Vector* vec = (Vector*)malloc(sizeof(Vector));
    vec->size = arr_size;
    vec->capacity = capacity;
    vec->data = data;

    return vec;
}

Vector* vector_with_capacity(int arr[], unsigned int arr_size, size_t capacity) {
    assert(capacity >= arr_size * sizeof(int));
    int* data = (int*)malloc(capacity);
    for (int i=0; i<arr_size; i++) {
        data[i] = arr[i];
    }

    Vector* vec = (Vector*)malloc(sizeof(Vector));
    vec->size = arr_size;
    vec->capacity = capacity;
    vec->data = data;

    return vec;
}
 
void clear_vec(Vector* vec) {
    free(vec->data);
    vec->data = NULL;

    vec->size = 0;
    vec->capacity = 0;
}

void delete_vec(Vector* vec) {
    clear_vec(vec);
    free(vec);
    vec = NULL;
}

Vector* copy_vec(Vector* vec) {
    unsigned int size = vec->size;
    int data[size];
    for (int i=0; i<size; i++) {
        data[i] = vec->data[i];
    }
    Vector* vec_copy = vector(data, size);

    return vec_copy;
}

int pop(unsigned int idx, Vector* vec) {
    assert(idx >= 0 && idx < vec->size);
    int num = vec->data[idx];
    unsigned int new_size = vec->size - 1;
    for (int i=idx; i<new_size; i++) {
        vec->data[i] = vec->data[i+1];
    }
    vec->size = new_size;

    return num;
}

void insert_num(int num, unsigned int idx, Vector* vec) {
    assert(idx >= 0 && idx <= vec->size);
    unsigned int new_size = vec->size + 1;
    size_t req_capacity = new_size * sizeof(int);
    if (req_capacity > vec->capacity) {
        vec->capacity = 2 * req_capacity;
        vec->data = (int*)realloc(vec->data, vec->capacity);
    }
    for (int i=vec->size; i>idx; i--) {
        vec->data[i] = vec->data[i-1];
    }
    vec->data[idx] = num;
    vec->size = new_size;
}

void insert_vec(Vector* from, Vector* into, int idx) {
    assert(idx >= 0 && idx <= into->size);
    unsigned int new_size = from->size + into->size;
    size_t req_capacity = new_size * sizeof(int);
    if (req_capacity > into->capacity) {
        into->capacity = 2 * req_capacity;
        into->data = (int*)realloc(into->data, into->capacity);
    }
    for (int i=into->size - 1; i>=idx; i--) {
        into->data[i + from->size] = into->data[i];
    }
    for (int i=idx; i<=from->size; i++) {
        into->data[i] = from->data[i - idx];
    }
    into->size = new_size;
}

void push(int num, Vector* vec) {
    insert_num(num, vec->size, vec);
}

void push_front(int num, Vector* vec) {
    insert_num(num, 0, vec);
}

unsigned int count_vec(int value, Vector* vec) {
    unsigned int ctr = 0;
    for (int i=0; i<vec->size; i++) {
        if (vec->data[i] == value) {
            ctr++;
        }
    }
    
    return ctr;
}

void join_vec(Vector* vec1, Vector* vec2) {
    unsigned int new_size = vec1->size + vec2->size;
    size_t req_capacity = new_size * sizeof(int);
    if (req_capacity > vec1->capacity) {
        vec1->capacity = 2 * req_capacity;
        vec1->data = (int*)realloc(vec1->data, vec1->capacity);
    }
    int j = 0;
    for (int i=vec1->size; i<new_size; i++, j++) {
        vec1->data[i] = vec2->data[j];
    }

    vec1->size = new_size;
}   

void reverse_vec(Vector* vec) {
    int data[vec->size];
    for (int i=0; i<vec->size; i++) {
        data[i] = vec->data[vec->size-(i+1)];
    }
    for (int i=0; i<vec->size; i++) {
        vec->data[i] = data[i];
    }
}

int find_value(int value, Vector* vec) {
    for (int i=0; i<vec->size; i++) {
        if (vec->data[i] == value) {
            return i;
        }
    }

    return -1;
}

void remove_value(int value, Vector* vec) {
    for (int i=0; i<vec->size; i++) {
        if (vec->data[i] == value) {
            pop(i, vec);
            return;
        }
    }

    return;
}

void print_vec(Vector* vec) {
    if (vec->size == 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i=0; i<vec->size; i++) {
        printf("%d", vec->data[i]);
        if (i < vec->size-1) {
            printf(", ");
        }
        else {
            printf("]");
        }
    }
}

void debug_vec(Vector* vec) {
    printf("Data: ");
    print_vec(vec); printf("\n");
    printf("Addr: %p\n", vec);
    printf("Size: %d\n", vec->size);
    printf("Capacity: %ld B\n", vec->capacity);
}

bool is_empty(Vector* vec) {
    if (vec->size == 0) {
        return true;
    }
    return false;
}

void set_element(int value, unsigned int idx, Vector* vec) {
    assert(idx >=0 && idx < vec->size);
    vec->data[idx] = value;
}

unsigned int get_len(Vector* vec) {
    return vec->size;
}

int get_element(unsigned int idx, Vector* vec) {
    assert(idx >= 0 && idx < vec->size);
    return vec->data[idx];
}

int get_first(Vector* vec) {
    return vec->data[0];
}

int get_last(Vector* vec) {
    return vec->data[vec->size - 1];
}

Vector* get_slice(unsigned int start, unsigned int stop, Vector* vec) {
    assert(start >= 0 && start < vec->size);
    assert(stop > start && stop <= vec->size);
    unsigned int size = stop - start;
    int data[size];
    for (int i=0; i<size; i++) {
        data[i] = vec->data[i + start];
    }
    Vector* slice = vector(data, size);

    return slice;
}