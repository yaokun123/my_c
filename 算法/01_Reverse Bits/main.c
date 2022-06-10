//// 翻转无符号整型
#include <stdio.h>
#include <math.h>
#include "print_binary.h"

//// 这个算法是 redis的dictScan 方法使用的
/* Function to reverse bits. Algorithm from:
 * http://graphics.stanford.edu/~seander/bithacks.html#ReverseParallel */
static unsigned long rev(unsigned long v) {
    unsigned long s = 8 * sizeof(v); // bit size; must be power of 2
    unsigned long mask = ~0;
    while ((s >>= 1) > 0) {
        mask ^= (mask << s);
        v = ((v >> s) & mask) | ((v << s) & ~mask);
    }
    return v;
}


static unsigned long rev_2(unsigned long v){
    unsigned long res = 0;
    int power = (8 * sizeof(v)) -1;
    //int power = 63;
    while (v){
        res += (v & 1) << power;
        v >>= 1;
        power--;
    }
    return res;
}


void test_dictScan_cursor(int tablesize){ // 8 16 32
    unsigned long v;
    unsigned long m0;

    v = 0;
    m0 = tablesize-1;

    printbits(v, (int)log2(tablesize));
    printf("  -->  ");

    do{
        v |= ~m0;
        v = rev_2(v);
        v++;
        v = rev_2(v);


        printbits(v,(int)log2(tablesize));
        printf(" --> ");
    }while (v != 0);

    printf("\b\b\b\b\b     \n");
}

int main(){
    unsigned a = 25;
    unsigned b = 99;

    printf("%lu\n",rev(a));
    printf("%lu\n",rev(b));

    printf("%lu\n",rev_2(a));
    printf("%lu\n",rev_2(b));

    print_binary(a,0);
    print_binary(a,1);
    print_binary(b,0);
    print_binary(b,1);

    test_dictScan_cursor(8);
    test_dictScan_cursor(16);
    test_dictScan_cursor(32);
}






