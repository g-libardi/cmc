/**
 * @file scanner.h
 * @brief This module reads streams of characters from a file.
 */

#ifndef SCANNER_H
#define SCANNER_H

/**
 * @brief Scanner structure.
 */
typedef struct Scanner {
    FILE *file;
    char *buffer;
    int buffer_size;
    int position;
    int size;

    /**
     * @brief Get the next character from the file.
     * @param scanner The scanner pointer.
     * @return The next character from the file or EOF if the end of the file is reached.
     */
    char (*next)(struct Scanner *scanner);
} Scanner;

/**
 * @brief Create a scanner instance.
 * @param filename The file path to read.
 * @param buffer_size The buffer size to read the file.
 * @return The scanner instance.
 */
Scanner new_scanner(char *filename, int buffer_size);

/**
 * @brief Free the scanner resources.
 * @param scanner The scanner pointer.
 */
void free_scanner(Scanner *scanner);

#endif // SCANNER_H
