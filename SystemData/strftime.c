#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {
    time_t t;
    struct tm *tmp;
    char buf1[16];
    char buf2[64];

    time(&t);
    tmp = localtime(&t);

    if (strftime(buf1, sizeof(buf1), "%Y-%m-%d %H:%M:%S", tmp) == 0) {
        printf("buffer length 16 is too small\n");
    } else {
        printf("buf1: %s\n", buf1);
    }

    if (strftime(buf2, sizeof(buf2), "%A, %d %B %Y, %H:%M:%S %Z", tmp) == 0) {
        printf("buffer length 64 is too small\n");
    } else {
        printf("buf2: %s\n", buf2);
    }

    exit(0);
}