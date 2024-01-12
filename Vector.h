// Implementation of a Vector (dynamically growing array) in C
// Consists of a pointer to some data, the length and a non-decreasing
// capacity (currently allocated memory)

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    size_t len;
    size_t capacity;
} Vec;

// Create an empty vector
Vec vec_new(void);

// Create vector from an already existing array
Vec vec_from_array(int *arr, size_t len);

// Display contents of vector
void vec_display(Vec *vector);

// Return pointer to the first element
// Will return NULL if empty
int *vec_start(Vec *vector);

// Return pointer to the last element
// Will return NULL if empty
int *vec_end(Vec *vector);

// Get pointer to the element at a given index
int *vec_get(Vec *vector, size_t index);

// Resize vector by doubling the capacity each time
int vec_resize(Vec *vector);

// Push value at the end of vector, resizing if required
void vec_push(Vec *vector, int num);

// Push another array at the end of the vector
void vec_extend(Vec *vector, int *arr, size_t len);

// Pop value and get back a pointer to it
int *vec_pop(Vec *vector);

// Insert element at given index, resizing if required
// Index cannot be beyond the last index (use vec_push instead for that)
// Moves all elements after the given index (O(n) time complexity)
int vec_insert(Vec *vector, size_t index, int num);

// Push value at the first index
// It is simply a special case of vec_insert
void vec_push_front(Vec *vector, int num);

// Return index of element
// Returns -1 if not found
size_t vec_find(Vec *vector, int num);

// Replace element at index with new element
// Returns 1 if invalid element is passed in
int vec_replace(Vec *vector, size_t index, int num);

// Remove element from index
// Moves over all elements after it (O(n) time complexity)
// Returns 1 if element is invalid
int vec_remove(Vec *vector, size_t index);

// Delete vector
void vec_del(Vec *vector);



#ifdef VECTOR_H_IMPLEMENTATION

// Create an empty vector
Vec vec_new() {
    Vec vector = { NULL, 0, 0 };
    return vector;
}

// Create vector from an already existing array
Vec vec_from_array(int *arr, size_t len) {
    if (arr == NULL) {
        fprintf(stderr, "\nError in allocating\n");
        exit(1);
    }

    size_t size = len * sizeof(int);
    int* data = (int*)malloc(size);
    if (data == NULL) {
        fprintf(stderr, "\nError in allocating\n");
        exit(1);
    }
    memcpy(data, arr, size);

    Vec new_vec = {data, len, len};
    return new_vec;
}

// Display contents of vector
void vec_display(Vec *vector) {
    for(size_t i=0; i<vector->len; i++) {
        printf("%d ", vector->data[i]);
    }
    putchar('\n');
}

// Return pointer to the first element
// Will return NULL if empty
int *vec_start(Vec *vector) {
    return vector->data;
}

// Return pointer to the last element
// Will return NULL if empty
int *vec_end(Vec *vector) {
    if (vector->data == NULL) {
        return NULL;
    }
    return (vector->data + vector->len - 1);
}

// Get pointer to the element at a given index
int *vec_get(Vec *vector, size_t index) {
    if (index < vector->len) {
        return (vector->data + index);
    } else {
        fprintf(stderr, "\na SEG FAULT for you: invalid index - `%ld`\n", index);
        return NULL;
    }
} 

// Resize vector by doubling the capacity each time
int vec_resize(Vec *vector) {
    // Handle empty vector
    if (vector->capacity == 0) {
        vector->data = (int*)malloc(sizeof(int));
        if (vector->data == NULL) {
            fprintf(stderr, "\nError in allocating\n");
            return 1;
        }
        vector->capacity += 1;
        return 0;
    } 

    size_t new_capacity = vector->capacity * 2;
    size_t new_size = new_capacity * sizeof(int);
    int* new_ptr = (int*)realloc(vector->data, new_size);

    if (new_ptr == NULL) {
        fprintf(stderr, "\nError in allocating\n");
        return 1;
    }
    vector->data = new_ptr;
    vector->capacity = new_capacity;
    return 0;
}

// Push value at the end of vector, resizing if required
void vec_push(Vec *vector, int num) {
    if (vector->len >= vector->capacity) {
        if (vec_resize(vector) == 1) {
            fprintf(stderr, "\nError in allocating\n");
            exit(1);
        }
    }
    vector->data[vector->len] = num;
    vector->len += 1;
}

// Push another array at the end of the vector
void vec_extend(Vec *vector, int *arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        vec_push(vector, arr[i]);
    }
}

// Pop value and get back a pointer to it
int *vec_pop(Vec *vector) {
    if (vector->data == NULL) {
        fprintf(stderr, "\na SEG FAULT for you: empty vector cant pop\n");
        return NULL;
    }

    int *num = vector->data + vector->len - 1;
    vector->len -= 1;
    return num;
}

// Insert element at given index, resizing if required
// Index cannot be beyond the last index (use vec_push instead for that)
// Moves all elements after the given index (O(n) time complexity)
int vec_insert(Vec *vector, size_t index, int num) {
    if (index >= vector->len) {
        return 1;
    }

    if (vector->len >= vector->capacity) {
        if (vec_resize(vector) == 1) {
            fprintf(stderr, "\nError in allocating\n");
            exit(1);
        }
    }

    for (size_t i=vector->len; i>index; i--) {
        vector->data[i] = vector->data[i-1];
    }
    vector->data[index] = num;
    vector->len += 1;
    return 0;
}

// Push value at the first index
// It is simply a special case of vec_insert
void vec_push_front(Vec *vector, int num) {
    vec_insert(vector, 0, num);
}

// Return index of element
// Returns -1 if not found
size_t vec_find(Vec *vector, int num) {
    for (size_t i = 0; i < vector->len; i++) {
        if (vector->data[i] == num) {
            return i;
        }
    }
    return -1;
}

// Replace element at index with new element
// Returns 1 if invalid element is passed in
int vec_replace(Vec *vector, size_t index, int num) {
    if (index >= vector->len) {
        return 1;
    }
    vector->data[index] = num;
    return 0;
}

// Remove element from index
// Moves over all elements after it (O(n) time complexity)
// Returns 1 if element is invalid
int vec_remove(Vec *vector, size_t index) {
    if (index >= vector->len) {
        return 1;
    }
    for (size_t i = index; i < vector->len; i++) {
        vector->data[i] = vector->data[i+1];
    }
    vector->len -= 1;
    return 0;
}

// Delete vector
void vec_del(Vec *vector) {
    free(vector->data);
    vector->len = 0;
    vector->capacity = 0;
}

#endif // VECTOR_H_IMPLEMENTATION
#endif // VECTOR_H
