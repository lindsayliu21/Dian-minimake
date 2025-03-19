
#include"parser.h"
//解析单行规则
void parse_rule(const char *line, Rule *rule){
char buffer[256];
strcpy(buffer,line);
//检查是否有冒号分隔符
char *colon=strchr(buffer,':');
if(colon==NULL){
    fprintf(stderr,"错误：目标行缺少冒号！\n");
    return ;
}
*colon='\0';//分割字符
strncpy(rule->target,buffer,32);
char *deps=colon+1;
rule->dep_count=0;
char *token=strtok(deps," ");
while(token!=NULL&&rule->dep_count< MAX_DEPS){
    strncpy(rule->dependencies[rule->dep_count],token,32);
    rule->dep_count++;
    token=strtok(NULL," ");
}
}
//检查重复目标
void check_duplicte_target(Rule rules[],int rule_count,const char *target){
    for(int i;i<rule_count;i++){
        if(strcmp(rules[i].target,target)==0){
            fprintf(stderr,"Error: Duplicate target definition '%s'\n",target);
            return;
        }
    }
}
//检查是否以.c结尾
int ends_with_dot_c(const char *str){
    const char *dot=strstr(str,'.');
    return (dot!=NULL&&*(dot+1)=='c'&&(dot+2)=='\0');
}
//检查依赖是否存在 
//1）先检查是否是存在的文件 2）再检查是否是其他规则的目标 3）若两者都不满足，报告错误
void check_dependencies(Rule rules[],int rule_count){
   for(int i=0;i<rule_count;i++){
    for(int j=0;j<rules[i].dep_count;j++){
        const char *dep=rules[i].dependencies[j];
        int exists=0;
        //检查目标是.c文件还是目标
        int key=ends_with_dot_c(dep);
        // .c文件     
        if(key){
        //检查是否是存在的文件
        FILE *file=fopen(dep,"r");
        if(file!=NULL){
            fclose(file);
            exists=1;
        }
        //文件不存在，报错
        else 
        {printf("Error: Invalid dependency '%s'\n",dep);}}
        //若是其他规则的目标
        else{
            for(int k=0;k<rule_count;k++){
                if(strcmp(rules[k].target,dep)==0){
                    exists=1;
                    break;
                }
            }
        
        //依赖是未定义的⽬标，报告错误
        if(!exists){
            fprintf(stderr,"Invalid dependency '%s'\n",dep);
            exit(1);
        }}
    }
   } 
}