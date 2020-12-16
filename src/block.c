#include "block.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

struct block* read_block(void* buffer) {
	struct block_header header;

	char* p = buffer;

	memcpy(&header.name, p, NAME_LENGTH);
	memcpy(&header.type, p + 16, sizeof(uint8_t));
	memcpy(&header.size, p + 17, sizeof(uint32_t));
	memcpy(&header.date, p + 21, sizeof(uint32_t));

	void* data = malloc(header.size);
	memcpy(data, p + 25, header.size);

	char date_string[20];
	strftime(date_string, 20, "%Y-%m-%d", localtime((time_t*) &header.date));

	printf("BLOCK\nname:\t%.16s\ntype:\t%d\nsize:\t%d\ndate:\t%s\n\n", header.name, header.type, header.size, date_string);

	if (header.type == TYPE_LIST) {
		int total_bytes = 0;
		char* index = data;

		do {
			struct block* block = read_block(index);

			total_bytes += block->size;
			index += block->size;

			free_block(block);
		} while (header.size > total_bytes);
	} else {
		printf("%.*s\n", header.size, data);
	}

	return create_block(&header, data);
}

void free_block(struct block* block) {
	free(block->data);
	free(block);
}