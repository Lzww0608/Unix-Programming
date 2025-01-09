#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINE 4096

int main(void) {
    char buf[MAXLINE];

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            fprintf(stderr, "fputs error");
            exit(1);
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "fgets error");
        exit(1);
    }

    exit(0);
}