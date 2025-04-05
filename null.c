#include <stdio.h>
#include <stdlib.h>

struct int_vector {
    size_t count;
    size_t capacity;
    int *v;
};

enum int_vector_fail {
    VEC_SUCCESS,
    VEC_FAILURE,
};

enum int_vector_fail create_int_vector( struct int_vector **v, size_t init_size) {
    if (init_size == 0) return VEC_FAILURE;
    *v = malloc(sizeof(struct int_vector));
    if (!*v) return VEC_FAILURE;
    (*v)->capacity = init_size;
    (*v)->count = 0;
    (*v)->v = (int*)malloc(sizeof(int) * init_size);
    if (!(*v)->v) return VEC_FAILURE;
    return VEC_SUCCESS;
}

int push_int_vector(struct int_vector *v, const int value) {
    if (!v) return VEC_FAILURE;
    if (v->count >= v->capacity) { // vector is full now
        int *new_v = realloc(v->v, sizeof(int) * (v->capacity * 2)); // increase the capacity
        if (new_v == NULL) // realloc failed
            return VEC_FAILURE;
        v->v = new_v;
        v->capacity *= 2;
    }
    v->v[v->count++] = value;
    return VEC_SUCCESS;
}

enum int_vector_fail pop_int_vector(struct int_vector *v, int *out) {
    if (!v) return VEC_FAILURE;
    if (v->count == 0) return VEC_FAILURE;
    *out = v->v[--v->count];
    if (v->count > 0 && v->count < v->capacity / 4) { // lower than 25% of the vector capacity.
        int *new_v = realloc(v->v, sizeof(int) * (v->capacity / 2)); // decrease the capacity
        if (new_v == NULL) // realloc failed
            return VEC_FAILURE;
        v->v = new_v;
        v->capacity /= 2;
    }
    return VEC_SUCCESS;
}

void free_int_vector(struct int_vector *v) {
    if (!v) return;
    free(v->v);
    free(v);
}


int main() {

    struct int_vector *v;
    if (create_int_vector(&v, 0) == VEC_FAILURE) {
        printf("FAILED to init.\n");
    }
    if (create_int_vector(&v, 3) == VEC_FAILURE) {
        printf("Failed to init again.\n");
        return -1;
    }
    for (int i = 0; i < 150; i++) {
        if (push_int_vector(v, i * 10) == VEC_FAILURE) {
            printf("Failed to push int_vector\n");
            return -1;
        }
    }
    for (int i = 0; i < 100; i++) {
        int n;
        if (pop_int_vector(v, &n) == VEC_FAILURE) {
            printf("Failed to pop int_vector\n");
            return -1;
        }
        printf("Popped %d.\n", n);
    }
    free_int_vector(v);
    v = NULL;
    return 0;
}