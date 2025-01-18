`dbg.h` 是调试用的宏.
`test_my_debug.c`只是一个用来测试dbg.h宏的源文件.
`minunit.h`是用来单元测试的宏.

`list.c`和`list.h`是我写的链表结构.
`liblist.lib`是将`list.c`打包为静态库文件.

`list_test.c`是一个可以用来测试这个链表机构的源文件. 你可以同时编译list_test.c list.c来得到可执行文件, 也可以链接上liblist.lib来编译list_test.c.


`list.cpp`是尝试用cpp风格写list.c.好像还没写完先不管了.


