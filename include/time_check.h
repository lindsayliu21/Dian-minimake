//静态语法检查
#ifndef TIME_CHECK_H
#define TIME_CHECK_H
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
 // 获取文件的修改时间
time_t get_mtime(const char* filename);
// 检查是否需要重新构建
int needs_rebuild(const char* target, const char** dependencies, int dep_count) ;
#endif
