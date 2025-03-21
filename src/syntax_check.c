#include"syntax_check.h"
int in_rule = 0;

void check_syntax(const char *line,int line_num){
    if(in_rule&&line[0]=='\t'){
        printf("Line%d: Command found before rule\n",line_num);
      exit(1);
    }else if(in_rule){
        in_rule=0;
    }
    //检查目标行是否有冒号
        char *colon=strstr(line,":");
        if(colon==NULL){
            //没有冒号，且不是命令行
        printf("Line%d: Missing colon in target definition\n",line_num);
        exit(1);
        }
    //检查命令是否以Tab开头
    else{
        //目标行不能以tab开头
        if(line[0]!='\t'){
        printf("Line%d: Command must start with Tab\n",line_num);
        exit(1);
    }
}
}