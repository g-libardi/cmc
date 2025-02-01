#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"


char next(Scanner *scanner) {
    // Read file if buffer is empty
    if (scanner->position == scanner->size) {
        scanner->size = fread(scanner->buffer, sizeof(char), scanner->buffer_size, scanner->file);
        scanner->position = 0;
    }

    // Return EOF if buffer is empty
    if (scanner->size == 0) {
        return EOF;
    }

    // Return next character
    return scanner->buffer[scanner->position++];
}


Scanner new_scanner(char *filename, int buffer_size) {
    // Get file descriptor
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Allocate buffer
    char *buffer = (char *)malloc(sizeof(char) * buffer_size);
    if (!buffer) {
        fprintf(stderr, "Error: Could not allocate buffer\n");
        exit(1);
    }

    // Initialize scanner
    Scanner scanner;
    scanner.file = file;
    scanner.buffer = buffer;
    scanner.buffer_size = buffer_size;
    scanner.position = 0;
    scanner.size = 0;
    scanner.next = next;

    return scanner;
}


void free_scanner(Scanner *scanner) {
    free(scanner->buffer);
    fclose(scanner->file);
}
