#include "lexer.h"

#include <stdlib.h>
#include <string.h>

#include "strings.h"

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
        "returns",
        "return",
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
            lexer->index += keysize - 1;
            return token;
        }
    }

    return NULL;
}

Token* lexer_check_identifiers(Lexer* lexer) {
    const static char allowedChars[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const static char allowedExtras[] = "0123456789";
    const static short allowedLength = 31;
    unsigned int idLength = 0;

    for (int i = 0; i < allowedLength && i + lexer->index < lexer->sourceLength; i++) {
        unsigned int actualIndex = lexer->index + i;
        if (strings_contains_char(lexer->source[actualIndex], allowedChars, strlen(allowedChars))) {
            idLength++;
            continue;
        }

        if (i != 0) {
            if (strings_contains_char(lexer->source[actualIndex], allowedExtras, strlen(allowedExtras))) {
                idLength++;
                continue;
            }
        }

        // Only gets here if char is none of the allowed
        break;
    }

    if (!idLength) {
        return NULL;
    } else if (idLength > 31) {
        printf("ERROR: identifier length longer than 31");
        return NULL;
    } else {
        char* value = malloc((idLength + 1) * sizeof(char));
        memcpy(value, &lexer->source[lexer->index], idLength);
        value[idLength] = '\0';
        Token* token = lexer_create_token(value, TOKEN_IDENTIFIER);
        free(value);

        lexer->index += idLength - 1;

        return token;
    }
}

Token* lexer_interpret(Lexer* lexer) {
    char c = lexer->source[lexer->index];
    if (
        c == ' ' || c == '\t' || 
        c == '\n' || c == '\v' || 
        c == '\r' || c == '\f'
    ) return NULL;

    Token* token = NULL;

    token = lexer_check_keywords(lexer);
    if (token != NULL) return token;

    token = lexer_check_identifiers(lexer);
    if (token != NULL) return token;

    // identify RValues examples:
    // string str = "string inside this"
    // int8 num = 029472

    return NULL;
}

void lexer_delete(Lexer* lexer) {
    free(lexer);
}