#include "files.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ReadFile* file_read_open(char* path) {
	ReadFile* file = calloc(1, sizeof(ReadFile));

	// setup path
	long pathSize = sizeof(char) * (strlen(path) + 1);
	file->path = calloc(1, pathSize);
	memcpy(file->path, path, pathSize);

	// open file
	FILE* ptr;
	ptr = fopen(path, "r");

	// find length
	fseek(ptr, 0, SEEK_END);
	file->size = 1 + ftell(ptr);
	fseek(ptr, 0, SEEK_SET);

	// create and read to buffer
	file->buffer = malloc(file->size);
	fread(file->buffer, 1, file->size - 1, ptr);
	fclose(ptr);

	return file;
}

void file_read_close(ReadFile* file) {
	free(file->buffer);
	free(file->path);
	free(file);
}