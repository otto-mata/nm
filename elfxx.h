#pragma once
#include "types.h"

elf32_t *elf32_new(void *content, size_t size);

elf64_t *elf64_new(void *content, size_t size);
void elf64_show_sections(elf64_t *elf);
void elf64_show_symbols(elf64_t *elf);
