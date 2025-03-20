//Makefile预处理
#ifndef PREPROCESS_H
#define PREPROCESS_H
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
 //辅助函数：去除首尾空白字符
static void trim_whitespace(char *str);
//辅助函数：去除注释和行尾空格
static void remove_comments_and_trims(char *line);
//预处理与⽂件读取
void preprocess_makefile(const char *filename);
#endif