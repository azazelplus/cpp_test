//`Stack`和`Queue`是非常简单的数据结构，它们是`List`的变体。
//它们是`List`的弱化或者转换形式，因为你只需要在`List`的一端放置元素。
//对于`Stack`，你只能能够在一段压入和弹出元素。
//而对于`Queue`，你只能够在开头压入元素，并在末尾弹出（或者反过来）。
//我能够只通过C预处理器和两个头文件来实现这两个数据结构。
//我的头文件只有21行, 且实现了所有`Stack`和`Queue`的操作，
//我们直接用`list.h`, 借用我们在ex32写的双向链表结构来实现stack和queue结构.

#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef List Stack;

//直接把双向链表的函数和宏偷来用就行了. 为了模拟stack只能在链尾操作, 不偷shift和unshift这两个方法就行了...
#define Stack_create List_create
#define Stack_destroy List_destroy
#define Stack-clear List_clear
#define Stack_clear_destroy List_clear_destroy

#define Stack_push List_push
#define Stack_pop List_pop
#define Stack_peek List_last
#define Stack_count List_count
//把遍历宏也偷过来.
#define STACK_FOREACH(S,V) LIST_FOREACH(S, last, prev, V)



#endif



