#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_SCOPE,
    TOKEN_IDENTIFIER,
    TOKEN_TYPE,
    TOKEN_EQ,
    TOKEN_STRLITERAL,
    TOKEN_NUMLITERAL,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAREN,
    TOKEN_RPAREN
} TokenTypes;

typedef struct {
    char* value;
    TokenTypes type;
} Token;

typedef struct {
    char* source;
    long sourceLength;
    long index;
} Lexer;

Lexer* lexer_create(char* source);

void lexer_delete(Lexer* lexer);

#endif