#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define VERSION "2.3.4"
#define LOG_ERR(format, ...)\
    fprintf(stderr,format,__VA_ARGS__)
int main(int argc, char** argv){
    if(argc < 3){
        LOG_ERR("Invalid number of args, for v%s\n!\n",VERSION);
        exit(1);
    }
    if(strcmp(argv[1],"-n")!=0){
        LOG_ERR("%s is a wrong param at index %d for v%s.\n",argv[1],1,VERSION);
        exit(1);
    }
}
