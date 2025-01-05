#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>


int main(void) {
    int fd;

    // 打开一个文件，如果不存在则创建，可读写
    fd = open("tempfile", O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
        printf("open error: %s\n", strerror(errno));
        return -1;
    }

    // 取消文件的硬链接(unlink)，使其不在有文件名
    if (unlink("tempfile") < 0) {
        printf("unlink error: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    printf("file unlinked\n");

    // 关闭文件
    close(fd);

    // 等待10秒，确保文件被删除
    sleep(10);

    printf("done\n");

    return 0;
}                                                                                             