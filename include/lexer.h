/**
 * @file lexer.h
 * @brief This module tokenizes a C file.
 */

#ifndef LEXER_H
#define LEXER_H

/**
 * @brief Token types enum.
 */
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


/**
 * @brief Token structure.
 */
typedef struct Token {
    char *lexeme;
    TokenType type;
    struct Token *next;
    int line;
} Token;


/**
 * @brief Tokenize a file with the lexer.
 * @param filename The file path.
 * @return The token list.
 */
Token *tokenize(char *filename);

/**
 * @brief Convert token type to string.
 * @param type The token type.
 * @return The string.
 */
char *token_type_to_str(TokenType type);

/**
 * @brief Free a token.
 * @param token The token.
 */
void free_token(Token *token);
/**
 * @brief Free multiple tokens.
 * @param token The token.
 */
void free_tokens(Token *token);

#endif // LEXER_H


