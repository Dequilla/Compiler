#include "strings.h"

int strings_contains_char(char character, const char* string, unsigned int length) {
	for (int i = 0; i < length; i++) {
		if (string[i] == character) return 1;
	}

	return 0;
}