#include <stdio.h>
#include "lexer.h"

int main(int argc, char** argv) {
    Lexer* lexer = lexer_create("int8 scope int8 type Animal { int8 legs = 100 }");
    
    while (lexer_advance(lexer)) {
        Token* token = lexer_interpret(lexer);

        if (token != NULL) {
            printf("Token: %s\n", token->value);
            free(token);
        }
    }

    lexer_delete(lexer);

    return 0;
}