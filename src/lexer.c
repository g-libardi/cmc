#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "scanner.h"
#include "lexer.h"
#include <string.h>

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

TokenType lexeme_list[30] = {
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
};

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

char *reserved_words[] = {
    "else",
    "if",
    "int",
    "return",
    "void",
    "while"
};
TokenType reserved_words_types[] = {
    ELSE_TOKEN,
    IF_TOKEN,
    INT_TOKEN,
    RETURN_TOKEN,
    VOID_TOKEN,
    WHILE_TOKEN
};
#define NUM_RESERVED_WORDS 6
#define MAX_WORD_SIZE 6
TokenType check_reserved_word(char *lexeme, int lexeme_size) {
    /*
     * n is the number of reserved words
     * m is the maximum size of a reserved word
     * O(n*m)
     * Since m is a constant(6), the time complexity is O(n)
     */
    int equal = 0;
    int i;
    for (i = 0; i < NUM_RESERVED_WORDS; i++) {
        /*strcmp(lexeme, reserved_words[i]);*/
        if (strcmp(lexeme, reserved_words[i]) == 0) {
            equal = 1;
            break;
        }
    }
    if (equal) {
        return reserved_words_types[i];
    }
    return ID_TOKEN;
}

Token *new_token(char *lexeme, int lexeme_size, TokenType type, int line) {
    if (type == ID_TOKEN) {
        type = check_reserved_word(lexeme, lexeme_size);
    }
    Token *token = (Token *)malloc(sizeof(Token));
    token->lexeme = (char *)malloc(sizeof(char) * (lexeme_size + 1));
    while (lexeme_size--) {
        token->lexeme[lexeme_size] = lexeme[lexeme_size];
    }
    token->type = type;
    token->line = line;
    token->next = NULL;
    return token;
}

char *token_type_to_str(TokenType type) {
    switch (type) {
        case ID_TOKEN: return "ID";
        case NUM_TOKEN: return "NUM";
        case PLUS_TOKEN: return "PLUS";
        case MINUS_TOKEN: return "MINUS";
        case TIMES_TOKEN: return "TIMES";
        case DIV_TOKEN: return "DIV";
        case LT_TOKEN: return "LT";
        case LT_EQ_TOKEN: return "LT_EQ";
        case GT_TOKEN: return "GT";
        case GT_EQ_TOKEN: return "GT_EQ";
        case EQ_TOKEN: return "EQ";
        case NEQ_TOKEN: return "NEQ";
        case NOT_TOKEN: return "NOT";
        case ASSIGN_TOKEN: return "ASSIGN";
        case SEMICOLON_TOKEN: return "SEMICOLON";
        case COMMA_TOKEN: return "COMMA";
        case LPAR_TOKEN: return "LPAR";
        case RPAR_TOKEN: return "RPAR";
        case LBRACKET_TOKEN: return "LBRACKET";
        case RBRACKET_TOKEN: return "RBRACKET";
        case LBRACE_TOKEN: return "LBRACE";
        case RBRACE_TOKEN: return "RBRACE";
        case LCOMMENT_TOKEN: return "LCOMMENT";
        case RCOMMENT_TOKEN: return "RCOMMENT";
        case ELSE_TOKEN: return "ELSE";
        case IF_TOKEN: return "IF";
        case INT_TOKEN: return "INT";
        case RETURN_TOKEN: return "RETURN";
        case VOID_TOKEN: return "VOID";
        case WHILE_TOKEN: return "WHILE";
    }
    return "UNKNOWN";
}


void free_token(Token *token) {
    free(token->lexeme);
    free(token);
}

void free_tokens(Token *token) {
    Token *next;
    while (token != NULL) {
        next = token->next;
        free_token(token);
        token = next;
    }
}

Token *tokenize(char *filename) {
    int line = 1;
    int column = 1;
    Scanner scanner = new_scanner(filename, 1000);
    char c = scanner.next(&scanner);
    State state = START;
    char *lexeme = (char *)malloc(sizeof(char) * 128);
    int lexeme_size = 0;
    Token *head = NULL;
    Token *current = NULL;
    while (c != EOF) {
        if (c == '\n') {
            line++;
        }
        CharClass cc = get_char_class(c);
        State next_state = transition_table[state][cc];
        if (next_state == ERROR) {
            lexeme[lexeme_size] = c;
            lexeme[lexeme_size + 1] = '\0';
            fprintf(stderr, "ERRO LÉXICO: \"%s\" [linha: %d], COLUNA %d\n", lexeme, line, column);
            exit(1);
        } else if (next_state == OK) {
            lexeme[lexeme_size] = '\0';
            TokenType type = lexeme_list[state - 1];
            Token *token = new_token(lexeme, lexeme_size, type, line);
            if (head == NULL) {
                head = token;
                current = token;
            } else {
                current->next = token;
                current = token;
            }

            lexeme_size = 0;
            state = START;
        } else {
            if (next_state != START)
                lexeme[lexeme_size++] = c;
            state = next_state;
            c = scanner.next(&scanner);
            column++;
        }
    }
    free(lexeme);
    free_scanner(&scanner);
    return head;
}
