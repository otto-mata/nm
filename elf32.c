#include "types.h"
#include <stdlib.h>

elf32_t *elf32_new(void *content, size_t size)
{
	elf32_t *elf;

	if (!content)
		return (NULL);
	elf = malloc(sizeof(*elf));
	if (!elf)
		return (NULL);
	elf->elf_header = content;
	elf->data = content;
	elf->phnum = elf->elf_header->e_phnum;
	elf->program_headers = (Elf32_Phdr *)((char *)content + elf->elf_header->e_phoff);
	elf->shnum = elf->elf_header->e_shnum;
	elf->section_headers = (Elf32_Shdr *)((char *)content + elf->elf_header->e_shoff);
	elf->size = size;
	return (elf);
}
