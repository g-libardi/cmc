#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    Scanner scanner = new_scanner(argv[1], 10);

    char c = scanner.next(&scanner);
    while (c != EOF) {
        printf("%c", c);
        c = scanner.next(&scanner);
    }

    free_scanner(&scanner);

    return 0;
}
