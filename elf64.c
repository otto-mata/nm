#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

static elf64_t *elf = NULL;

static inline Elf64_Shdr *elf64_get_shstrtab()
{
	return &elf->section_headers[elf->elf_header->e_shstrndx];
}

static char *elf64_get_section_name(Elf64_Shdr *sctn)
{
	Elf64_Shdr *shstrtab = elf64_get_shstrtab();
	char *shstrdata = elf->data + shstrtab->sh_offset;
	return &shstrdata[sctn->sh_name];
}

static char *elf64_get_section_name_by_ndx(int ndx)
{
	return elf64_get_section_name(&elf->section_headers[ndx]);
}

static Elf64_Shdr *elf64_get_section_by_name(const char *name)
{
	Elf64_Shdr *sh;
	for (Elf64_Half i = 0; i < elf->shnum; i++)
	{
		sh = &elf->section_headers[i];
		if (strcmp(name, elf64_get_section_name(sh)) == 0)
			return (sh);
	}
	return (NULL);
}

static char *elf64_get_symbol_name(Elf64_Sym *sym)
{
	Elf64_Shdr *strtab = elf64_get_section_by_name(".strtab");
	if (!strtab)
		return (NULL);
	char *strdata = elf->data + strtab->sh_offset;
	return &strdata[sym->st_name];
}
static int namecmp(Elf64_Sym *sym1, Elf64_Sym *sym2)
{
	char *name1 = strdup(elf64_get_symbol_name(sym1));
	char *name2 = strdup(elf64_get_symbol_name(sym2));

	int diff = strcoll(name1, name2);
	free(name1);
	free(name2);
	return diff;
}

static int sortname(const void *sym1, const void *sym2)
{
	return namecmp(*(Elf64_Sym **)sym1, *(Elf64_Sym **)sym2);
}

static void sortutil(Elf64_Sym *symbols[], int count)
{
	qsort(symbols, count, sizeof(*symbols), sortname);
}

void elf64_show_sections()
{
	Elf64_Shdr *sh;
	for (Elf64_Half i = 0; i < elf->shnum; i++)
	{
		sh = &elf->section_headers[i];
		printf("section %s\n", elf64_get_section_name(sh));
		__builtin_dump_struct(sh, printf);
	}
}

void print_symbol_type(Elf64_Sym *sym)
{
	char *sctn_name = elf64_get_section_name_by_ndx(sym->st_shndx);
	if (!sym->st_value)
	{
		if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
			printf(" w");
		else
			printf(" U");
		return;
	}
	if (!sctn_name)
	{
		printf("  ");
		return;
	}
	char c = sctn_name[1];
	if (c == 't' && ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		c = 'T';
	else if (ELF64_ST_BIND(sym->st_info) == STB_GLOBAL)
		c -= 32;
	else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
		c = 'W';
	printf(" %c", c);
}

void elf64_show_symbols(elf64_t *_elf)
{
	elf = _elf;
	Elf64_Shdr *symtab = elf64_get_section_by_name(".symtab");
	if (!symtab)
	{
		printf("No symbol\n");
		return;
	}
	Elf64_Sym *sym = (void *)elf->data + symtab->sh_offset;
	size_t symnum = symtab->sh_size / symtab->sh_entsize;
	Elf64_Sym **sorted_sym = calloc(symnum, sizeof(Elf64_Sym *));

	for (size_t i = 0; i < symnum; i++)
	{
		sorted_sym[i] = malloc(sizeof(*sorted_sym[i]));
		memmove(sorted_sym[i], &sym[i], sizeof(sym[i]));
	}
	sortutil(sorted_sym, symnum);
	for (size_t i = 0; i < symnum; i++)
	{
		Elf64_Sym *cur = sorted_sym[i];

		char *name = elf64_get_symbol_name(cur);
		if (*name == 0)
			continue;
		if (cur->st_shndx > elf->shnum)
			continue;
		if (cur->st_value)
			printf("%016lx", cur->st_value);
		else
			printf("                ");
		print_symbol_type(cur);

		printf(" %s", name);
		printf("\n");
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
