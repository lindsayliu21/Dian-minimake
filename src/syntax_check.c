#include"syntax_check.h"
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
//全局状态：标记是否在规则规则中（目标行之后）
static bool in_rule=false;
void check_syntax(const char *line,int line_num){
    //检查目标行是否有冒号
    if(!in_rule){
        char *colon=strstr(line,':');
        if(colon==NULL){
        if(line[0]=='\t') 
        printf("Line%d: Command found before rule\n",line_num);
        else printf("Line%d: Missing colon in target definition\n",line_num);
        exit(1);
        }
    }
    //检查命令是否以Tab开头
    else{if(line[0]!='\t'){
        printf("Line%d: Command must start with Tab\n",line_num);
        exit(1);
    }
    }
}