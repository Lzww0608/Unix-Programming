#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

// 替换 apue.h 中的 err_sys 函数
void err_sys(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, ": %s\n", strerror(errno));
    va_end(args);
    exit(1);
}

// 定义 RWRWRW 宏，表示用户、组和其他用户都具有读写权限
#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(void) {
    // 创建第一个文件 "foo"，此时 umask 值为 0
    umask(0);
    if (creat("foo", RWRWRW) < 0) {
        err_sys("creat error for foo");
    } else {
        printf("File 'foo' created successfully.\n");
    }

    // 创建第二个文件 "bar"，此时 umask 值禁止组用户和其他用户的读写权限
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (creat("bar", RWRWRW) < 0) {
        err_sys("creat error for bar");
    } else {
        printf("File 'bar' created successfully.\n");
    }

    exit(0);
}