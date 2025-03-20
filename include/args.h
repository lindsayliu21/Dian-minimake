//命令行解析
#ifndef ARGS_H
#define ARGS_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 //打印--help
void print_help();
//命令⾏参数解析
void parse_args(int argc,char *argv[]);
#endif