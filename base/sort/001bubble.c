//
// Created by 姚坤 on 2023/3/16.
//
# include <stdio.h>
# include "000tool.h"

void bubble(int a[], int len){
    int swap_count = 0;
    int cmp_count = 0;
    int loop_count = 0;
    long long start = get_current_timestamp();
    for(int i=0;i<len;i++){
        for(int j=0; j<len-i-1;j++){
            loop_count++;
            if(cmp(a[j], a[j+1], &cmp_count) > 0){
                swap(a, j, j+1, &swap_count);
            }
        }
    }
    long long end = get_current_timestamp();
    printf("bubble time take = %lld(ms), swap count num = %d, cmp count num = %d, loop count num = %d\n", end-start, swap_count, cmp_count, loop_count);
}


void bubble_2(int a[], int len){
    int swap_count = 0;
    int cmp_count = 0;
    int loop_count = 0;
    long long start = get_current_timestamp();
    for(int i=0;i<len;i++){
        int sorted = 1;
        for(int j=0; j<len-i-1;j++){
            loop_count++;
            if(cmp(a[j], a[j+1], &cmp_count) > 0){
                swap(a, j, j+1, &swap_count);
                sorted = 0;
            }
        }
        if(sorted == 1){    // 一轮比较下来没有发生交换，可以说明已经有序了
            break;
        }
    }
    long long end = get_current_timestamp();
    printf("bubble_2 time take = %lld(ms), swap count num = %d, cmp count num = %d, loop count num = %d\n", end-start, swap_count, cmp_count, loop_count);
}



