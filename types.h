#pragma once
#include <elf.h>
#include <stddef.h>

typedef struct elf64_st
{
	char *data;
	size_t size;
	Elf64_Ehdr *elf_header;
	Elf64_Phdr *program_headers;
	Elf64_Half phnum;
	Elf64_Shdr *section_headers;
	Elf64_Half shnum;
} elf64_t;

typedef struct elf32_st
{
	char *data;
	size_t size;
	Elf32_Ehdr *elf_header;
	Elf32_Phdr *program_headers;
	Elf32_Half phnum;
	Elf32_Shdr *section_headers;
	Elf32_Half shnum;
} elf32_t;
