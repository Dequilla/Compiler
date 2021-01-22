#include <stdio.h>
#include "lexer.h"
#include "files.h"

int main(int argc, char** argv) {
    char* cwd = file_get_cwd();
    printf("Current dir: %s\n", cwd);

    // Keep alive until lexer is done
    RFile* file = file_read_open("../scripts/test.deq");
    if (file == NULL) return -1;

    printf(" -- File content -- \n%s\n\n", file->buffer);

    Lexer* lexer = lexer_create(file->buffer);
    
    printf(" -- Tokens -- \n");
    while (lexer_advance(lexer)) {
        Token* token = lexer_interpret(lexer);

        if (token != NULL) {
            printf("Token: %d - %s\n", token->type, token->value);
            lexer_delete_token(token);
        }
    }

    // Cleanup
    free(cwd);
    lexer_delete(lexer);
    file_read_close(file);

    return 0;
}