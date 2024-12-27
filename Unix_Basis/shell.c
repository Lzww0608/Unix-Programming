#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 1024 

void err_sys(const char *msg) {
    perror(msg);
    exit(1);
}

void err_ret(const char *fmt, const char *arg) {
    fprintf(stderr, fmt, arg);
    fprintf(stderr, ": %s\n", strerror(errno));
}

int main(void) {
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% "); /* print prompt (printf requires %% to print %) */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0'; /* replace newline with null */
        }

        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) { /* child */
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        /* parent */
        if ((pid = waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error");
        }
        printf("%% ");
    }

    exit(0);
}