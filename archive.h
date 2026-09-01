#pragma once
#include <stddef.h>

int is_ar(void *content);
int parse_ar(void *content, size_t size);
