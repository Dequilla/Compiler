#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_SCOPE,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
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