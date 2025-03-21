#include"syntax_check.h"


void check_syntax(const char *line,int line_num,int *in_rule){
    // 检查目标行是否有冒号
    char *colon = strstr(line, ":");
    if (colon != NULL) {
        *in_rule = 1;  // 进入规则
    } else if (*in_rule && line[0] == '\t') {
        // 检查命令是否以 Tab 开头
        printf("Line %d: Command found before rule\n", line_num);
        exit(1);
    } else if (*in_rule && line[0] != '\t' && line[0] != '\0') {
        // 检查命令是否以 Tab 开头
        printf("Line %d: Command must start with Tab\n", line_num);
        exit(1);
    } else if (colon == NULL && line[0] != '\0') {
        // 检查目标行是否缺少冒号
        printf("Line %d: Missing colon in target definition\n", line_num);
        exit(1);
    }
}