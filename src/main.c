#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "block.h"

int main() {
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
	FILE* fp = fopen("out.taf", "w");
	fwrite(l_block->data, l_block->size, 1, fp);
	fclose(fp);

	// Free memory
	free_block(l_block);
	free_block(s_block);

	return 0;
}