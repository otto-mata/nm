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
	void *file_data_p = NULL;

	file_data_p = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (file_data_p == MAP_FAILED)
	{
		perror("mmap");
		close(fd);
		return (6);
	}
	write(STDOUT_FILENO, file_data_p, statbuf.st_size);
	munmap(file_data_p, statbuf.st_size);
}
