//
// Created by 姚坤 on 2023/3/16.
//
# include <stdio.h>
# include "000print_array.h"
int main(){
    int a[] = {5, 8, 1, 10, 3, 2, 111};
    int len = sizeof(a)/sizeof(int);
    print_array(a, len);
    return 0;
}

