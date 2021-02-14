#include "directory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "block.h"

#include <assert.h>

#define PATH_BUF_SIZE 2048

static struct block* convert_file(const char* path) {
	FILE* fp = fopen(path, "r");
	assert(fp);

	fseek(fp, 0, SEEK_END);
	int file_size = ftell(fp);
	rewind(fp);

	void* text_buf = malloc(file_size);
	fread(text_buf, file_size, 1, fp);

	struct block_header header = { "Text block", TYPE_STRING, file_size, 0 };
	struct block* block = create_block(&header, text_buf);

	free(text_buf);
	fclose(fp);

	return block;
}

// Windows doesn't support dirent.h, use the WIN32 API instead
#ifdef _WIN32

#include "Windows.h"

struct block* convert_directory(const char* dir_name) {
	WIN32_FIND_DATA entry;
	HANDLE dir = NULL;

	char path[PATH_BUF_SIZE];

	sprintf(path, "%s/*.*", dir_name);

	if ((dir = FindFirstFile(path, &entry)) == INVALID_HANDLE_VALUE) {
		printf("Could not find path: %s", path);
		return;
	}

	do {
		if (strcmp(entry.cFileName, ".") != 0
		&& strcmp(entry.cFileName, "..") != 0) {
			sprintf(path, "%s/%s", dir_name, entry.cFileName);

			if (entry.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// create a list tag
				printf("Directory: %s\n", path);
				convert_directory(path);
			} else {
				// read the file and create a string tag
				printf("File: %s\n", path);
			}
		}
	} while (FindNextFile(dir, &entry));

	FindClose(dir);
}

#else

#include <dirent.h>

struct block* convert_directory(const char* dir_name) {
	struct dirent* entry;
	DIR* dir;

	char path[PATH_BUF_SIZE];

	if (!(dir = opendir(dir_name))) {
		printf("Could not find path: %s", dir_name);
		return 0;
	}

	int buffer_size = 0;
	void* buffer = malloc(0);

	assert(buffer);

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") != 0
		&& strcmp(entry->d_name, "..") != 0) {
			sprintf(path, "%s/%s", dir_name, entry->d_name);

			struct block* file_block;

			if (entry->d_type == DT_DIR) {
				printf("Directory: %s\n", path);
				file_block = convert_directory(path);
			} else if (entry->d_type == DT_REG) {
				printf("File: %s\n", path);
				file_block = convert_file(path);
			}

			if (file_block) {
				int end = buffer_size;
				buffer_size += file_block->size;

				buffer = realloc(buffer, buffer_size);
				memcpy(buffer + end, file_block->data, file_block->size);
				free_block(file_block);
			}
		}
	}

	closedir(dir);

	struct block_header header = { "Untitled List", TYPE_LIST, buffer_size, 0 };
	return create_block(&header, buffer);
}

#endif