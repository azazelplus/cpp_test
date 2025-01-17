//自动化测试经常用于例如Python和Ruby的其它语言，但是很少用于C。
//一部分原因是自动化加载和测试C的代码片段具有较高的难度。
//这一章中，我们会创建一个非常小型的测试“框架”，并且使用你的框架目录构建测试用例的示例。
//我接下来打算使用，并且你会包含进框架目录的框架，叫做“minunit”，
//它以Jera Design所编写的一小段代码作为开始，之后我扩展了它，就像这样：


#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include "dbg.h"
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message) if (!(test)) { log_err(message); return message; }
#define mu_run_test(test) debug("\n-----%s", " " #test); \
    message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    argc = 1; \
    debug("----- RUNNING: %s", argv[0]);\
        printf("----\nRUNNING: %s\n", argv[0]);\
        char *result = name();\
        if (result != 0) {\
            printf("FAILED: %s\n", result);\
        }\
        else {\
            printf("ALL TESTS PASSED\n");\
        }\
    printf("Tests run: %d\n", tests_run);\
        exit(result != 0);\
}


int tests_run;

#endif