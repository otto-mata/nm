#include "array.h"
#include <stdlib.h>
#include <stdint.h>

array_t *new_array(size_t capacity)
{
    array_t *arr = malloc(sizeof(*arr));
    if (!arr)
        return (NULL);
    arr->d = malloc(capacity * sizeof(uintptr_t));
    if (!arr->d)
    {
        free(arr);
        return (NULL);
    }
    arr->capacity = capacity;
    arr->size = 0;
    return (arr);
}

array_t *grow(array_t *arr)
{
    if (!arr)
        return (NULL);
    size_t new_capacity = arr->capacity * 2;
    uintptr_t **new_d = malloc(new_capacity * sizeof(uintptr_t));
    if (!new_d)
        return (NULL);
    for (size_t i = 0; i < arr->size; i++)
        new_d[i] = arr->d[i];
    free(arr->d);
    arr->d = new_d;
    arr->capacity = new_capacity;
    return (arr);
}

push_result_t arr_push(array_t *arr, void *data)
{
    if (!arr)
        return ((push_result_t){.data = NULL, .origin = NULL});
    if (!arr->d)
        return ((push_result_t){.data = NULL, .origin = arr});
    if ((arr->size + 1) > (arr->capacity / 2))
    {
        array_t *nptr = grow(arr);
        if (!nptr)
            return ((push_result_t){.data = NULL, .origin = arr});
        arr = nptr;
    }
    arr->d[arr->size++] = data;
    return ((push_result_t){.data = data, .origin = arr});
}

void *arr_pop(array_t *arr)
{
    if (!arr)
        return (NULL);
    if (!arr->d)
        return (NULL);
    if (arr->size == 0)
        return (0);
    void *data = arr->d[arr->size - 1];
    arr->d[arr->size - 1] = NULL;
    arr->size--;
    return (data);
}

void arr_destroy(array_t *arr)
{
    if (!arr)
        return;
    free(arr->d);
    free(arr);
}