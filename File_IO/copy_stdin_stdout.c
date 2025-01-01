#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE  4096

// Replacement for err_sys from `apue.h`
void err_sys(const char *msg) {
    perror(msg);
    exit(1);
}

int main(void) {
    int n;
    char buf[BUFSIZE];
    while ((n == read(STDIN_FILENO, buf, BUFSIZE) > 0)) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            err_sys("write error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    exit(0);
}