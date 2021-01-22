#include "files.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

char* file_get_cwd() {
#ifdef _WIN32
	TCHAR* pwd = malloc(MAX_PATH * sizeof(TCHAR));
	GetCurrentDirectory(MAX_PATH, pwd);
	return pwd;
#else
	printf("ERROR: file_get_cwd not implemented for this system/platform\n");
	return NULL;
#endif
}

RFile* file_read_open(char* path) {
	RFile* file = calloc(1, sizeof(RFile));

	// setup path
	long pathSize = sizeof(char) * (strlen(path) + 1);
	file->path = calloc(1, pathSize);
	memcpy(file->path, path, pathSize);

	// open file
	FILE* ptr;
	ptr = fopen(path, "rb");
	if (ptr == NULL) {
		printf("ERROR: file not found \"%s\"\n", path);
		return NULL;
	}

	// find length
	fseek(ptr, 0, SEEK_END);
	file->size = 1 + ftell(ptr);
	fseek(ptr, 0, SEEK_SET);

	// create and read to buffer
	file->buffer = malloc(file->size);
	fread(file->buffer, 1, file->size - 1, ptr);
	file->buffer[file->size - 1] = '\0';
	fclose(ptr);
	ptr = NULL;

	return file;
}

void file_read_close(RFile* file) {
	free(file->buffer);
	free(file->path);
	free(file);
}