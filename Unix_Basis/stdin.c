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

    /* 从标准输入读取数据,直到遇到EOF或错误 */
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        /* 将读取的数据写入标准输出 */
        if (write(STDOUT_FILENO, buf, n) == -1) {
            err_sys("Write error");
        }
    }

    /* 如果read返回负值,说明读取出错 */
    if (n < 0) {
        err_sys("read error"); 
    }

    exit(0);
}