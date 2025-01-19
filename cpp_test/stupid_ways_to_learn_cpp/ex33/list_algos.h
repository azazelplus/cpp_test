//我将想你介绍涉及到排序的两个算法，你可以用它们操作链表。
//我首先要警告你，如果你打算对数据排序，不要使用链表，它们对于排序十分麻烦，并且有更好的数据结构作为替代。

#ifndef List_algo_h
#define List_algo_h

#include "list.h"

//定义一个函数指针类型别名`List_compare`, 返回值为`int *`, 参数列表为`const void* a, const void* b`
typedef int (*List_compare)(const void* a, const void* b);

//bubble sort函数标签
int List_bubble_sort(List *list, List_compare cmp);

//merge sort函数标签
List *List_merge_sort(List *lst, List_compare cmp);


#endif





















