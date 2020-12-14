#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "block.h"

int main() {
	const char* message = "This is an example string to be written into a block.";
	struct block_header header = { "Example", TYPE_STRING, strlen(message), 0};
	localtime((time_t*) &header.date);

	FILE* fp = fopen("out.taf", "w");
	write_block(fp, &header, (void*) message);
	fclose(fp);

	return 0;
}