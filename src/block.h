#ifndef H_BLOCK
#define H_BLOCK

#define NAME_LENGTH 16

#include <stdio.h>
#include <stdint.h>

enum block_type {
	TYPE_STRING
};

struct block_header {
	char name[NAME_LENGTH];
	uint8_t type;
	uint32_t size;
	uint32_t date;
};

void write_block(void* buffer, struct block_header* header, void* data);

#endif