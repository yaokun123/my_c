//
// Created by 姚坤 on 2023/3/17.
//
# include "./sort/000tool.h"
# include "./sort/001bubble.h"

int main(){
    int a[] = {5, 8, 1, 10, 3, 2, 111};
    int len = sizeof(a)/sizeof(int);

    int *b = copy_array(a, len);
    print_array(b, len);
    print_array(a, len);
    bubble_2(a, len);
    print_array(a, len);

    return 0;
}