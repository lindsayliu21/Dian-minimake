#ifndef PREPROCESS_H
#define PREPROCESS_H
 //辅助函数：去除首尾空白字符
static void trim_whitespace(char *str);
//辅助函数：去除注释和行尾空格
static void remove_comments_and_trims(char *line);
//预处理与⽂件读取
void preprocees_makefile(const char *filename);
#endif