//使用单元测试(unit testing)而不是写一个main函数.
// 在不同的编程语言中，有不同的单元测试框架来帮助你写和执行单元测试。例如：

// -   **C语言**：`minunit`，`CUnit`
// -   **C++**：`Google Test`（gtest），`Catch2`
// -   **Python**：`unittest`，`pytest`
// -   **Java**：`JUnit`

//我们使用轻量级测试框架minunit测试. 它通过宏来简化测试的编写和运行. 
#include "minunit.h"
#include "list.h"
#include <assert.h>


//定义测试数据
static List* list = NULL;
char* test1="test1 data";
char* test2="test2 data";
char* test3="test3 data";


//编写测试函数.
//每个测试函数的结构非常相似，基本上是创建链表并执行一些操作，然后使用 mu_assert 来验证操作的正确性。如果断言失败，程序会给出错误信息。


char* test_create(){
    list = List_create();
    mu_assert(list!=NULL, "Fail to creat list.")
    return NULL;
}



























