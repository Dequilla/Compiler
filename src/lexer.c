#include "lexer.h"

#include <stdlib.h>
#include <string.h>

Lexer* lexer_create(char* source) {
    Lexer* lexer = malloc(sizeof(Lexer));
    
    lexer->source = source;
    lexer->sourceLength = strlen(lexer->source);
    lexer->index = 0;

    return lexer;
}

void lexer_delete(Lexer* lexer) {
    free(lexer);
}