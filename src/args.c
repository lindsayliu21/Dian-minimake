#include"args.h"
#include<stdio.h>
#include<string.h>
 //打印 --help
void print_help(){
    printf("Usage:minimake[target][options]\n");
        printf("Options:\n");
        printf("  --help\tDisplay this help message\n");
    }
//命令⾏参数解析      
void parse_args(int argc,char *argv[]){
if(argc==1){
    printf("Error: No target specificied\n");
    exit(1);
}
if(strcmp(argv[1],"--help")==0){
    print_help();
    return 0;
}
else if(strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0){
    verbose_mode = 1;
}
else{
    printf("Error: Invalid arguments!\n");
    exit(1);//无效参数
}
if(argc>2){
    printf("Error: Too many argument!\n");
    exit(1);//参数过多
}

}
