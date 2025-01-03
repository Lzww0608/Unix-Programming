**ls -l**
-: 普通文件
d: 目录
l: 符号链接
b: 块设备文件
c: 字符设备文件
p: 命名管道 (FIFO)
s: 套接字 (Socket)



**总结:**

| 特性         | `stat`                                   | `lstat`                                  | `fstatat`                                                                |
|--------------|-------------------------------------------|-------------------------------------------|-------------------------------------------------------------------------|
| 核心功能     | 获取文件/目录状态信息                      | 获取文件/目录状态信息                      | 获取文件/目录状态信息                                                   |
| 符号链接处理 | **跟随**                                   | **不跟随**                                 | 由 `flags` 控制：跟随 (默认) 或不跟随 (`AT_SYMLINK_NOFOLLOW`)              |
| 路径解析     | 相对于当前工作目录或绝对路径              | 相对于当前工作目录或绝对路径              | 相对于当前工作目录 (使用 `AT_FDCWD`) 或由 `dirfd` 指定的目录或绝对路径 |
| 主要用途     | 获取目标文件的属性                       | 获取符号链接本身的属性                   | 更安全、原子性的文件操作，可灵活控制符号链接跟随                         |
| 参数 `dirfd` | 无                                        | 无                                        | 指定相对路径解析的起始目录                                              |
| 参数 `flags` | 无                                        | 无                                        | 控制符号链接跟随行为                                                      |



`chmod -X`: 为目录添加执行权限，文件不添加
`chmod -R`: 递归修改目录下的所有文件和子目录的权限