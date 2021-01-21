#include <stdio.h>
#include "lexer.h"
#include "files.h"

int main(int argc, char** argv) {
    ReadFile* file = file_read_open("scripts/test.deq");
    printf("%s", file->buffer);

    Lexer* lexer = lexer_create("int8 scope int8 type Animal { int8 legs = 100 }");
    
    while (lexer_advance(lexer)) {
        Token* token = lexer_interpret(lexer);

        if (token != NULL) {
            printf("Token: %s\n", token->value);
            lexer_delete_token(token);
        }
    }

    // Cleanup
    lexer_delete(lexer);
    file_read_close(file);

    return 0;
}