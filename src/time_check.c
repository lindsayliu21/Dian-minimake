#include <sys/stat.h> // 用于 stat() 函数
#include <time.h>     // 用于 time_t 类型
#include"time_check.h"
// 获取文件的修改时间
time_t get_mtime(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == -1) {
        perror("无法获取文件状态");
        return -1; // 文件不存在或无法访问
    }
    return st.st_mtime;
}

// 检查是否需要重新构建
int needs_rebuild(const char* target, const char** dependencies, int dep_count) {
    time_t target_mtime = get_mtime(target);
    if (target_mtime == -1) {
        // 目标文件不存在，需要构建
        return 1;
    }

    for (int i = 0; i < dep_count; i++) {
        time_t dep_mtime = get_mtime(dependencies[i]);
        if (dep_mtime == -1) {
            fprintf(stderr, "错误: 依赖文件 '%s' 不存在\n", dependencies[i]);
            exit(1);
        }
        if (dep_mtime > target_mtime) {
            // 依赖文件比目标文件新，需要重新构建
            return 1;
        }
    }

    // 目标文件是最新的，无需重新构建
    return 0;
}