#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "lexer.h"
#include "pparser.h"
#include <string.h>

void run_lexical_analyzer(char *filename) {
    Token *token = tokenize(filename);
    Token *head = token;
    while (token != NULL) {
        printf("%s \"%s\" [linha: %d]\n", token_type_to_str(token->type), token->lexeme, token->line);
        token = token->next;
    }
    free_tokens(head);
}

void run_parser(char *filename) {
    Token *token = tokenize(filename);
    parse(token);
    free_tokens(token);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s [OPTIONS] <filename>\n", argv[0]);
        return 1;
    }
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s [OPTIONS] <filename>\n", argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "-L") == 0) {
            run_lexical_analyzer(argv[i + 1]);
            return 0;
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "-P") == 0) {
            run_parser(argv[i + 1]);
            return 0;
        }
    }


    return 0;
}
