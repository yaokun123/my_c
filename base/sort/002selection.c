//
// Created by 姚坤 on 2023/3/17.
//

#include <stdio.h>
#include "000tool.h"

void selection(int array[], int len){
    for(int i=0;i<len;i++){
        int index = 0;
        for(int j=1;j<len-i;j++){
            if(array[index] < array[j]){
                index = j;
            }
        }

        int tmp = array[index];
        array[index] = array[len-i-1];
        array[len-i-1] = tmp;
    }
}

int main(){
    int a[] = {5, 8, 1, 10, 3, 2, 111};
    int len = sizeof(a)/sizeof(int);
    print_array(a, len);
    selection(a, len);
    print_array(a, len);
    return 0;
}
