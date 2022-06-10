//
// Created by 姚坤 on 2022/6/10.
//
#include <stdio.h>
int print_binary(unsigned long v,int rev){
    int power = (8 * sizeof(v));
    char str[power+1];

    for (int j = 0; j < power; ++j) {
        if(rev == 0){
            str[power-1-j] = (char)((v & 1) + 48);
        }else{
            str[j] = (char)((v & 1) + 48);
        }
        v >>= 1;
    }
    str[power] = '\0';
    printf("%s\n",str);
    return 0;
}

// 打印低len位
int printbits(unsigned long v,int len){
    char str[len+1];

    for (int i = 0; i < len; ++i) {
        str[len-1-i] = (char)((v & 1) + 48);
        v >>= 1;
    }
    str[len] = '\0';
    printf("%s",str);
    return 0;
}
