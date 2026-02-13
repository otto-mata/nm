#include "array.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    ARRAY x = new_array(8);
    assert(SIZ(x) == 0);
    assert(CAP(x) == 8);
    char *w = "hello";
    push_result_t res = arr_push(x, w);
    assert(res.origin != NULL);
    assert(res.data == w);
    assert(SIZ(x) == 1);
    assert(CAP(x) == 8);
    char *z = arr_pop(x);
    assert(z == w);
    assert(SIZ(x) == 0);
    assert(CAP(x) == 8);
    res = arr_push(x, w);
    res = arr_push(x, w + 1);
    res = arr_push(x, w + 2);
    res = arr_push(x, w + 3);
    res = arr_push(x, w + 4);
    assert(SIZ(x) == 5);
    assert(CAP(x) == 16 || (printf("cap: %zu\n", CAP(x)) && 0));
    int i = 4;
    while (SIZ(x))
    {
        z = arr_pop(x);
        assert(z == (void *)((uintptr_t)w + i));
        i--;
    }
    assert(SIZ(x) == 0);
    assert(CAP(x) == 16);
    arr_destroy(x);
}