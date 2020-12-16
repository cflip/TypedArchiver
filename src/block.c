#include "block.h"

#include <stdlib.h>
#include <string.h>

void write_block(void* buffer, struct block_header* header, void* data) {
	memcpy(buffer, header, sizeof(struct block_header));
	memcpy((char*) buffer + sizeof(struct block_header), data, header->size);
}
