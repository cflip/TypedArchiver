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

	// Write the string block to a buffer
	int s_size = HEADER_BYTES + s_header.size;
	void* s_buffer = malloc(s_size);
	write_block(s_buffer, &s_header, (void*) message);

	// Create a header for a list block
	struct block_header l_header = { "List Example", TYPE_LIST, s_size, 0 };

	// Write the string block and list into another buffer
	int l_size = HEADER_BYTES + l_header.size;
	void* l_buffer = malloc(l_size);
	write_block(l_buffer, &l_header, (void*) s_buffer);

	// Write the list block into a file
	FILE* fp = fopen("out.taf", "w");
	fwrite(l_buffer, l_size, 1, fp);
	fclose(fp);

	// Free memory
	free(l_buffer);
	free(s_buffer);

	return 0;
}