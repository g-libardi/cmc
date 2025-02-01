#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"
#include "lexer.h"

/**
 * @brief Enum for Character classes.
 */

typedef enum {
    START,
    ID,
    NUM,
    PLUS,
    MINUS,
    TIMES,
    DIV,
    LT,
    LT_EQ,
    GT,
    GT_EQ,
    EQ,
    NEQ,
    NOT,
    ASSIGN,
    SEMICOLON,
    COMMA,
    LPAR,
    RPAR,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    LCOMMENT,
    RCOMMENT,
    OK,
    ERROR
} State;

typedef enum {
    CC_LETTER,
    CC_DIGIT,
    CC_WHITESPACE,
    CC_PLUS,
    CC_MINUS,
    CC_STAR,
    CC_SLASH,
    CC_LT,
    CC_GT,
    CC_EQ,
    CC_EXCLAMATION,
    CC_SEMICOLON,
    CC_COMMA,
    CC_LPAR,
    CC_RPAR,
    CC_LBRACKET,
    CC_RBRACKET,
    CC_LBRACE,
    CC_RBRACE,
    CC_EOF,
    CC_OTHER
} CharClass;

State transition_table[25][21] = {
    {ID, NUM, START, PLUS, MINUS, TIMES, DIV, LT, GT, ASSIGN, NOT, SEMICOLON, COMMA, LPAR, RPAR, LBRACKET, RBRACKET, LBRACE, RBRACE, OK, ERROR},
    {ID, ERROR, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {ERROR, NUM, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, LCOMMENT, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, LT_EQ, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, GT_EQ, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, NEQ, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, EQ, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, ERROR, OK, ERROR},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK, OK},
    {LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, RCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT},
    {LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, START, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT, LCOMMENT}
};



CharClass get_char_class(char c) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
        return CC_LETTER;
    } else if (c >= '0' && c <= '9') {
        return CC_DIGIT;
    } else if (isspace(c)) {
        return CC_WHITESPACE;
    } else {
        switch (c) {
            case '+': return CC_PLUS;
            case '-': return CC_MINUS;
            case '*': return CC_STAR;
            case '/': return CC_SLASH;
            case '<': return CC_LT;
            case '>': return CC_GT;
            case '=': return CC_EQ;
            case '!': return CC_EXCLAMATION;
            case ';': return CC_SEMICOLON;
            case ',': return CC_COMMA;
            case '(': return CC_LPAR;
            case ')': return CC_RPAR;
            case '[': return CC_LBRACKET;
            case ']': return CC_RBRACKET;
            case '{': return CC_LBRACE;
            case '}': return CC_RBRACE;
            case EOF: return CC_EOF;
            default: return CC_OTHER;
        }
    }
}


Token new_token(char *lexeme, TokenType type) {
    Token token;
    token.lexeme = lexeme;
    token.type = type;
    token.next = NULL;
    return token;
}

void free_token(Token *token) {
    free(token->lexeme);
}


Token *tokenize(char *filename) {
    Scanner scanner = new_scanner(filename, 1000);
    char c = scanner.next(&scanner);
    State state = START;
    char *lexeme = (char *)malloc(sizeof(char) * 128);
    int lexeme_size = 0;
    while (c != EOF) {
        CharClass cc = get_char_class(c);
        State next_state = transition_table[state][cc];
        if (next_state == ERROR) {
            fprintf(stderr, "Error: Invalid character %c\n", c);
            exit(1);
        } else if (next_state == OK) {
            lexeme[lexeme_size] = '\0';
            printf("lexem found: %s\n-------\n", lexeme);
            lexeme_size = 0;
            state = transition_table[START][cc];
            c = scanner.next(&scanner);
        } else {
            if (next_state != START)
                lexeme[lexeme_size++] = c;
            state = next_state;
            c = scanner.next(&scanner);
        }
    }
    free(lexeme);
    free_scanner(&scanner);
    return NULL;
}
