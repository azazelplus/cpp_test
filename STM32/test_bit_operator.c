
#include <stdio.h>



int main() {
    int a = 42;          // 定义一个整型变量
    int *p = &a;         // 指向变量 a 的指针

    printf("变量 a 的地址：%p\n", (void*)&a);  // 直接打印 a 的地址
    printf("指针 p 的值：%p\n", (void*)p);     // 打印指针 p 的值 (即 a 的地址)
    
    return 0;
}










