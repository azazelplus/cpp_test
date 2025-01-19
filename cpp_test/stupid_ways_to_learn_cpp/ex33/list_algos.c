
#include "list_algos.h"
#include "dbg.h"

//inline关键字是C/C++编译器的指示符. 它建议编译器将该函数的调用`内联展开`, 即`在调用该函数的地方直接插入函数的代码，而不是进行常规的函数调用。`
// #### **优点：**

// -   **减少函数调用开销**：避免了函数调用的开销，尤其是在小函数（如简单的计算或操作）中，性能提升明显。
// -   **代码优化**：有时，内联函数能让编译器进行更好的优化，比如常量折叠、循环展开等。

// #### **缺点：**

// -   **增加代码体积**：由于每个调用 `inline` 函数的地方都会插入函数体的代码，因此可能导致二进制文件的代码体积膨胀，尤其是当该函数被多次调用时。
// -   **不总是生效**：`inline` 是编译器的提示，编译器并不一定会按照开发者的意图将函数内联展开。编译器可能会根据函数的复杂度、调用频率等因素决定是否内联。


//这个函数不改变链表结构, 仅仅交换两个节点储存的值.
inline void ListNode_swap(ListNode *a, ListNode *b){
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}



//我们的老朋友bubble sort.
int List_bubble_sort_old(List *list, List_compare cmp){
//bubble sort的第一轮循环即元素个数counter, 第二个循环是具体的遍历元素交换.
    for(ListNode *round=list->first;
        round!=NULL;
        round=round->next){
            
        for(ListNode *current=list->first;
            current!=NULL;
            current=current->next){
                if(cmp(current->value, current->next->value))
                    ListNode_swap(current, current->next);
        }
    }
    return 0;
}



//给无聊的两层循环来点优化吧. 
//1.可以加一个检验:如果在上一轮遍历中, 没有触发swap, 说明已经排好了, 不一定非要进行count次循环!
//2.对内层这个`交换的遍历循环`, 事实上外层循环每过一次, 内层循环都可以提前停下(因为k次外层循环可以保证队列的至少最后k个位置是已经排好的)
//3.加一个用户传入list长度为0的捣乱情况的退出机制.
int List_bubble_sort(List *list, List_compare cmp){

    if(list->count==0)  //1.
        return 0;

    int round_count=0;  
   
   
    for(ListNode *round=list->first;
        round_count!=list->count;
        round=round->next, round_count++){
            
        int sorted=0;   //sorted记录每次内层循环有没有发生swap, 如果没发生, 说明提前排好, 可以结束了.

        int i=0;    //i用来对内层遍历计数.
        for(ListNode *current=list->first;
            i!=list->count-round_count;    //2.
            current=current->next,i++){
                if(cmp(current->value, current->next->value))
                    {
                        ListNode_swap(current, current->next); 
                        sorted=1;
                    }
        }
        if(sorted==0)     //3.
            break;
    }
    return 0;
}



//合成`left`和`right`两个已经排序(头节点序最小)的链表, 保证合并后的的链表有序/                                                                                     
inline List *List_merge(List *left, List *right, List_compare cmp){
    List *result_list = List_create();
    void *val = NULL;   //用来临时保存从 left 或 right 链表中移除的值

    while(List_count(left)>0 || List_count(right)>0){ //一直弹出直到两个列表都变成空的
        if(List_count(left)>0 && List_count(right)>0){      //如果两个链表都非空, 则各取其链首比较.
            if(cmp(List_first(left), List_first(right))<=0)     //left<right, 先shift出left头节点作为最小的
                val=List_shift(left);
             else
                val=List_shift(right);
            List_push(result_list, val);
        }else if(List_count(left)>0){                      //right链表已经为空, 就一直shift left即可.
            val = List_shift(left);
            List_push(result_list, val);
        }else if(List_count(right)>0){                      //同理, 当left链表已经为空
            val = List_shift(right);
            List_push(result_list, right);
        }         
    }
    return result_list;
}



List *List_merge_sort(List *list, List_compare cmp){
    if(list_count(list) <= 1)      //无需排序
        return list;
    
    //把当前列表一分为二.
    List* left = List_create();
    List* right = List_create();
    int middle = List_count(list)/2;
    //depart
    LIST_FOREACH(list, first, next, cur){   
        if(middle>0)
            List_push(left, cur->value);
        else
            List_push(right, cur->value);
        middle--;
    }

    //递归
    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    if (sort_left != left) List_destroy(left);
    if (sort_right != right) List_destroy(right);

    return List_merge(sort_left, sort_right, cmp);
}






