#ifndef FILES_H
#define FILES_H

typedef struct {
	char* buffer;
	long size;
	char* path;
} ReadFile;

ReadFile* file_read_open(char* path);

void file_read_close(ReadFile* file);
	
#endif