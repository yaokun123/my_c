//
// Created by 姚坤 on 2023/3/16.
//

#ifndef MY_C_000TOOL_H
#define MY_C_000TOOL_H

void print_array(int array[], int a);
void swap(int array[], int i1, int i2, int *swap_count);
int cmp(int num_1, int num_2, int * cmp_count);
long long get_current_timestamp();
void * copy_array(int array[], int len);

#endif //MY_C_000TOOL_H
