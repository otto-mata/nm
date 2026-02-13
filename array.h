#ifndef ARRAY_H
#define ARRAY_H
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uintptr_t **d;
    size_t capacity;
    size_t size;
} array_t;

typedef struct
{
    array_t *origin;
    void *data;
} push_result_t;

array_t *new_array(size_t capacity);
push_result_t arr_push(array_t *arr, void *data);
void *arr_pop(array_t *arr);
void arr_destroy(array_t *arr);

#endif