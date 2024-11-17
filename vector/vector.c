#include "vector.h"

Vector* vector(void* arr, int length, VecDataType data_type) {
    int elem_size;
    switch (data_type)
    {
    case VEC_INT32:
        elem_size = sizeof(int);
        break;
    case VEC_INT64:
        elem_size = sizeof(long long);
        break;
    case VEC_FLOAT:
        elem_size = sizeof(float);
        break;
    case VEC_DOUBLE:
        elem_size = sizeof(double);
        break;
    default:
        printf("Unsupported vector data type.");
        abort();
    }

    size_t cap = 2 * length * elem_size;
    void* data;
    if (arr == NULL || length == 0) {
        data = NULL;
        cap = 0;
    }
    else {
        data = malloc(cap);
        _copy_data(arr, data, length, elem_size);
    }

    Vector* vec = (Vector*)malloc(sizeof(Vector));
    vec->data = data;
    vec->data_type = data_type;
    vec->elem_size = elem_size;
    vec->length = length;
    vec->capacity = cap;

    return vec;
}

Vector* vector_with_capacity(void* arr, int length, VecDataType dt, size_t cap) {
    int elem_size;
    switch (dt)
    {
    case VEC_INT32:
        elem_size = sizeof(int);
        break;
    case VEC_INT64:
        elem_size = sizeof(long long);
        break;
    case VEC_FLOAT:
        elem_size = sizeof(float);
        break;
    case VEC_DOUBLE:
        elem_size = sizeof(double);
        break;
    default:
        printf("Unsupported vector data type.");
        abort();
    }

    assert(cap >= length*elem_size);
    void* data = malloc(cap);

    if (arr != NULL && length != 0) {
        _copy_data(arr, data, length, elem_size);
    }

    Vector* vec = (Vector*)malloc(sizeof(Vector));
    vec->data = data;
    vec->data_type = dt;
    vec->elem_size = elem_size;
    vec->length = length;
    vec->capacity = cap;

    return vec;
}

Vector* zero_vector(int length, VecDataType dt) {
    int elem_size;
    switch (dt)
    {
    case VEC_INT32:
        elem_size = sizeof(int);
        break;
    case VEC_INT64:
        elem_size = sizeof(long long);
        break;
    case VEC_FLOAT:
        elem_size = sizeof(float);
        break;
    case VEC_DOUBLE:
        elem_size = sizeof(double);
        break;
    default:
        printf("Unsupported vector data type.");
        abort();
    }

    void* tmp_data = calloc(length, elem_size);
    size_t capacity = 2 * length * elem_size;
    Vector* vec = vector_with_capacity(tmp_data, length, dt, capacity);
    free(tmp_data);
    
    return vec;
}
 
void clear_vec(Vector* vec) {
    free(vec->data);
    vec->data = NULL;

    vec->length = 0;
    vec->capacity = 0;
}

void delete_vec(Vector* vec) {
    if (vec->data != NULL) {
        clear_vec(vec);
    }
    vec->length = 0;
    vec->capacity = 0;
    vec->elem_size = 0;
    free(vec);
    vec = NULL;
}

void cast_vec_dt(Vector* vec, VecDataType dt) {
    size_t req_cap = vec->length * 8;
    void* cast_data = calloc(vec->length, 8);

    switch (vec->data_type) {
    case VEC_INT32: {
        int* vec_arr = calloc(vec->length, sizeof(int));
        for (int i=0; i<vec->length; i++) {
            vec_arr[i] = *(int*)get_vec_elem(vec, i);
        }
        switch (dt) {
            case VEC_INT32:
                break;
            case VEC_INT64:
                for (int i=0; i<vec->length; i++) {
                    long long value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(long long));
                }
                break;
            case VEC_FLOAT:
                for (int i=0; i<vec->length; i++) {
                    float value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(float));
                }
                break;
            case VEC_DOUBLE:
                for (int i=0; i<vec->length; i++) {
                    double value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(double));
                }
                break;
        }
        free(vec_arr);
    }
    break;
    case VEC_INT64: {
        long long* vec_arr = calloc(vec->length, sizeof(long long));
        for (int i=0; i<vec->length; i++) {
            vec_arr[i] = *(long long*)get_vec_elem(vec, i);
        }
        switch (dt) {
            case VEC_INT32:
                for (int i=0; i<vec->length; i++) {
                    int value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(int));
                }
                break;
            case VEC_INT64:
                break;
            case VEC_FLOAT:
                for (int i=0; i<vec->length; i++) {
                    float value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(float));
                }
                break;
            case VEC_DOUBLE:
                for (int i=0; i<vec->length; i++) {
                    double value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(double));
                }
                break;
        }
        free(vec_arr);
    }
    break;
    case VEC_FLOAT: {
        float* vec_arr = calloc(vec->length, sizeof(float));
        for (int i=0; i<vec->length; i++) {
            vec_arr[i] = *(float*)get_vec_elem(vec, i);
        }
        switch (dt) {
            case VEC_INT32:
                for (int i=0; i<vec->length; i++) {
                    int value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(int));
                }
                break;
            case VEC_INT64:
                for (int i=0; i<vec->length; i++) {
                    long long value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(long long));
                }
                break;
            case VEC_FLOAT:
                break;
            case VEC_DOUBLE:
                for (int i=0; i<vec->length; i++) {
                    double value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(double));
                }
                break;
        }
        free(vec_arr);
    }
    break;
    case VEC_DOUBLE: {
        double* vec_arr = calloc(vec->length, sizeof(double));
        for (int i=0; i<vec->length; i++) {
            vec_arr[i] = *(double*)get_vec_elem(vec, i);
        }
        switch (dt) {
            case VEC_INT32:
                for (int i=0; i<vec->length; i++) {
                    int value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(int));
                }
                break;
            case VEC_INT64:
                for (int i=0; i<vec->length; i++) {
                    long long value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(long long));
                }
                break;
            case VEC_FLOAT:
                for (int i=0; i<vec->length; i++) {
                    float value = vec_arr[i];
                    _set_data_elem(cast_data, i, &value, sizeof(float));
                }
                break;
            case VEC_DOUBLE:
                break;
        }
        free(vec_arr);
    }
    break;
    }
    
    free(vec->data);
    vec->data = cast_data;
    vec->data_type = dt;
    vec->capacity = req_cap;
    switch (dt) {
        case VEC_INT32:
        case VEC_FLOAT:
            vec->elem_size = 4;
            break;
        case VEC_INT64:
        case VEC_DOUBLE:
            vec->elem_size = 8;
            break;
    }
}

Vector* copy_vec(Vector* vec) {
    int length = vec->length;
    void* tmp_data = malloc(vec->capacity);
    _copy_data(vec->data, tmp_data, length, vec->elem_size);
    Vector* vec_copy = vector_with_capacity(tmp_data, length, vec->data_type, vec->capacity);
    free(tmp_data);

    return vec_copy;
}

void assign_vec(Vector* old_vec, Vector* new_vec) {
    clear_vec(old_vec);
    old_vec->length = new_vec->length;
    old_vec->capacity = new_vec->capacity;
    old_vec->data_type = new_vec->data_type;
    old_vec->elem_size = new_vec->elem_size;
    old_vec->data = malloc(new_vec->capacity);
    _copy_data(new_vec->data, old_vec->data, old_vec->length, old_vec->elem_size);
}

Vector* add_vector(Vector* vec1, Vector* vec2) {
    assert(vec1->data_type == vec2->data_type);
    void* elem_sum = malloc(vec1->capacity);
    for (int i=0; i<vec1->length; i++) {
        void* elem1 = get_vec_elem(vec1, i);
        void* elem2 = get_vec_elem(vec2, i);
        switch(vec1->data_type) {
        case VEC_INT32:
            *((int*)elem_sum + i) = *(int*)elem1 + *(int*)elem2;
            break;
        case VEC_INT64:
            *((long long*)elem_sum + i) = *(long long*)elem1 + *(long long*)elem2;
            break;
        case VEC_FLOAT:
            *((float*)elem_sum + i) = *(float*)elem1 + *(float*)elem2;            
            break;
        case VEC_DOUBLE:
            *((double*)elem_sum + i) = *(double*)elem1 + *(double*)elem2;            
            break;             
        }
    }

    Vector* sum = vector(elem_sum, vec1->length, vec1->data_type);
    free(elem_sum);

    return sum;
}

void pop(int idx, Vector* vec) {
    assert(idx >= 0 && idx < vec->length);
    int new_size = vec->length - 1;
    for (int i=idx; i<new_size; i++) {
        set_vec_elem(vec, i, get_vec_elem(vec, i+1));
    }
    vec->length = new_size;
}

void insert_num(Vector* vec, int idx, void* num) {
    assert(idx >= 0 && idx <= vec->length);
    int new_size = vec->length + 1;
    size_t req_capacity = new_size * sizeof(vec->elem_size);
    if (req_capacity > vec->capacity) {
        vec->capacity = 2 * req_capacity;
        vec->data = realloc(vec->data, vec->capacity);
    }
    vec->length = new_size;
    for (int i=vec->length-1; i>idx; i--) {
        set_vec_elem(vec, i, get_vec_elem(vec, i-1));
    }
    set_vec_elem(vec, idx, num);
}

void insert_vec(Vector* from, Vector* into, int idx) {
    assert(idx >= 0 && idx <= into->length);
    assert(from->data_type == into->data_type);
    int new_size = from->length + into->length;
    into->length = new_size;
    size_t req_capacity = new_size * sizeof(from->elem_size);
    if (req_capacity > into->capacity) {
        into->capacity = 2 * req_capacity;
        into->data = realloc(into->data, into->capacity);
    }
    for (int i=into->length - from->length - 1; i>=idx; i--) {
        set_vec_elem(into, i+from->length, get_vec_elem(into, i));
    }
    for (int i=idx; i<idx+from->length; i++) {
        set_vec_elem(into, i, get_vec_elem(from, i-idx));
    }
}

void push(Vector* vec, void* num) {
    insert_num(vec, vec->length, num);
}

void push_front(Vector* vec, void* num) {
    insert_num(vec, 0, num);
}

int count_vec(Vector* vec, void* value) {
    int ctr = 0;
    for (int i=0; i<vec->length; i++) {
        void* vec_elem = get_vec_elem(vec, i);
        if (compare_vec_elem(vec_elem, value, vec->elem_size)) {
            ctr++;
        }
    }
    
    return ctr;
}

void append_vec(Vector* vec, Vector* other) {
    insert_vec(other, vec, vec->length);
}   

void reverse_vec(Vector* vec) {
    void* tmp_data = malloc(vec->capacity);
    for (int i=0; i<vec->length; i++) {
        void* elem = get_vec_elem(vec, vec->length-(i+1));
        _set_data_elem(tmp_data, i, elem, vec->elem_size);
    }
    for (int i=0; i<vec->length; i++) {
        _copy_data(tmp_data, vec->data, vec->length, vec->elem_size);
    }
    free(tmp_data);
}

int find_value(Vector* vec, void* value) {
    for (int i=0; i<vec->length; i++) {
        void* elem = get_vec_elem(vec, i);
        if (compare_vec_elem(elem, value, vec->elem_size)) {
            return i;
        }
    }

    return -1;
}

void remove_value(Vector* vec, void* value) {
    for (int i=0; i<vec->length; i++) {
        void* elem = get_vec_elem(vec, i);
        if (compare_vec_elem(elem, value, vec->elem_size)) {
            pop(i, vec);
            return;
        }
    }

    return;
}

bool compare_vec_elem(void* elem, void* value, int elem_size) {
    for (int i=0; i<elem_size; i++) {
        if (*((char*)elem + i) != *((char*)value + i)) {
            return false;
        }
    }

    return true;
}

void print_vec(Vector* vec) {
    if (vec->length == 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i=0; i<vec->length; i++) {
        void* elem = get_vec_elem(vec, i);
        switch(vec->data_type) {
        case VEC_INT32:
            printf("%d", *(int*)elem);
            break;
        case VEC_INT64:
            printf("%lld", *(long long*)elem);
            break;
        case VEC_FLOAT:
            printf("%.3f", *(float*)elem);
            break;
        case VEC_DOUBLE:
            printf("%.3lf", *(double*)elem);
            break;
        }
        if (i < vec->length-1) {
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
    printf("Data type: ");
    switch(vec->data_type) {
    case VEC_INT32:
        printf("VEC_INT32\n");
        break;
    case VEC_INT64:
        printf("VEC_INT64\n");
        break;
    case VEC_FLOAT:
        printf("VEC_FLOAT\n");
        break;
    case VEC_DOUBLE:
        printf("VEC_DOUBLE\n");
        break;
    }
    printf("Element size: %d Bytes\n", vec->elem_size);
    printf("Addr: %p\n", vec);
    printf("length: %d\n", vec->length);
    printf("Capacity: %ld Bytes\n", vec->capacity);
}

bool is_vec_empty(Vector* vec) {
    if (vec->length == 0 || vec->data == NULL) {
        return true;
    }
    return false;
}

void set_vec_elem(Vector* vec, int idx, void* value) {
    assert(idx >=0 && idx < vec->length);
    _set_data_elem(vec->data, idx, value, vec->elem_size);
}

int get_vec_len(Vector* vec) {
    return vec->length;
}

void* get_vec_elem(Vector* vec, int idx) {
    assert(idx >= 0 && idx < vec->length);
    void* elem_ptr = vec->data + idx*vec->elem_size;
    return elem_ptr;
}

void* get_vec_first(Vector* vec) {
    return get_vec_elem(vec, 0);
}

void* get_vec_last(Vector* vec) {
    return get_vec_elem(vec, vec->length-1);
}

Vector* get_slice(Vector* vec, int start, int stop) {
    assert(start >= 0 && start < vec->length);
    assert(stop > start && stop <= vec->length);
    int length = stop - start;
    void* tmp_data = malloc(length*vec->elem_size);
    for (int i=0; i<length; i++) {
        void* value = get_vec_elem(vec, i+start);
        _set_data_elem(tmp_data, i, value, vec->elem_size);
    }
    Vector* slice = vector(tmp_data, length, vec->data_type);
    free(tmp_data);

    return slice;
}

void _copy_data(void* data_from, void* data_to, int length, int elem_size) {
    assert(data_from != NULL && data_to != NULL);
    for (int i=0; i<length; i++) {
        for (int j=0; j<elem_size; j++) {
            *((char*)data_to + i*elem_size + j) = *((char*)data_from + i*elem_size + j);
        }
    }
}

void* _get_data_elem(void* data, int idx, int elem_size) {
    void* ptr = data + idx*elem_size;
    return ptr;
}

void _set_data_elem(void* data, int idx, void* value, int elem_size) {
    void* ptr = data + idx*elem_size;
    for (int i=0; i<elem_size; i++) {
        *((char*)ptr + i) = *((char*)value + i);
    }
}