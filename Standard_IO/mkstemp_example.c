#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// Replacement for err_sys from apue.h
void err_sys(const char *msg) {
    perror(msg);
    exit(1);
}

void make_temp(char *template);

int main() {
    // `mkstemp` 需要一个指向字符串的指针，字符串必须要可以修改
    char good_template[] = "/tmp/dirXXXXXX"; /* right way */
    //只有指针在栈上，字符串为只读，保存在常量区
    char *bad_template = "/tmp/dirXXXXXX";  /* wrong way */

    printf("trying to create first temp file...\n");
    make_temp(good_template);

    printf("trying to create second temp file...\n");
    make_temp(bad_template);

    exit(0);
}

void make_temp(char *template) {
    int fd;
    struct stat sbuf;

    if ((fd = mkstemp(template)) < 0) {
        err_sys("can't create temp file");
    }
    printf("temp name = %s\n", template);
    close(fd);

    if (stat(template, &sbuf) < 0) {
        if (errno == ENOENT) {
            printf("file doesn't exist\n");
        } else {
            err_sys("stat failed");
        }
    } else {
        printf("file exists\n");
        unlink(template); // Delete the temporary file
    }
}