#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include "elfxx.h"

static int parse32(void *content, size_t size)
{
	elf32_t *elf = elf32_new(content, size);
	if (!elf)
		return (1);
	elf32_show_symbols(elf);
	free(elf);
	return (0);
}

static int parse64(void *content, size_t size)
{
	elf64_t *elf = elf64_new(content, size);
	if (!elf)
		return (1);
	elf64_show_symbols(elf);
	free(elf);
	return (0);
}

int parse_file(char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (2);
	}

	struct stat st;

	if (fstat(fd, &st))
	{
		perror("fstat");
		close(fd);
		return (3);
	}

	void *content = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (content == MAP_FAILED)
	{
		perror("mmap");
		close(fd);
		return (6);
	}
	int ret = 0;

	switch (((unsigned char *)content)[4])
	{
	case 1:
		parse32(content, st.st_size);

		break;
	case 2:
		parse64(content, st.st_size);
		break;
	}
	munmap(content, st.st_size);
	close(fd);
	return (ret);
}
