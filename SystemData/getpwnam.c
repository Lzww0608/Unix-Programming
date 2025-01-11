#include <pwd.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* 根据用户名查找密码文件条目
 * 参数:
 *   name: 要查找的用户名
 * 返回值:
 *   成功返回对应的passwd结构体指针
 *   失败返回NULL
 */
struct passwd *getpwnam(const char *name) {
    struct passwd *pwd;
    
    /* 打开密码文件 */
    setpwent();
    
    /* 遍历密码文件中的每一项 */
    while ((pwd = getpwent()) != NULL) {
        //printf("正在检查用户: %s\n", pwd->pw_name);
        /* 比较用户名是否匹配 */
        if (strcmp(pwd->pw_name, name) == 0) {
            endpwent();
            return pwd;
        }
    }
    
    /* 关闭密码文件 */
    endpwent();
    
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("用法: %s username\n", argv[0]);
        return 1;
    }

    struct passwd *pwd = getpwnam(argv[1]);
    if (pwd == NULL) {
        printf("找不到用户: %s\n", argv[1]);
        return 1;
    }

    printf("用户名: %s\n", pwd->pw_name);
    printf("用户ID: %d\n", pwd->pw_uid);
    printf("组ID: %d\n", pwd->pw_gid); 
    printf("真实姓名: %s\n", pwd->pw_gecos);
    printf("主目录: %s\n", pwd->pw_dir);
    printf("Shell: %s\n", pwd->pw_shell);

    return 0;
}
