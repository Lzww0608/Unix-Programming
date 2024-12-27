#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void err_sys(const char *msg) {
    perror(msg);
    exit(1);
}
#define     BUFFSIZE    4096


int main(void) {
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) == -1) {
            err_sys("Write error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }

    exit(0);
}