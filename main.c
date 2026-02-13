#include "array.h"

int main(int argc, char **argv)
{
    array_t *files = new_array(1);
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (!arr_push(files, argv[i]).data)
            {
                arr_destroy(files);
                return (1);
            }
        }
    }
    else
    {
        if (!arr_push(files, "a.out").data)
        {
            arr_destroy(files);
            return (1);
        }
    }
}