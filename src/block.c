#include "block.h"

void write_block(FILE* file, struct block_header* header, void* data) {
	fwrite(&header->name, sizeof(header->name), 1, file);
	fwrite(&header->type, sizeof(header->type), 1, file);
	fwrite(&header->size, sizeof(header->size), 1, file);
	fwrite(&header->date, sizeof(header->date), 1, file);

	fwrite(data, header->size, 1, file);
}
