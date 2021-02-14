#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "block.h"
#include "directory.h"

void main_write(const char* in_path, const char* out_path) {
	struct stat path_stat;
	stat(in_path, &path_stat);

	struct block* file_block;

	if (S_ISDIR(path_stat.st_mode)) {
		file_block = convert_directory(in_path);
	} else if (S_ISREG(path_stat.st_mode)) {
		file_block = convert_file(in_path);
	}

	FILE* fp = fopen(out_path, "w");
	fwrite(file_block->data, file_block->size, 1, fp);
	fclose(fp);

	free_block(file_block);
}

void main_read(const char* filename) {
	FILE* fp = fopen(filename, "r");

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);

	void* buffer = malloc(size);
	fread(buffer, size, 1, fp);
	struct block* block = read_block(buffer);

	free(buffer);
	free_block(block);
	fclose(fp);
}

int main(int argc, char** argv) {
	if (argc <= 2) {
		printf("Usage:\n%s [-r/-w] [filename]\n", argv[0]);
		return 0;
	} else {
		if (strcmp(argv[1], "-w") == 0) {
			main_write(argv[2], "output.taf");
		} else if (strcmp(argv[1], "-r") == 0) {
			main_read(argv[2]);
		} else {
			printf("Please use:\n-r for reading a file.\n-w for writing to a file");
		}
	}

	return 0;
}