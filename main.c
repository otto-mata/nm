#include <stdlib.h>
#include <stdio.h>

int parse_file(char *path);

int main(int argc, char **argv)
{
    char **files = NULL;
    int nfiles = 0;
    if (argc > 1)
    {
        files = malloc(argc * sizeof(char *));
        if (!files)
        {
            perror("malloc");
            return (1);
        }
        int i;
        for (i = 1; i < argc; i++)
            files[i - 1] = argv[i];
        files[i - 1] = NULL;
        nfiles = argc - 1;
    }
    else
    {
        files = malloc(sizeof(char *));
        if (!files)
        {
            perror("malloc");
            return (1);
        }
        *files = "a.out";
        nfiles = 1;
    }
    for (int i = 0; i < nfiles; i++)
    {
        if (parse_file(files[i]))
        {
            free(files);
            return (1);
        }
    }

    free(files);
}