//
// Created by 姚坤 on 2023/3/8.
//




int main(){
    //// 1、修饰局部变量：表示变量的值不能被改变了
    const int n = 5;    // 用const修饰变量时，一定要给变量初始化，否则之后就不能再进行赋值了。
    int const m = 5;    // 这两种写法是一样的

    const char *str = "hello world";    // 用于修饰常量静态字符串
    // str[4] = 'x';                    // 如果没有const的修饰，我们可能会在后面有意无意的写str[4]='x'这样的语句
    // 这样会导致对只读内存区域的赋值，然后程序会立刻异常终止。有了const，这个错误就能在程序被编译的时候就立即检查出来，这就是const的好处。
    // 让逻辑错误在编译期被发现。


    //// 2、常量指针与指针常量
    // 常量指针是指针指向的内容是常量，可以有一下两种定义方式。
    const int *n1;
    int const *m1;
    int i = 5;
    int j = 100;
    n1 = &i;
    // *n1 = 10;       // 常量指针说的是不能通过这个指针改变变量的值
    i = 6;             // 但是还是可以通过其他的引用来改变变量的值的
    n1 = &j;           // 常量指针指向的值不能改变，但是这并不是意味着指针本身不能改变，常量指针可以指向其他的地址


    // 指针常量是指指针本身是个常量，不能在指向其他的地址，写法如下
    int * const n2 = &i;
    // n2 = &j;         // 指针常量指向的地址不能改变
    *n2 = 50;           // 地址中保存的数值是可以改变的


    // 指向常量的常指针，是以上两种的结合
    const int* const p; // 指针指向的位置不能改变并且也不能通过这个指针改变变量的值，但是依然可以通过其他的普通指针改变变量的值。


    //// 3、修饰函数的参数，根据常量指针与指针常量，const修饰函数的参数也是分为三种情况
    // 3-1、防止修改指针指向的内容（常量指针）
    void StringCopy(char*strDestination,const char*strSource);

    // 3-2、防止修改指针指向的地址（指针常量）
    void swap ( int* const p1 , int* const p2 );

    // 3-3、以上两种的结合
    void swap2 ( const int* const p1);


    //// 4、修饰函数的返回值
    // 如果给以“指针传递”方式的函数返回值加 const 修饰，那么函数返回值（即指针）的内容不能被修改，该返回值只能被赋给加const 修饰的同类型指针。
    const char* GetString(void);
    // char*str = GetString();
    // const char*str = GetString();    // 正确用法


    //// 5、修饰全局变量 使用的方法与局部变量是相同的
    // 全局变量的作用域是整个文件，我们应该尽量避免使用全局变量，因为一旦有一个函数改变了全局变量的值，它也会影响到其他引用这个变量的函数，
    // 导致出了bug后很难发现，如果一定要用全局变量，我们应该尽量的使用const修饰符进行修饰，
    return 0;
}