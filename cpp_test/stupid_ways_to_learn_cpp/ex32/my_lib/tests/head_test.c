//测试一些宏/预编译特性的新手教程.

#include <stdio.h>


//变参宏的用法.
#define   MAX(a,b) (a>b?a:b)

//`...`接受可变数量的参数. `##__VA_ARGS__ `用来引入宏传入的实际参数.
#define log1(...) printf(__VA_ARGS__);
//下面的例子里, 给log1传入了三个参数:
//"this is a test of __VA_ARGS__: %s, %d\n"
//str
//num
//__VA_ARGS__此时被替换为`"this is a test of __VA_ARGS__: %s, %d\n", str, num`.
int main(){
    char* str = "test";
    int num=10086;
    log1("this is a test of __VA_ARGS__: %s, %d\n", str, num)
    return 0;
}




//宏的常见高阶用法: foreach循环.
//val是从数组中拿出来的a[i].  第一个for循环用i遍历数组每个元素.   第二个嵌套的for目的是拿val值, 其实依靠cnt只执行一次, 目的只是接收用户在foreach后的具体每个循环要执行的多个语句. 这样看来, 语法上第二个for循环是一个语句, 从而第一个for循环不需要带`{}`. 
//为啥不能只用一个for循环? 因为要接收`val`为类似`int a`的替换内容, val没法进行多次赋值了, 需要...总之只是个语法糖...你替换写一下就知道了...
//btw: backslash`\`后面不能带空格哦. 不过这只是个warning.
#define foreach(val, arr)\
for (size_t i = 0, cnt = 0, size=sizeof(arr)/sizeof(arr[0]); i<size; ++i, cnt=0)\
    for (val = arr[i]; cnt<1; ++cnt)



//一些宏中的特殊符号
//`#`把任意类型的字面量转换为字符串(不能转换变量哦, 毕竟是预编译阶段.)
#define ToString(val) #val  
//`##`是标记粘合符. 把`参数/函数名`连接在一起得到一个新的标识符(变量/函数等的名字, 就是一个标识符). 感觉没啥用啊.
#define Connect(x) x##y
//`#@`参数转字符. 和`#`参数转字符很类似.



//btw `字面量(literal)` 即程序中固定的常量, 如`1`,`'h'`,`"hello"`
//C中''和""的区别: `a`是一个字符字面量, 即const char, "a"是一个字符串字面量, 即const char[]或者说const *char, 它有两个字节, 第一个是`a`, 第二个是`\0`. 
int main(){

    //foreach宏用例.
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    foreach(int a, arr)
    {
        printf("%d", a);
    }

    printf("%s\n", ToString(12345));    //把字面量转换为字符串


    int xy=5; printf("%d\n", Connect(x));    //##标记粘合符, 把某个变量黏上一个y字母

    return 0;
}





