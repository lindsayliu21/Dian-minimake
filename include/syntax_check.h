//静态语法检查
#ifndef SYNTAX_CHECK_H
#define SYNTAX_CHECK_H
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
 //全局状态：标记是否在规则规则中（目标行之后）
static bool in_rule=false;
//静态语法检查
void check_syntax(const char *line,int line_num);
#endif
