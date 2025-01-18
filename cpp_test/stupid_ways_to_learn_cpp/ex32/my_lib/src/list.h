//这是我写的一个双向链表的头文件, 定义了链表及其相关的操作接口。
//具体来说, 定义了:
//
//使用方法:#include "list.h"


//常见的防止重复包含的手段, 定义一个空宏名.
#ifndef my_lib_lish_h
#define my_lib_lish_h

#include <stdlib.h>


struct ListNode;    //声明ListNode结构体


//定义ListNode和List类. 用typedef的方式只是为了以后少写个struct关键字而已. 用cpp的class更好.
typedef struct ListNode{
    struct ListNode* next;
    struct ListNode* prev;
    void *value;

} ListNode;

typedef struct List{
    int count;
    ListNode* first;    //指向列表第一个node
    ListNode* last;     //指向列表最后一个node
} List;


//声明一些List方法.(c没法用成员函数, 只好这样了)
List* List_create();
void List_destroy(List* List);
void List_clear(List* List);
void List_clear_destroy(List* List);


//宏定义. 宏可以简单理解为`文本替换`, 把`List_count(A)`替换为`(A)->count`. 在宏定义中使用(), 目的是在以后出现含有额外参数的用法中, 保证运算优先级. 
//比如以后要用`List_count(list+5)`, 括号内的list+5本意是指针的加减运算, 但是如果不加括号宏定义`#define List_count(A) A->count`, 内容会被翻译为`list + 5->count`. `->`优先级大于`+`导致编译器尝试执行`5->count`, 显然是错误的.
//总之因为是文本替换, 编译器是不会管你具体写了什麽`#define (*&^*%) (*&^*&)`的.
#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)


//又是声明一些List方法.
void List_push(List* list, void* value);
void* List_pop(List* list);
void List_unshift(List* list, void* value);
void* List_shift(List* list);
void* List_remove(List* list, ListNode *node);


//这是个遍历链表的宏, 简化了一下遍历操作. 使用`LIST_FOREACH(L, S, M, V)`来代替下面的代码:
// ListNode *_node = NULL;
// ListNode *V = NULL;
// for(V = _node = L->S; _node != NULL; V = _node = _node->M)
//btw, C的链式赋值表达式特性: `a=b=10`等价于先进行`b=10`, 然后表达式`b=10`会返回`10`给a, 也就是接下来进行`a=(b=10)`, 或者说`a=10`. 
//总之, `a=b=10;`等价于`a=(b=10);`等价于`a=10;b=10;` 然而, 我不推荐你像作者一样用太多这种类似三元表达式的混蛋东西.
#define LIST_FOREACH(list, first, next, current) \
    ListNode *_node = NULL;\
    ListNode *current = NULL;\
    for(current = _node = (list)->first; _node != NULL; current = _node = _node->next)
    //这个for循环的初始化部分: current = _node = (list)->first;  把current和_node两个指针都指向list的第一个node. 事实上, current用于存储当前节点, _node用于在循环中移动.
    //for的循环条件部分: _node != NULL;     即当_node跳出链表时停下. 注意cpp中应该用`nullptr`关键字表示空指针.
    //for的更新部分: current = _node = next;    把current和_node两个指针都指向list的下一个node


#endif