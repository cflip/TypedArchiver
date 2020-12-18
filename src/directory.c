#include "directory.h"

#include <stdio.h>
#include <string.h>
#include "block.h"

#define PATH_BUF_SIZE 2048

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

void convert_directory(const char* dir_name) {
	struct dirent* entry;
	DIR* dir;

	char path[PATH_BUF_SIZE];

	if (!(dir = opendir(dir_name))) {
		printf("Could not find path: %s", dir_name);
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") != 0
		&& strcmp(entry->d_name, "..") != 0) {
			sprintf(path, "%s/%s", dir_name, entry->d_name);

			if (entry->d_type == DT_DIR) {
				// create a list tag
				printf("Directory: %s\n", path);
				convert_directory(path);
			} else {
				// read the file and create a string tag
				printf("File: %s\n", path);
			}
		}
	}

	closedir(dir);
}

#endif