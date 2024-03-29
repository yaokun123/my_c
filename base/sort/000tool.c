//
// Created by 姚坤 on 2023/3/16.
//

//// https://www.cs.usfca.edu/~galles/visualization/Algorithms.html
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
int * random_array(int len){
    int size = sizeof(int) * len;
    int * address = (int *)malloc(size);
    for(int i=0;i<len;i++){
        address[i] = rand();
    }
    return address;
}
void print_array(int array[], int len){
    printf("[");
    for(int i=0; i<len; i++){
        if(i == len-1){
            printf("%d", array[i]);
        }else{
            printf("%d,", array[i]);
        }
    }
    printf("]\n");
}

void swap(int array[], int i1, int i2, int *swap_count){
    if (i1 == i2) return;
    int tmp = array[i1];
    array[i1] = array[i2];
    array[i2] = tmp;
    (*swap_count)++;
}

int cmp(int num_1, int num_2, int *cmp_count){
    (*cmp_count)++;
    return num_1-num_2;
}

long long get_current_timestamp(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long tmp = tv.tv_sec;
    tmp = 1000*tmp;
    tmp = tmp + tv.tv_usec;
    return tmp;
}

int * copy_array(int array[], int len){
    if (len == 0) return NULL;
    int size = sizeof(int) * len;

    void * address = malloc(size);
    memcpy(address, array, size);
    return (int *)address;
}