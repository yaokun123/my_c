//
// Created by 姚坤 on 2023/3/16.
//
# include <stdio.h>
# include "000tool.h"

void bubble(int a[], int len){
    int swap_count = 0;
    for(int i=0;i<len;i++){
        for(int j=0; j<len-i-1;j++){
            if(a[j] > a[j+1]){
                swap(a, j, j+1, &swap_count);
            }
        }
    }
}


void bubble_2(int a[], int len){
    int swap_count = 0;
    int cmp_count = 0;
    long long start = get_current_timestamp();
    for(int i=0;i<len;i++){
        int sorted = 1;
        for(int j=0; j<len-i-1;j++){
            if(cmp(a[j], a[j+1], &cmp_count) > 0){
                swap(a, j, j+1, &swap_count);
                sorted = 0;
            }
        }
        if(sorted == 1){    // 一轮比较下来没有发生交换，可以说明已经有序了
            long long end = get_current_timestamp();
            printf("bubble_2 time take = %lld(ms)\n", end-start);
            printf("bubble_2 swap count num = %d\n", swap_count);
            printf("bubble_2 cmp count num = %d\n", cmp_count);
            return;
        }
    }
    long long end = get_current_timestamp();
    printf("bubble_2 time take = %lld(ms)\n", end-start);
    printf("bubble_2 swap count num = %d\n", swap_count);
    printf("bubble_2 cmp count num = %d\n", cmp_count);
}

int main(){
    int a[] = {5, 8, 1, 10, 3, 2, 111};
    int len = sizeof(a)/sizeof(int);
    print_array(a, len);
    bubble_2(a, len);
    print_array(a, len);
    return 0;
}



