#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline Elf64_Shdr *elf64_get_shstrtab(elf64_t *elf)
{
	return &elf->section_headers[elf->elf_header->e_shstrndx];
}

static char *elf64_get_section_name(elf64_t *elf, Elf64_Shdr *sctn)
{
	Elf64_Shdr *shstrtab = elf64_get_shstrtab(elf);
	char *shstrdata = elf->data + shstrtab->sh_offset;
	return &shstrdata[sctn->sh_name];
}

static Elf64_Shdr *elf64_get_section_by_name(elf64_t *elf, const char *name)
{
	Elf64_Shdr *sh;
	for (Elf64_Half i = 0; i < elf->shnum; i++)
	{
		sh = &elf->section_headers[i];
		if (strcmp(name, elf64_get_section_name(elf, sh)) == 0)
			return (sh);
	}
	return (NULL);
}

static char *elf64_get_symbol_name(elf64_t *elf, Elf64_Sym *sym)
{
	Elf64_Shdr *strtab = elf64_get_section_by_name(elf, ".strtab");
	if (!strtab)
		return (NULL);
	char *strdata = elf->data + strtab->sh_offset;
	return &strdata[sym->st_name];
}

void elf64_show_sections(elf64_t *elf)
{
	Elf64_Shdr *sh;
	for (Elf64_Half i = 0; i < elf->shnum; i++)
	{
		sh = &elf->section_headers[i];
		printf("section %s\n", elf64_get_section_name(elf, sh));
		__builtin_dump_struct(sh, printf);
	}
}

void elf64_show_symbols(elf64_t *elf)
{
	Elf64_Shdr *symtab = elf64_get_section_by_name(elf, ".symtab");
	if (!symtab)
	{
		printf("No symbol\n");
		return;
	}
	Elf64_Sym *sym = (void *)elf->data + symtab->sh_offset;
	size_t symnum = symtab->sh_size / symtab->sh_entsize;
	for (size_t i = 0; i < symnum; i++)
	{
		if (sym[i].st_shndx > elf->shnum)
			continue;
		if (sym[i].st_value)
			printf("%016lx", sym[i].st_value);
		else
			printf("                ");
		printf(" %s\n", elf64_get_symbol_name(elf, &sym[i]));
	}
}

elf64_t *elf64_new(void *content, size_t size)
{
	elf64_t *elf;

	if (!content)
		return (NULL);
	elf = malloc(sizeof(*elf));
	if (!elf)
		return (NULL);
	elf->elf_header = content;
	elf->data = content;
	elf->phnum = elf->elf_header->e_phnum;
	elf->program_headers = (Elf64_Phdr *)((char *)content + elf->elf_header->e_phoff);
	elf->shnum = elf->elf_header->e_shnum;
	elf->section_headers = (Elf64_Shdr *)((char *)content + elf->elf_header->e_shoff);
	elf->size = size;
	return (elf);
}
