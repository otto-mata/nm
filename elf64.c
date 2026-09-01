#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "bfd-flags.h"
#include "elfxx.h"

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

static Elf64_Shdr *elf64_get_section_by_ndx(int ndx)
{
	return &elf->section_headers[ndx];
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

static uint32_t elf_get_flags_for_section(Elf64_Shdr *hdr)
{
	uint32_t flags = 0;

	if (hdr->sh_type != SHT_NOBITS)
		flags |= SEC_HAS_CONTENTS;
	if (hdr->sh_type == SHT_GROUP)
		flags |= SEC_GROUP;
	if ((hdr->sh_flags & SHF_ALLOC) != 0)
	{
		flags |= SEC_ALLOC;
		if (hdr->sh_type != SHT_NOBITS)
			flags |= SEC_LOAD;
	}
	if ((hdr->sh_flags & SHF_WRITE) == 0)
		flags |= SEC_READONLY;
	if ((hdr->sh_flags & SHF_EXECINSTR) != 0)
		flags |= SEC_CODE;
	else if ((flags & SEC_LOAD) != 0)
		flags |= SEC_DATA;
	if ((hdr->sh_flags & SHF_MERGE) != 0)
		flags |= SEC_MERGE;
	if ((hdr->sh_flags & SHF_STRINGS) != 0)
		flags |= SEC_STRINGS;
	if ((hdr->sh_flags & SHF_TLS) != 0)
		flags |= SEC_THREAD_LOCAL;
	if ((hdr->sh_flags & SHF_EXCLUDE) != 0)
		flags |= SEC_EXCLUDE;
	return flags;
}

static char section_type(Elf64_Shdr *section)
{
	uint32_t flags = elf_get_flags_for_section(section);
	if (flags & SEC_CODE)
		return 't';
	if (flags & SEC_DATA)
	{
		if (flags & SEC_READONLY)
			return 'r';
		else if (flags & SEC_SMALL_DATA)
			return 'g';
		else
			return 'd';
	}
	if (!(flags & SEC_HAS_CONTENTS))
	{
		if (flags & SEC_SMALL_DATA)
			return 's';
		else
			return 'b';
	}
	// if (flags & SEC_DEBUGGING)
	// 	return 'N';
	// if ((flags & SEC_HAS_CONTENTS) && (flags & SEC_READONLY))
	// 	return 'n';
	return '?';
}

static char symbol_class(Elf64_Sym *sym)
{
	Elf64_Shdr *sym_sec = elf64_get_section_by_ndx(sym->st_shndx);
	uint32_t flags = elf_get_flags_for_section(sym_sec);
	char c = '?';
	if (sym->st_shndx == SHN_COMMON)
	{
		if (flags & SEC_SMALL_DATA)
			return 'c';
		else
			return 'C';
	}
	if (sym->st_shndx == SHN_UNDEF)
	{
		if (ELF_ST_BIND(sym->st_info) == STB_WEAK)
		{
			if (ELF_ST_TYPE(sym->st_info) == STT_OBJECT)
				return 'v';
			else
				return 'w';
		}
		else
			return 'U';
	}
	// Add check for indirect section 'I'
	if (ELF_ST_TYPE(sym->st_info) == STT_GNU_IFUNC)
		return 'i';
	if (ELF_ST_BIND(sym->st_info) == STB_WEAK)
	{
		if (ELF_ST_TYPE(sym->st_info) == STT_OBJECT)
			return 'V';
		else
			return 'W';
	}
	if (ELF_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
		return 'u';

	if (sym->st_shndx == SHN_ABS)
		c = 'a';
	else
		c = section_type(sym_sec);
	if (ELF_ST_BIND(sym->st_info) == STB_GLOBAL)
		c = toupper(c);
	return c;
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
		if (cur->st_shndx != SHN_UNDEF)
			printf("%016lx ", cur->st_value);
		else
			printf("                 ");

		printf("%c %s", symbol_class(cur), name);
		printf("\n");
	}
	for (size_t i = 0; i < symnum; i++)
		free(sorted_sym[i]);
	free(sorted_sym);
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
