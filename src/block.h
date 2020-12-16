#ifndef H_BLOCK
#define H_BLOCK

#define NAME_LENGTH 16
#define HEADER_BYTES 25

#include <stdint.h>

enum block_type {
	TYPE_LIST,
	TYPE_STRING
};

struct block_header {
	char name[NAME_LENGTH];
	uint8_t type;
	uint32_t size;
	uint32_t date;
};

struct block {
	void* data;
	int size;
};

struct block* create_block(struct block_header* header, void* data);
void free_block(struct block* block);

#endif