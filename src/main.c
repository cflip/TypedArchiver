#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

enum block_type {
	TYPE_STRING
};

struct block_header {
	char name[16];
	uint8_t type;
	uint32_t size;
	uint32_t date;
};

void write_block(FILE* file, struct block_header* header, void* data) {
	fwrite(&header->name, sizeof(header->name), 1, file);
	fwrite(&header->type, sizeof(header->type), 1, file);
	fwrite(&header->size, sizeof(header->size), 1, file);
	fwrite(&header->date, sizeof(header->date), 1, file);

	fwrite(data, header->size, 1, file);
}

int main() {
	const char* message = "This is an example string to be written into a block.";
	struct block_header header = { "Example", TYPE_STRING, strlen(message), 0};
	localtime((time_t*) &header.date);

	FILE* fp = fopen("out.taf", "w");
	write_block(fp, &header, (void*) message);
	fclose(fp);

	return 0;
}