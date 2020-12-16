#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "block.h"

void write_test(const char* filename) {
	// Create a header and data for a string block
	const char* message = "This is an example string to be written into a block.";
	struct block_header s_header = { "Example", TYPE_STRING, strlen(message), 0};
	time((time_t*) &s_header.date);

	// Write the string block to a block struct
	struct block* s_block = create_block(&s_header, (void*) message);

	// Create a list block and block header
	struct block_header l_header = { "List Example", TYPE_LIST, s_block->size, 0 };
	struct block* l_block = create_block(&l_header, (void*) s_block->data);

	// Write the list block into a file
	FILE* fp = fopen(filename, "w");
	fwrite(l_block->data, l_block->size, 1, fp);
	fclose(fp);

	// Free memory
	free_block(l_block);
	free_block(s_block);
}

void read_test(const char* filename) {
	FILE* fp = fopen(filename, "r");

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);

	void* buffer = malloc(size);
	fread(buffer, size, 1, fp);
	read_block(buffer);

	free(buffer);
	fclose(fp);
}

int main(int argc, char** argv) {
	if (argc <= 2) {
		printf("Usage:\n%s [-r/-w] [filename]\n", argv[0]);
		return 0;
	} else {
		if (strcmp(argv[1], "-w") == 0) {
			write_test(argv[2]);
		} else if (strcmp(argv[1], "-r") == 0) {
			read_test(argv[2]);
		} else {
			printf("Please use:\n-r for reading a file.\n-w for writing to a file");
		}
	}
	return 0;
}