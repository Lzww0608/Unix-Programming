/*
为什么这种方式能防止僵尸进程？

第一个 fork()： 原始父进程 waitpid 了第一个子进程，确保了第一个子进程不会变成僵尸进程。

第二个 fork() 和第一个子进程的退出： 当第一个子进程退出时，第二个子进程会被 init 进程收养。 
init 进程的一个重要职责就是定期回收孤儿进程的资源，包括已终止的子进程。因此，第二个子进程结束时，
init 进程会负责回收其资源，它不会变成僵尸进程。
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

pid_t create_detached_process(void) {
    pid_t pid;

    // 第一次 fork
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        return -1; // 返回 -1 表示创建失败
    } else if (pid > 0) {
        // 父进程 (原始进程)
        // 等待第一个子进程结束，但不关心其状态
        if (waitpid(pid, NULL, 0) != pid) {
            perror("waitpid error");
            // 这里可以选择是否继续执行，或者直接返回错误
        }
        return 0; // 父进程成功返回 0，表示完成了创建分离子进程的任务
    } else {
        // 第一个子进程
        // 第二次 fork
        pid = fork();
        if (pid < 0) {
            perror("fork error");
            exit(EXIT_FAILURE); // 第一个子进程创建第二个子进程失败，直接退出
        } else if (pid > 0) {
            // 第一个子进程 (作为第二个子进程的父进程)
            exit(EXIT_SUCCESS); // 第一个子进程直接退出，将第二个子进程交给 init 进程管理
        } else {
            // 第二个子进程 (我们真正想要的分离进程)
            // 从这里开始执行第二个子进程的逻辑
            sleep(2);
            printf("second child, parent pid = %ld\n", (long)getppid());
            return getpid(); // 返回第二个子进程的 PID
        }
    }
    // 理论上不应该执行到这里
    return -1;
}

int main() {
    pid_t detached_pid = create_detached_process();

    if (detached_pid > 0) {
        printf("Detached process created with PID: %d\n", detached_pid);
        // 父进程可以继续执行自己的逻辑，无需担心分离的子进程
    } else if (detached_pid == 0) {
        printf("Parent process finished creating detached process.\n");
    } else {
        fprintf(stderr, "Failed to create detached process.\n");
        return 1;
    }

    // 父进程可以执行其他操作
    sleep(5);
    printf("Parent process exiting.\n");

    return 0;
}