//我现在会向你展示你目前所见过的，最强大且卓越的代码的全部内容。

//学习这个dbg宏的同时, 这也是个W编写宏的个人教程.

//#define会生成一个`宏名`.  宏名在代码中用来代替一些内容.
//而类似下面的三段式, 其实只定义了一个宏名(没有后面的替换), 主要作用是利用检查宏来防止重复包含而已.
    // #ifndef __dbg_h__       // 如果 __dbg_h__ 宏还未定义
    // #define __dbg_h__       // 定义 __dbg_h__ 宏
    // // 头文件的内容
    // #endif


//C编译器提供`标准预定义宏`可以直接使用. (ANSI标准)
//__LINE__      当前编译的代码行号
//__FILE__      当前编译文件的源文件名(比如ex18.c)
//__DATE__      当前源程序(比如ex18.exe)创建的日期
//__TIME__      当前源程序创建的小时时间
//__FUNCTION__  当前正在被访问的函数名
//simple example:
    // int main(){
    //     printf("%s\n", __DATE__);
    //     printf("%s\n", __TIME__);
    //     printf("%s\n", __FILE__);
    //     printf("%d\n", __LINE__);
    //     printf("%s\n", __FUNCTION__);
    //     return 0;
    // }
//the output is:
// Jan 16 2025
// 15:32:46
// test.c
// 8
// main

//带参宏:   在宏名的最后使用`()`来实现带参数的宏. 一个简单的例子:
//btw: 双下划线`__`命名一般是保留给编译器和标准库实现的, 为了避免潜在冲突, 用户自己的宏可以用单下划线, 或者变参宏的话直接用函数名的形式命名.
    // #define   MAX(a,b) (a>b?a:b)
    // int main(){
    //     int a=5;    int b=10;
    //     printf("%d", MAX(a,b));
    //     return 0;
    // }
// the output is:
// 10



#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h> //strerror()


//打印调试信息的宏.
#ifdef NDEBUG   //(如果用户#define NDEBUG,即not debug, 则宏 `debug` 会变成空的宏，禁用调试输出。
#define debug(M, ...)// 空的宏.
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
//debug宏接受M(手动描述的错误message)参数和之后的任意个补充参数. 后面可选参数是供使用者实现M中可能的格式化字符串参数的.
//printf()将输出打印到标准输出(终端), 而f(file)printf()函数: printf的拓展版. 将输出打印到指定文件流. 语法: fprintf(FILE* stream, "xxx", arg1, arg2...)
//此处, fprintf的第一个参数是stderr, 即向stderr中打印内容. 第二个参数是一个格式化字符串"DEBUG %s:%d: " M "\n", 其中M将被第一个宏参数替换. 第3,4个参数是两个常见预定义宏, 分别表示编译时的源文件名和行数. 
//`##`是C中的预处理运算符`token-pasting operator`
//`stderr`是一个FILE* 类型的全局变量, 指向C标准库的`错误输出流`, 和stdout一样只不过用来输入错误信息.

//举个例子, 如果输入debug("This is a test message with value %d", 42);
//宏会展开为:fprintf(stderr, "DEBUG main.c:15: This is a test message with value %d\n", 42);
#endif




//返回最近的错误信息的宏. 其实就是`strerror(errno);`, 但是多了一个errno==0的情况.
//strerror是一个全局函数, 声明在`string.h`. 它接受一个错误码(一般是errno值), 返回一个字符串, 描述错误码对应的错误信息. 可以看成对errno的翻译
//errno是我们的老朋友全局变量, 一个存储最后一个错误发生时的错误的int变量. 常见值有ENOMEN内存不足, EINVAL无效参数, EIO输入输出错误, EPERM操作不允许.
//单独对待errno==0的情况是因为, 如果直接给strerror(0),会输出"success!" 但是既然我们调用了函数肯定现在有问题只是error没捕捉到而已
#define clean_errno() (errno==0 ? "None" : strerror(errno))



//日志宏.提供三种日志级别，分别记录错误、警告和信息。
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: error: %s) "M" \n ", __FILE__, __LINE__,  clean_errno(), ##__VA_ARGS__)
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: error: %s) "M" \n ", __FILE__, __LINE__,  clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) "M" \n ", __FILE__, __LINE__, ##__VA_ARGS__)



//错误处理宏. 检查条件A是否成立, 不成立则打印错误日志并清空errno(防止误报), 然后跳转到errno标签, 执行清理和退出.

#define check(A, M, ...) if(!(A)) {log_err(M, ##__VA_ARGS__);  errno=0;  goto error;}


//sentinel哨兵. 无条件触发错误，用于代码逻辑的“死角”或“不可到达”部分。
#define sentinel(M, ...) {log_err(M, ##__VA_ARGS__); errno=0; goto error;}

//检查内存分配是否成功. 如果传入的指针A为NULL(cpp为nullptr), 打印"Out of memory."
#define check_mem(A) check((A), "Out of memory.")


//类似 check,打印的是调试信息而非错误日志。适用于仅用于调试的检查。
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }




#endif