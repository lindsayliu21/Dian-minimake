#ifndef AGRS_H
#define ARGS_H;
int verbose_mode=0;
 //打印--help
void print_help();
//命令⾏参数解析
void parse_args(int argc,char *argv[]);
#endif