#include <stdio.h>

#define VECTOR_H_IMPLEMENTATION
#include "Vector.h"


int main() {
    int arr[5] = {10,20,30,40,50};
    Vec vector = vec_from_array(arr, 5);

    vec_display(&vector);
    printf("Begin: %d, End: %d\n", *vec_start(&vector), *vec_end(&vector));
    printf("Index %d: %d\n\n", 2, *vec_get(&vector, 2));

    for (int i=1; i<=5; i++) {
        vec_push(&vector, i*i);
    }
    vec_display(&vector);
    printf("len : %ld\n", vector.len);
    printf("capacity: %ld\n", vector.capacity);

    printf("popped value: %d\n", *vec_pop(&vector));
    printf("popped value: %d\n", *vec_pop(&vector));
    vec_display(&vector);


    for (int i=9; i>5; i--) {
        vec_push_front(&vector, i);
    }
    vec_display(&vector);

    vec_insert(&vector, 4, 1000);
    vec_insert(&vector, 8, 2000);
    vec_insert(&vector, 10, 3000);

    vec_display(&vector);
    printf("len : %ld\n", vector.len);
    printf("capacity: %ld\n", vector.capacity);

    printf("Index: %ld\n", vec_find(&vector, 1000));
    printf("Index: %ld\n", vec_find(&vector, 10));
    printf("Index: %ld (not found)\n", vec_find(&vector, 256));

    vec_replace(&vector, 0, -1);
    vec_replace(&vector, 9, 999);
    vec_display(&vector);

    vec_remove(&vector, 0);
    vec_remove(&vector, 9);
    vec_display(&vector);

    // vec_del(&vector);
    putchar('\n');

    Vec new_vec = vec_new();
    for (int i=0;i<10;i++) {
        vec_push(&new_vec, i*i*i);
    }
    vec_display(&new_vec);
    printf("len : %ld\n", new_vec.len);
    printf("capacity: %ld\n", new_vec.capacity);

    vec_extend(&new_vec, vector.data, vector.len);

    vec_display(&new_vec);
    printf("len : %ld\n", new_vec.len);
    printf("capacity: %ld\n", new_vec.capacity);

    vec_del(&new_vec);
    printf("%zu %zu\n", new_vec.len, new_vec.capacity);
    
    int a = vec_insert(&new_vec, 0, 10);
    printf("%d\n", a);



    putchar('\n');
    return 0;
}
