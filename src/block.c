#include "block.h"

#include <stdlib.h>
#include <string.h>

void write_block(void* buffer, struct block_header* header, void* data) {
	char* p = buffer;

	memcpy(p,      &header->name, NAME_LENGTH);
	memcpy(p + 16, &header->type, sizeof(uint8_t));
	memcpy(p + 17, &header->size, sizeof(uint32_t));
	memcpy(p + 21, &header->date, sizeof(uint32_t));

	memcpy(p + 25, data, header->size);
}
