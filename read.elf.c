#include <elf.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);

    int fd = open(argv[1], O_RDONLY);
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
    int type = ((unsigned char *)content)[4] == 2 ? 64 : 32;
    printf("%s is %dbit\n", argv[1], type);
    munmap(content, statbuf.st_size);
}
