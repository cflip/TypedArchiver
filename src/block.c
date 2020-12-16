#include "block.h"

#include <stdlib.h>
#include <string.h>

struct block* create_block(struct block_header* header, void* data) {
	struct block* result = malloc(sizeof(struct block));
	result->size = HEADER_BYTES + header->size;
	result->data = malloc(result->size);

	char* p = result->data;

	memcpy(p,      &header->name, NAME_LENGTH);
	memcpy(p + 16, &header->type, sizeof(uint8_t));
	memcpy(p + 17, &header->size, sizeof(uint32_t));
	memcpy(p + 21, &header->date, sizeof(uint32_t));

	memcpy(p + 25, data, header->size);

	return result;
}

void free_block(struct block* block) {
	free(block->data);
	free(block);
}