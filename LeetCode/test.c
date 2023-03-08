//
// Created by 姚坤 on 2023/3/7.
//

#include <stdio.h>

int main(int argc, char *argv[], char *env[]){
    printf("参数个数：%d\n", argc);

    while (*argv){
        printf("%s ", *argv++);
    }
    printf("\n");

    while (*env){
        printf("%s ", *env++);
    }
    printf("\n");
    return 0;
}
