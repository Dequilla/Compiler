#ifndef FILES_H
#define FILES_H

typedef struct {
	char* buffer;
	long size;
	char* path;
} RFile;

char* file_get_cwd();

RFile* file_read_open(char* path);

void file_read_close(RFile* file);
	
#endif