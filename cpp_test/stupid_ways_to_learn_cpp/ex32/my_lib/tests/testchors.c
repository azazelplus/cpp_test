
#include <stdio.h>


void test() {
    int x = 5;
    if (x < 10) {
        goto myLabel;  // 跳转到 myLabel 标签
    }

myLabel:
    printf("This will be printed.\n");
    
    printf("This won't be printed.\n");


}


int main(){
    test();
    return 0;
}


