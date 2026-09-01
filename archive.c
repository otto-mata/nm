#include <ar.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elfxx.h"

static char *ar_name(struct ar_hdr *hdr)
{
	static char buffer[17];
	strncpy(buffer, hdr->ar_name, sizeof(hdr->ar_name));
	char *eon = strchr(buffer, '/');
	if (!eon)
		return NULL;
	*eon = 0;
	return buffer;
}

int is_ar(void *content)
{
	return *(unsigned long *)content == *(unsigned long *)ARMAG;
}

int parse_ar(void *content, size_t size)
{
	if (!is_ar(content))
		return 1;
	/* skip magic */
	size_t offset = SARMAG;
	char *cpy;
	while (offset < size)
	{
		struct ar_hdr *hdr = content + offset;
		int ar_member_size = atoi(hdr->ar_size);
		if (ar_member_size < 1)
			break;
		cpy = ar_name(hdr);

		offset += sizeof(struct ar_hdr);
		void *elf_data = content + offset;
		offset += ar_member_size;
		if (!*cpy)
			continue;
		if (is_elf(elf_data))
		{
			printf("%s:\n", cpy);
			parse_elf(elf_data, ar_member_size);
		}
		else
			printf("%s: file format not recognized\n", cpy);
	}
	return (0);
}
