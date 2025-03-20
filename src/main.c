#include "args.h"
#include "preprocess.h"
#include "syntax_check.h"
#include "parser.h"
#include  "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <time.h>
int verbose_code=0;
// 读取并解析Makefile
/*Rule *parse_makefile(const char *filename, int *rule_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("无法打开Makefile");
        exit(1);
    }

    Rule *rules = malloc(sizeof(Rule) * 10);  // 假设最多10条规则
    *rule_count = 0;
    char line[256];
    int current_rule = -1;
    char outfile;

    while(fgets(line, sizeof(line), file)){
        // 预处理：去除注释和空格
        preprocess_makefile(line,outfile,verbose_code);

        int result = parse_rule(line, &rules[*rule_count]);
        if (result == 0) {
            current_rule = (*rule_count)++;
        } else if (result == 1) {
            // 命令添加到当前规则
            if (current_rule >= 0) {
                strcpy(rules[current_rule].command, line);
            }
        }
    }

    fclose(file);
    return rules;
}*/
    // 检查文件是否存在
    int file_exists(const char *filename) {
        struct stat st;
        return (stat(filename, &st) == 0);
    }
    
    // 获取文件修改时间
    time_t get_mtime(const char *filename) {
        struct stat st;
        stat(filename, &st);
        return st.st_mtime;
    }
    
    // 执行构建命令
    void execute_command(const char *command) {
        printf("执行命令: %s\n", command);
        int status = system(command);
        if (status != 0) {
            fprintf(stderr, "命令执行失败: %d\n", status);
            exit(EXIT_FAILURE);
        }
    }
    
    // 主函数
    int main(int argc, char *argv[]) {

        // 1. 解析命令行参数
        parse_args(argc, argv);
        const char *target = argv[1];
    
        // 2. 预处理Makefile
        preprocess_makefile("Makefile","Minimake_cleared.mk",verbose_code);
        int rule_count ;
        // 3. 读取清理后的Makefile并进行语法检查
        FILE *cleaned_file = fopen("Minimake_cleared.mk", "r");
        if (!cleaned_file) {
            perror("无法打开清理后的Makefile");
            exit(EXIT_FAILURE);
        }
    
        char line[256];
        int line_num = 0;
        Rule rules[MAX_TARGETS];
       
        // 4. 逐行解析规则
        while (fgets(line, sizeof(line), cleaned_file)) {
            line_num++;
            line[strcspn(line, "\n")] = '\0'; // 去除换行符
    
            // 静态语法检查
            check_syntax(line, line_num);
    
            // 解析规则
            if (strchr(line, ':') != NULL) {
                parse_rule(line, &rules[rule_count]);
                check_duplicate_target(rules, rule_count, rules[rule_count].target);
                rule_count++;
            }
        }
        fclose(cleaned_file);
    
    
        // 5. 检查依赖有效性
        check_dependencies(rules, rule_count);
    
        // 6. 查找用户指定的目标规则
        /*Rule *target_rule = NULL;
        for (int i = 0; i < rule_count; i++) {
            if (strcmp(rules[i].target, target) == 0) {
                target_rule = &rules[i];
                break;
            }
        }
    
        if (!target_rule) {
            fprintf(stderr, "错误: 目标 '%s' 未在Makefile中定义\n", target);
            exit(EXIT_FAILURE);
        }*/
    // 构建依赖图
    Graph graph;
    init_graph(&graph);
    for (int i = 0; i < rule_count; i++) {
        for (int j = 0; j < rules[i].dep_count; j++) {
            add_edge(&graph, rules[i].target, rules[i].dependencies[j]);
        }
    }
    // 拓扑排序
    char **order = malloc(sizeof(char *) * graph.count);
    bool success = topological_sort(&graph, order);
    if (!success) {
        printf("错误: 检测到循环依赖！\n");
        return 1;
    }
     // 执行编译命令
     for (int i = 0; i < graph.count; i++) {
        const char* target = order[i];
        for (int j = 0; j < rule_count; j++) {
            if (strcmp(rules[j].target, target) == 0) {
                printf("执行命令: %s\n", rules[j].command);
                system(rules[j].command);  // 执行编译命令
                break;
            }
        }}
       /* // 7. 检查是否需要构建
        int need_rebuild = 0;
        if (!file_exists(target_rule->target)) {
            need_rebuild = 1;
        } else {
            time_t target_time = get_mtime(target_rule->target);
            for (int i = 0; i < target_rule->dep_count; i++) {
                const char *dep = target_rule->dependencies[i];
                if (get_mtime(dep) > target_time) {
                    need_rebuild = 1;
                    break;
                }
            }
        }
    
        // 8. 执行构建命令
        if (need_rebuild) {
            printf("正在构建目标: %s\n", target_rule->target);
            execute_command(target_rule->command);
        } else {
            printf("目标 '%s' 已是最新，无需构建\n", target_rule->target);
        }
    */
    // 释放资源
    free(order);

    return 0;
    
    }

