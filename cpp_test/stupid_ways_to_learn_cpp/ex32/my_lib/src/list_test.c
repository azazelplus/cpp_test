//使用单元测试(unit testing)而不是写一个main函数.
// 在不同的编程语言中，有不同的单元测试框架来帮助你写和执行单元测试。例如：

// -   **C语言**：`minunit`，`CUnit`
// -   **C++**：`Google Test`（gtest），`Catch2`
// -   **Python**：`unittest`，`pytest`
// -   **Java**：`JUnit`

//我们使用轻量级测试框架minunit测试. 它通过宏来简化测试的编写和运行.  看看怎么用就行了有时间再看它的实现之类的吧~
#include "minunit.h"    //这里包含了我们的dbg.h
#include "list.h"
#include <assert.h>
//最终编译时,我们需要链接list_test.c和list.c(后者是我们自己写的库, 所以需要手动链接库文件), 即`gcc list_test.c list.c -o list_test`



//定义测试数据
static List* list = NULL;
char* test1="test1 data";
char* test2="test2 data";
char* test3="test3 data";


//编写测试函数.
//每个测试函数的结构非常相似，基本上是创建链表并执行一些操作，然后使用 mu_assert 来验证操作的正确性。
//返回值为字符串, 如果断言失败，程序会返回错误信息。


char* test_create(){
    list = List_create();
    mu_assert(list!=NULL, "Fail to creat list.")
    return NULL;
}


char *test_destroy()
{
    List_clear_destroy(list);
    return NULL;
}


char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}



char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}


char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}


//执行所有测试.
// -   `mu_suite_start()` 用来初始化测试套件，表示一系列测试的开始。
// -   `mu_run_test(test_name)` 用来运行每个单元测试函数，依次执行前面定义的所有测试。
// -   如果有任何测试失败，`mu_run_test` 会打印错误信息。
char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}


//运行测试: RUN_TESTS()
RUN_TESTS(all_tests);



//运行成功 结果:
// PS F:\aza\code_git\cpp_test\stupid_ways_to_learn_cpp\ex32\my_lib\src> .\list_test.exe
// DEBUG list_test.c:133: ----- RUNNING: F:\aza\code_git\cpp_test\stupid_ways_to_learn_cpp\ex32\my_lib\src\list_test.exe
// ----
// RUNNING: F:\aza\code_git\cpp_test\stupid_ways_to_learn_cpp\ex32\my_lib\src\list_test.exe
// DEBUG list_test.c:121:
// ----- test_create
// DEBUG list_test.c:122:
// ----- test_push_pop
// DEBUG list_test.c:123:
// ----- test_unshift
// DEBUG list_test.c:124:
// ----- test_remove
// DEBUG list_test.c:125:
// ----- test_shift
// DEBUG list_test.c:126:
// ----- test_destroy
// ALL TESTS PASSED
// Tests run: 6






//我们可以把整个链表结构打包成一个静态/动态库文件.

// | 扩展名  | 系统         | 类型       | 功能                               | 记忆关键词         |
// |---------|--------------|------------|----------------------------------|--------------------|
// | `.a`    | Linux/Unix   | 静态库     | 编译时打包进可执行文件             | Archive（博物馆）  |
// | `.lib`  | Windows      | 静态库/导入库 | 提供静态链接或动态库接口信息     | Library（库）      |
// | `.so`   | Linux/Unix   | 动态库     | 运行时动态加载                    | Shared Object（共享对象） |
// | `.dll`  | Windows      | 动态库     | 运行时动态加载                    | Dynamic Link Library（动态链接库） |
//Windows 下的 .a 文件也可以正常使用.

//打包静态库:
//先用-c选项进行只编译不链接, 得到`目标`文件, 即list.o, 
//接下来，你需要使用 ar 工具将目标文件打包成静态库.
// ar 是 Unix 系统中用于创建、修改和提取静态库的工具。rcs 是 ar 的常用选项，意思是：
// r：插入或替换库中的文件。
// c：创建库文件（如果库文件不存在）。
// s：创建索引，这样库文件可以被链接器更有效地使用。
// 执行后，liblist.a 就是你创建的静态库。
//PS F:\aza\code_git\cpp_test\stupid_ways_to_learn_cpp\ex32\my_lib\src> gcc -c list.c -o list.o
//PS F:\aza\code_git\cpp_test\stupid_ways_to_learn_cpp\ex32\my_lib\src> ar rcs liblist.lib list.o

//链接静态库:
//在编译你的某个需要用到list结构的文件, 比如你写的这个list_test.c时, 这样编译:
//gcc list_test.c -L. -l list -o list_test
// -   `-L.`：告诉编译器在当前目录查找库文件（即 `liblist.lib`）。
// -   `-l list`：告诉编译器链接名为 `liblist.lib` 的库文件。注意这里的 `list` 是去掉了 `lib` 前缀.
// -   `-o list_test`：指定输出的可执行文件名为 `list_test`。
// 于是得到了可以运行的`list_test.exe`.
//事实上, 把list.c打包成库后通过`gcc [需要用到的文件] -L. -l list -o [程序名]` 和`gcc [需要用到的文件] list.c -o [程序名]`结果是一样的.
//打包的好处: 打包后实际上gcc只需要编译[需要用到的文件]并且链接上`liblist.lib`, 而不需要重新编译list.c. 需要用到的库文件源代码不可见, 是保密的. 再者可以打包很多.c为一个.lib.



//打包动态库:
//1. 编译源代码为`共享对象文件`
//gcc -fPIC -c list.c -o list.o
//-fPIC 选项告诉编译器生成位置无关代码（Position Independent Code），这是动态库所必需的。

//2.创建动态库文件.dll
// gcc -shared -o liblist.dll list.o
// -shared 选项告诉编译器创建共享库（动态库）。liblist.dll 就是你创建的动态库文件。

//3.使用. 同样地, 链接动态库编译你的文件即可.
//gcc list_test.c -L. -l list -o list_test

//4.程序运行: 运行程序时, 你需要告诉OS在哪里找到动态库. 设置环境变量.
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
// ./list_test
