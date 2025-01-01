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
    char buf1[] = "abcdefghij";
    char buf2[] = "ABCDEFGHIJ";

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");

    /* offset now = 10 */

    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");

    /* offset now = 16384 */

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");

    /* offset now = 16394 */

    close(fd);
    exit(0);
}