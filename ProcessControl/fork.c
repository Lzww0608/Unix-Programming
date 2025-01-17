#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int globvar = 6;          /* external variable in initialized data */
char buf[] = "a write to stdout\n";

void err_sys(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void) {
    int        var;        /* automatic variable on the stack */
    pid_t      pid;

    var = 88;
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
        err_sys("write error");
    }
    printf("before fork\n"); /* we don't flush stdout */

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        /* child */
        globvar++;           /* modify variables */
        var++;
    } else {
        /* parent */
        sleep(2);          /* parent */
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}