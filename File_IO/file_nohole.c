#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) /* 0644 */

// Replacement for err_sys from apue.h
void err_sys(const char *msg) {
    perror(msg);
    exit(1);
}

int main(void) {
    int fd;
    char buf[16394];
    for (int i = 0; i < 16394; i++) {
        buf[i] = 'a';
    }

    if ((fd = creat("file.nohole", FILE_MODE)) < 0)
        err_sys("creat error");


    if (write(fd, buf, 16394) != 16394)
        err_sys("buf write error");

    /* offset now = 16394 */

    close(fd);
    exit(0);
}