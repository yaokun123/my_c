//
// Created by 姚坤 on 2023/3/17.
//

#include "000tool.h"
#include <stdio.h>
int swap_count = 0;
int cmp_count = 0;
int loop_count = 0;

//// 完全二叉树的几个性质
// 1、已知父节点位置i，求子节点位置。左节点2i+1，右节点2i+2
// 2、已知子节点位置i，求父节点位置。(i-1) >> 1
// 3、
// n = n0 + n1 + n2;
//                          n2 + 1 = n0;
// 2n2 + n1 + 1 = n;

// 上滤
void siftUp(int array[], int index){

}


/**
 * 下滤
 * @param array
 * @param index
 * @param len
 */
void siftDown(int array[], int index, int len){
    while (1){
        loop_count++;
        int leftIndex = (index * 2) + 1;
        int rightIndex = leftIndex+1;
        if(leftIndex > len-1){// 当前节点已经是叶子节点了，不需要再下滤
            break;
        }

        // 判断需要交换的节点是左还是右
        int changIndex = leftIndex;
        if(rightIndex <= len-1 &&  cmp(array[rightIndex], array[leftIndex], &cmp_count) > 0){
            changIndex = rightIndex;
        }
        // printf("%d,%d,%d,%d\n", index, leftIndex, rightIndex, changIndex);
        // printf("%d\n", changIndex);


        // 判断是否需要交换
        if(cmp(array[changIndex], array[index], &cmp_count) <= 0){
            break;
        }

        swap(array, changIndex, index, &swap_count);

        // 继续判断
        index = changIndex;
    }
}

/**
 * 批量建堆
 * @param array
 * @param len
 */
void bulk_creat_heap(int array[], int len){
    // 自下而上的下滤
    for (int i=(len-2) >> 1; i>=0; i--){
        loop_count++;
        siftDown(array,i,len);
    }
}


/**
 * 堆排序
 * @param array
 * @param len
 */
void heap_sort(int array[], int len){
    long long start = get_current_timestamp();
    bulk_creat_heap(array, len);
    // print_array(array, len);
    for(int i = len-1; i>0; i--){
        loop_count++;
        swap(array, 0, i, &swap_count);
        // print_array(array, len);

        siftDown(array,0, i);
    }
    long long end = get_current_timestamp();
    printf("heap_sort time take = %lld(ms), swap count num = %d, cmp count num = %d, loop count num = %d\n", end-start, swap_count, cmp_count, loop_count);
    return;
}
