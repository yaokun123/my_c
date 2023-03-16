//
// Created by 姚坤 on 2023/3/16.
//
#include <stdio.h>
void print_array(int array[], int len){
    printf("[");
    for(int i=0; i<len; i++){
        if(i == len-1){
            printf("%d", array[i]);
        }else{
            printf("%d,", array[i]);
        }
    }
    printf("]\n");
}