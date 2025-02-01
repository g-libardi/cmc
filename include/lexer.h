#ifndef LEXER_H
#define LEXER_H

typedef enum {
    ID_TOKEN,
    NUM_TOKEN,
    PLUS_TOKEN,
    MINUS_TOKEN,
    TIMES_TOKEN,
    DIV_TOKEN,
    LT_TOKEN,
    LT_EQ_TOKEN,
    GT_TOKEN,
    GT_EQ_TOKEN,
    EQ_TOKEN,
    NEQ_TOKEN,
    NOT_TOKEN,
    ASSIGN_TOKEN,
    SEMICOLON_TOKEN,
    COMMA_TOKEN,
    LPAR_TOKEN,
    RPAR_TOKEN,
    LBRACKET_TOKEN,
    RBRACKET_TOKEN,
    LBRACE_TOKEN,
    RBRACE_TOKEN,
    LCOMMENT_TOKEN,
    RCOMMENT_TOKEN,
    ELSE_TOKEN,
    IF_TOKEN,
    INT_TOKEN,
    RETURN_TOKEN,
    VOID_TOKEN,
    WHILE_TOKEN,
} TokenType;


typedef struct Token {
    char *lexeme;
    TokenType type;
    struct Token *next;
} Token;


Token *tokenize(char *filename);


#endif // LEXER_H


