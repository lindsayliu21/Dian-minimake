//规则解析与存储
#ifndef PARSER_H
#define PARSER_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_TARGETS 10
#define MAX_DEPS 10
#define MAX_COMMAND_LEN 256
typedef struct Rule{
    char target[32];//目标名称
    char dependencies[MAX_DEPS][32];//依赖列表
    int dep_count;//依赖数量
    char command[MAX_COMMAND_LEN];//编译命令
} Rule;
//解析单行规则
void parse_rule(const char *line,Rule *rule);
//检查重复目标
void check_duplicate_target(Rule rules[],int rule_count,const char*target);
//检查是否以.c结尾
int ends_with_dot_c(const char *str);
//检查依赖是否存在
void check_dependencies(Rule rules[],int rule_count);
#endif