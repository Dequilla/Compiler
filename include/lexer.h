#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_STRLITERAL,
    TOKEN_NUMLITERAL
} TokenTypes;

typedef struct {
    char* value;
    TokenTypes type;
} Token;

Token* lexer_create_token(char* value, TokenTypes type);

void lexer_delete_token(Token* token);

typedef struct {
    char* source;
    long sourceLength;
    long index;
} Lexer;

Lexer* lexer_create(char* source);

int lexer_advance(Lexer* lexer);

Token* lexer_check_keywords(Lexer* lexer);

Token* lexer_check_identifiers(Lexer* lexer);

Token* lexer_check_values(Lexer* lexer);

Token* lexer_interpret(Lexer* lexer);

void lexer_delete(Lexer* lexer);

#endif