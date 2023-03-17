//
// Created by 姚坤 on 2023/3/17.
//

#include <stdio.h>
#include "000tool.h"

void selection(int array[], int len){
    int swap_count = 0;
    int cmp_count = 0;
    int loop_count = 0;
    long long start = get_current_timestamp();
    for(int i=0;i<len;i++){
        int index = 0;
        for(int j=1;j<len-i;j++){
            loop_count++;
            if(cmp(array[j], array[index], &cmp_count) > 0){
                index = j;
            }
        }

        swap(array, index, len-i-1, &swap_count);
    }
    long long end = get_current_timestamp();
    printf("selection time take = %lld(ms), swap count num = %d, cmp count num = %d, loop count num = %d\n", end-start, swap_count, cmp_count, loop_count);
}
