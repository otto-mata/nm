#pragma once
#include "types.h"

#define ELF_ST_BIND(val) (((unsigned char)(val)) >> 4)
#define ELF_ST_TYPE(val) ((val) & 0xf)

elf32_t *elf32_new(void *content, size_t size);
void elf32_show_symbols(elf32_t *_elf);

elf64_t *elf64_new(void *content, size_t size);
void elf64_show_symbols(elf64_t *elf);
