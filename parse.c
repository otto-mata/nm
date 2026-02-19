#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <elf.h>

int parse32(Elf32_Ehdr *content)
{
    return (0);
}

int parse64(Elf64_Ehdr *content)
{
    return (0);
}

int parse_file(char *path)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return (2);

    struct stat statbuf;

    if (fstat(fd, &statbuf))
    {
        perror("fstat");
        close(fd);
        return (3);
    }

    void *content = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (content == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return (6);
    }
    int ret = 0;
    unsigned char type = ((unsigned char *)content)[4];
    if (type == 2)
        ret = parse64(content);
    else if (type == 1)
        ret = parse32(content);
    else
        ret = 1;
    munmap(content, statbuf.st_size);
    close(fd);
    return (ret);
}