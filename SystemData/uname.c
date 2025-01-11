#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname name;
    
    if (uname(&name) == -1) {
        printf("获取系统信息失败\n");
        return 1;
    }
    
    printf("操作系统名称: %s\n", name.sysname);
    printf("主机名: %s\n", name.nodename);
    printf("发行版本: %s\n", name.release);
    printf("版本: %s\n", name.version);
    printf("硬件架构: %s\n", name.machine);
    
    return 0;
}
