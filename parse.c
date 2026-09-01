#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include "elfxx.h"
#include "archive.h"

int parse_file(char *path)
{
	int ret = 0;
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
	if (is_elf(content))
		ret = parse_elf(content, st.st_size);
	if (is_ar(content))
		ret = parse_ar(content, st.st_size);
	munmap(content, st.st_size);
	close(fd);
	return (ret);
}
