#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

static char *path_for(char *bin, char *path)
{
    if (!bin)
        return (NULL);
    if (strchr(bin, '/'))
        return (strdup(bin));
    if (!path)
        return (NULL);
    char *s = strtok(path, ":");
    char test[4096] = {0};
    do
    {
        if (!s)
            break;
        strcat(test, s);
        if (test[strlen(test) - 1] != '/')
            strcat(test, "/");
        strcat(test, bin);
        if (!access(test, X_OK))
            return strdup(test);
        else
            bzero(test, 4096);
        s = strtok(NULL, ":");
    } while (s);
    return (NULL);
}

static char **add_ldpreload(char **envp)
{
    int i = 0;
    while (envp[i])
        i++;
    char **nenvp = calloc(i + 2, sizeof(char *));
    if (!nenvp)
    {
        perror("calloc");
        return 0;
    }
    for (int j = 0; j < i; j++)
        nenvp[j] = envp[j];
    nenvp[i] = strdup("LD_PRELOAD=./mtrace.so");
    nenvp[i + 1] = 0;
    return (nenvp);
}

int main(int argc, char **argv, char **envp)
{
    if (argc < 2)
    {
        fprintf(stderr, "LD_PRELOAD=%s\n", getenv("LD_PRELOAD"));
        return (0);
    }
    char **child_argv = &argv[1];
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    else if (pid == 0)
    {
        char *bin_path = path_for(argv[1], getenv("PATH"));
        if (!bin_path)
        {
            fprintf(stderr, "could not locate '%s'.\n", argv[1]);
            return (1);
        }
        char **nenvp = add_ldpreload(envp);
        if (execve(bin_path, child_argv, nenvp))
        {
            perror("execve");
            free(nenvp);
            return (1);
        }
        exit(0);
    }
}