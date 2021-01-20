#include <stdio.h>
#include "lexer.h"

int main(int argc, char** argv) {
    Lexer* lexer = lexer_create("Hello world!");
    printf("%s -> %d", lexer->source, lexer->sourceLength);
    lexer_delete(lexer);

    return 0;
}