#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Hello, World!\n");
    int a = 1;

    switch (fork()) {
        case -1:
            perror("fork error!");
            break;
        case 0:
            a = 2;
            printf("child process");
            break;
        default:
            a = 3;
            printf("parent process");
            break;
    }
    return 0;
}
