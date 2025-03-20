#include"preprocess.h"
#include"args.h"


//辅助函数: 去除首尾空白字符
static void trim_whitespace(char *str){
    char *end;
    //空字符串处理
    if(*str=='\0'){
        return;
    }
    //去除前导空白
    while(isspace((unsigned char)*str))str++;
    //去除尾部空白
    end=str+strlen(str)-1;
    while(end>str&&isspace((unsigned char)*end)) end--;
    //终止符
    *(end+1)='\0';
}
//辅助函数：去除注释和行尾空格
static void remove_comments_and_trims(char *line){
    char *comment_start=strchr(line,'#');
    if(comment_start){
        *comment_start='\0';
    }
    trim_whitespace(line);
}
//预处理与⽂件读取
void preprocess_makefile(const char *filename){
    int verbose_mode=0;
FILE *infile=fopen(filename,"r");
if(!infile){
    perror("Error: Failed to open Makefile\n");
    exit(1);
}
FILE *outfile = NULL;
    if (verbose_mode) {
        outfile = fopen("Minimake_cleared.mk", "w");
        if (!outfile) {
            perror("Error: Failed to create output file\n");
            fclose(infile);
            exit(1);
        }
    }
char line[256];
while(fgets(line,sizeof(line),infile)){
    //去除行尾换行符
    line[strcspn(line,"\n")]='\0';
    //去除注释#和行尾空格
    remove_comments_and_trims(line);
    //去除首尾空白
   printf("处理后的行：%s\n",line);
   //过滤空行
   if(line[0]=='\0'){continue;}
   printf("Porocessed line: [%s]\n",line);
   if (verbose_mode) {
     fprintf(outfile, "%s\n", line);
}
}
fclose(infile);
    if (verbose_mode) {
        fclose(outfile);
    }
}
