//
// Created by 姚坤 on 2023/3/17.
//
#include <stdlib.h>
# include "./sort/000tool.h"
# include "./sort/001bubble.h"
# include "./sort/002selection.h"

int main(){
    int a1[] = {5, 8, 1, 10, 3, 2, 111};
    // int a1[] = {1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(a1)/sizeof(int);

    int *a2 = copy_array(a1, len);
    int *a3 = copy_array(a1, len);

    bubble_2(a1, len);
    // print_array(a1, len);

    bubble(a2, len);
    // print_array(a2, len);

    selection(a3, len);
    // print_array(a3, len);

    free(a2);
    free(a3);
    return 0;
}