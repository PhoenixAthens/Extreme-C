#include <stdio.h>
#include <string.h>
#define ABC 4
#define ADD(a,b)a+b
#define CODE \
printf("%d\n",i)

#define printVar(a) printf("%d\n",a);
#define startLoop(v,s,e) for(int v=s;v<=e;v++){
#define endLoop }

#define cmd(Name) \
    char Name ## _cmd[256] = ""; \
    strcpy(Name ## _cmd,#Name);


int main(int argc, char** argv){

    int x = 5;
    int y = ABC;
    int z = x+y;
    printf("result-1: %d\n",z);
    int a = ADD(x,z);
    printf("result-2: %d\n",a);
    //CODE;
    startLoop(counter, 1, 10)
        printVar(counter)
    endLoop

    cmd(copy);
    cmd(paste);
    cmd(cut);
    char uIn[256];
    scanf("%s",uIn);
    if(strcmp(uIn,copy_cmd)==0){
        printf("We copy\n");
    }else if(strcmp(uIn,cut_cmd)==0){
        printf("We cut\n");
    }else if(strcmp(uIn,paste_cmd)==0){
        printf("We paste\n");
    }else{
        printf("Don't know!\n");
    }
    return 0;
}
