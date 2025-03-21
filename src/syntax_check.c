#include"syntax_check.h"


void check_syntax(const char *line,int line_num,int *in_rule){
    if(!*in_rule){
        char *colon = strstr(line, ":");
        if(colon==NULL){
            printf("Line %d: Missing colon in target definition\n", line_num);
        exit(1);
        }
        else if(line[0] != '\t'){
            printf("Line %d: Command found before rule\n", line_num);
            exit(1);}
        *in_rule=1;
        return;
    }
    else{
        if(line[0] != '\t'){
        printf("Line %d: Command must start with Tab\n", line_num);
        exit(1);
        }
    *in_rule=0;
    return;
    }
    
}