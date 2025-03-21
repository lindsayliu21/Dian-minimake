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
#include<libgen.h>
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
        char *makefile_path = "Makefile";  // 默认在当前目录查找
    char *target = NULL;
     // 优先处理 --help
     for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            exit(0);
        }
    }
     // 解析其他参数
     for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose_code = 1;
        }
        else if (argv[i][0] != '-') {
            target = argv[i];
        } else {
            fprintf(stderr, "错误: 未知选项 '%s'\n", argv[i]);
            exit(1);
        }
    }
    if (!target) {
        fprintf(stderr, "错误: 未指定构建目标\n");
        exit(1);
    }
    
   printf("正在构建目标：%s\n",target);
        target = argv[1];
    
        // 3. 预处理Makefile
        preprocess_makefile(makefile_path,"Minimake_cleared.mk",verbose_code);
        int rule_count ;
        // 4. 读取清理后的Makefile并进行语法检查
        FILE *cleaned_file = fopen("Minimake_cleared.mk", "r");
        if (!cleaned_file) {
            perror("无法打开清理后的Makefile");
            exit(EXIT_FAILURE);
        }
    
        char line[256];
        int line_num = 0;
        Rule rules[MAX_TARGETS];
       
        // 5. 逐行解析规则
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
    
    
        //6. 检查依赖有效性
        check_dependencies(rules, rule_count);
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
       
    free(order);

    return 0;
    
    }

