#include "elfxx.h"
#include <stdio.h>
#include <stdlib.h>

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

int is_elf(void *content)
{
	return (*(int *)content) == *(int *)ELFMAG;
}

int parse_elf(void *content, size_t size)
{

	if (size < 5 || !is_elf(content))
		return (1);
	char cls = ((char *)content)[EI_CLASS];
	switch (cls)
	{
	case ELFCLASS32:
		return parse32(content, size);
	case ELFCLASS64:
		return parse64(content, size);
	default:
		fprintf(stderr, "Unknown ELF Class `%d`\n", cls);
		break;
	}
	return (1);
}
