#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "block.h"

int main() {
	const char* message = "This is an example string to be written into a block.";
	struct block_header header = { "Example", TYPE_STRING, strlen(message), 0};
	time((time_t*) &header.date);

	int size = sizeof(struct block_header) + header.size;
	void* buffer = malloc(size);
	write_block(buffer, &header, (void*) message);

	FILE* fp = fopen("out.taf", "w");
	fwrite(buffer, size, 1, fp);
	fclose(fp);

	free(buffer);

	return 0;
}