//
// Created by 姚坤 on 2023/3/16.
//
# include <stdio.h>
# include "000print_array.h"

void bubble(int a[], int len){
    for(int i=0;i<len;i++){
        for(int j=0; j<len-i-1;j++){
            if(a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}


void bubble_2(int a[], int len){
    for(int i=0;i<len;i++){
        int sorted = 1;
        for(int j=0; j<len-i-1;j++){
            if(a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                sorted = 0;
            }
        }
        if(sorted == 1){    // 一轮比较下来没有发生交换，可以说明已经有序了
            return;
        }
    }
}

int main(){
    int a[] = {5, 8, 1, 10, 3, 2, 111};
    int len = sizeof(a)/sizeof(int);
    print_array(a, len);
    bubble_2(a, len);
    print_array(a, len);
    return 0;
}



