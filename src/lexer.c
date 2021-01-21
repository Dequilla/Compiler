#include "lexer.h"

#include <stdlib.h>
#include <string.h>

Token* lexer_create_token(char* value, TokenTypes type) {
    Token* token = calloc(1, sizeof(Token));
    token->type = type;

    long length = sizeof(char) * (strlen(value) + 1);
    token->value = calloc(1, length);
    memcpy(token->value, value, length);

    return token;
}

void lexer_delete_token(Token* token) {
    free(token->value);
    free(token);
}

Lexer* lexer_create(char* source) {
    Lexer* lexer = calloc(1, sizeof(Lexer));
    
    lexer->source = source; // TODO: Remember to deallocate source
    lexer->sourceLength = strlen(lexer->source);
    lexer->index = -1;

    return lexer;
}

int lexer_advance(Lexer* lexer) {
    return lexer->index++ < lexer->sourceLength - 1;
}

Token* lexer_check_keywords(Lexer* lexer) {
    static const char* keywords[] = {
        "scope",
        "type",
        "fn",
        "int8",
        "int16",
        "int32",
        "int64",
        "string",
        "{",
        "}",
        "(",
        ")",
        "=",
        "."
    };
    static const int size = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < size; i++) {
        
        int isSame = 1;
        const int keysize = strlen(keywords[i]);
        for (int j = 0; j < keysize && lexer->index + j < lexer->sourceLength; j++) {
            const char keyChar = keywords[i][j];
            const char lexChar = lexer->source[lexer->index + j];

            if (keyChar != lexChar) {
                isSame = 0;
                break;
            }
        }

        if (isSame) {
            Token* token = lexer_create_token(keywords[i], TOKEN_KEYWORD);
            lexer->index += keysize;
            return token;
        }
    }

    return NULL;
}

Token* lexer_interpret(Lexer* lexer) {
    Token* token;

    token = lexer_check_keywords(lexer);

    return token;
}

void lexer_delete(Lexer* lexer) {
    free(lexer);
}