%{
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "pparser.h"

Token *tokenHead = NULL;
Token *currentToken = NULL;

/**
 * @brief Convert a token type to a string.
 * @param t The token type.
 */
int token_to_bison_token(TokenType t) {
    switch (t) {
        case ID_TOKEN: return ID_TK;
        case NUM_TOKEN: return NUM_TK;
        case PLUS_TOKEN: return PLUS_TK;
        case MINUS_TOKEN: return MINUS_TK;
        case TIMES_TOKEN: return TIMES_TK;
        case DIV_TOKEN: return DIV_TK;
        case LT_TOKEN: return LT_TK;
        case LT_EQ_TOKEN: return LT_EQ_TK;
        case GT_TOKEN: return GT_TK;
        case GT_EQ_TOKEN: return GT_EQ_TK;
        case EQ_TOKEN: return EQ_TK;
        case NEQ_TOKEN: return NEQ_TK;
        case ASSIGN_TOKEN: return ASSIGN_TK;
        case SEMICOLON_TOKEN: return SEMICOLON_TK;
        case COMMA_TOKEN: return COMMA_TK;
        case LPAR_TOKEN: return LPAR_TK;
        case RPAR_TOKEN: return RPAR_TK;
        case LBRACKET_TOKEN: return LBRACKET_TK;
        case RBRACKET_TOKEN: return RBRACKET_TK;
        case LBRACE_TOKEN: return LBRACE_TK;
        case RBRACE_TOKEN: return RBRACE_TK;
        case ELSE_TOKEN: return ELSE_TK;
        case IF_TOKEN: return IF_TK;
        case INT_TOKEN: return INT_TK;
        case RETURN_TOKEN: return RETURN_TK;
        case VOID_TOKEN: return VOID_TK;
        case WHILE_TOKEN: return WHILE_TK;
        default: return -2;
    }
}


/**
 * @brief Functio to acquire tokens from the token stream.
 */
int yylex(void)
{
    if (currentToken != NULL) {
        int tokenType = currentToken->type;
        tokenType = token_to_bison_token(tokenType);
        currentToken = currentToken->next;
        return tokenType;
    }
    return 0;
}

void yyerror(const char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}
%}

%token ID_TK NUM_TK PLUS_TK MINUS_TK TIMES_TK DIV_TK
%token LT_TK LT_EQ_TK GT_TK GT_EQ_TK EQ_TK NEQ_TK
%token ASSIGN_TK SEMICOLON_TK COMMA_TK LPAR_TK RPAR_TK
%token LBRACKET_TK RBRACKET_TK LBRACE_TK RBRACE_TK
%token ELSE_TK IF_TK INT_TK RETURN_TK VOID_TK WHILE_TK

%%

program
    : declaration_list
    ;

declaration_list
    : declaration_list declaration
    | declaration
    ;

declaration
    : var_declaration
    | fun_declaration
    ;

var_declaration
    : type_specifier ID_TK SEMICOLON_TK
    | type_specifier ID_TK LBRACKET_TK NUM_TK RBRACKET_TK SEMICOLON_TK
    ;

type_specifier
    : INT_TK
    | VOID_TK
    ;

fun_declaration
    : type_specifier ID_TK LPAR_TK params RPAR_TK compound_stm
    ;

param
    : type_specifier ID_TK
    | type_specifier
    ;

param_list
    : param_list COMMA_TK param
    | param
    ;

params
    : param_list
    | VOID_TK
    ;

compound_stm
    : LBRACE_TK local_declarations statement_list RBRACE_TK
    ;

local_declarations
    : local_declarations var_declaration
    | /* empty */
    ;

statement_list
    : statement_list statement
    | /* empty */
    ;

statement
    : expression_stmt
    | compound_stm
    | selection_stm
    | iteration_stm
    | return_stm
    ;

expression_stmt
    : expression SEMICOLON_TK
    | SEMICOLON_TK
    ;

selection_stm
    : IF_TK LPAR_TK expression RPAR_TK statement ELSE_TK statement
    | IF_TK LPAR_TK expression RPAR_TK statement
    ;

iteration_stm
    : WHILE_TK LPAR_TK expression RPAR_TK statement
    ;

return_stm
    : RETURN_TK SEMICOLON_TK
    | RETURN_TK expression SEMICOLON_TK
    ;

expression
    : var ASSIGN_TK expression
    | simple_expression
    ;

var
    : ID_TK LBRACKET_TK expression RBRACKET_TK
    | ID_TK
    ;

simple_expression
    : additive_expression relop additive_expression
    | additive_expression
    ;

relop
    : LT_EQ_TK
    | LT_TK
    | GT_TK
    | GT_EQ_TK
    | EQ_TK
    | NEQ_TK
    ;

additive_expression
    : additive_expression PLUS_TK term
    | additive_expression MINUS_TK term
    | term
    ;

term
    : term TIMES_TK factor
    | term DIV_TK factor
    | factor
    ;

factor
    : LPAR_TK expression RPAR_TK
    | var
    | call
    | NUM_TK
    ;

call
    : ID_TK LPAR_TK args RPAR_TK
    ;

args
    : arg_list
    | /* empty */
    ;

arg_list
    : arg_list COMMA_TK expression
    | expression
    ;
%%


/**
 * @brief Parse the token stream.
 * @param tokens The token stream.
 */
int parse(Token *tokens) {
    /* Tokenize the input file. */
    tokenHead = tokens;
    currentToken = tokenHead;
    
    /* Parse the token stream. */
    int result = yyparse();
    printf("Result: %s\n", result == 0 ? "Passed" : "Syntax Error");
    
    return result;
}

