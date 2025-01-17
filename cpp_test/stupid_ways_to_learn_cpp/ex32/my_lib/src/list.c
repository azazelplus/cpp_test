
#include "list.h"
#include "dbg.h"




//把头文件中仅声明的函数定义出来.
//List的构造函数. 简单返回一个List结构体, 初始化prev和next为0, 即nullptr.
//malloc(memory allocate)只分配堆内存. calloc(contiguous allocate)分配堆内存并初始化为0.
//btw, C中允许并鼓励void*隐式转换为其他指针, malloc和calloc可以直接用. cpp不允许void*隐式转换. 如果在cpp中用(其实直接用new不香吗)malloc和calloc需要显示转换哦.
List *List_create(){
    return calloc(1,sizeof(List));//可以看成cpp中的构造函数
}


//free list structure memory. 释放链表结构内存.
void List_destory(List* list){
    ListNode* current=list->first;
    ListNode* next=NULL;

    while(current!=NULL){   //遍历链表逐一释放节点
        next=current->next; //next记录current的下一个节点.
        free(current);  //current指针所指的ListNode被free.
        current=next;   //current移动到下一个节点
    }
    //最后释放List本身
    free(list);
}


//free listnode value memory.   释放所有节点存储的值(那些值也是动态分配的内存.)
void List_clear(List* list){
    ListNode* current=list->first;

    //for each node in list:
    while(current!=NULL){
        free(current->value);
        current=current->next;
    }
}


//free list.    结合上述两个函数, 同时释放链表结构和其节点储存的数据的内存.
void List_clear_destory(List* list){
    List_clear(list);
    List_destory(list);
}


//在链表list尾部插入一个存储void* value数据的新节点.
void List_push(List* list, void* value){
    //创建node并存数据
    ListNode* newnode = calloc(1,sizeof(ListNode));
    newnode->value=value;

    //连接这个node到list
    if(list->first==NULL){   //空列表时.
        list->first=newnode;   //此时列表的第一个和最后一个节点都是newnode
        list->last=newnode;
    }else{      //非空列表时: 要改变三个指针指向完成连接.可以画个图更清晰.
        list->last->next = newnode;    //当前最后一个节点(list->last)的next指向: 从NULL改为newnode
        newnode->prev = list->last;    //newnode的prev指向: 从NULL改为旧的最后一个节点(list->last)
        list->last = newnode;          //list的last指向从旧的最后一个节点到newnode
    }
    list->count++;
}


//返回链表尾部的那个节点储存的void* value, 同时删除尾部节点.
//btw: C没有引用特性, 如果是cpp可以写为ListNode* List_pop(const List& list), 这传递一个list结构体的引用(但是不能修改).
void* List_pop(List* list){   //为啥这里返回类型用void*, 不是还得隐式转换为ListNode*嘛. cpp不支持这样. 不懂为何要这样写...
    ListNode* last_node = list->last; 
    if(last_node!= NULL){
        return List_remove(list, last_node);
    }else   //last==NULL, 已经是空链表了, 就直接弹出一个NULL.
        return NULL;
}


//在链表头部插入一个新节点. 和list_push类似.
void List_unshift(List* list, void* value){
    ListNode* newnode = calloc(1, sizeof(ListNode));
    check_mem(newnode);

    newnode->value = value;
    
    if(list->first == NULL){    //空链表
        list->first = newnode;
        list->last = newnode;
    }else{      //非空链表
        newnode->next = list->first;
        list->first->prev = newnode;
        list->first = newnode;
    }
    list->count++;
error:
    return;
}


//从链表list头部弹出一个节点. 和List_pop类似.
void* List_shift(List* list){
    ListNode* first_node = list->first;
    if(first_node!=NULL){
        return List_remove(list, list->first);
    }else   //当链表已经空了时只能shift出来一个NULL了
        return NULL;
}


//从list中移除指定node, 并返回该node储存的值(void* result). 注意. 这并不会删掉储存的值的内存, 储存的值还是存在的!
void* List_remove(List* list, ListNode* node){
    void* result = NULL;    //初始化为NULL, 这样如果中间赋值失败, 就返回一个NULL.

    check(list->first, "List is empty!");   //需要dbg.h宏才能用哦. 如果检查到list是空链表, 会输出错误然后跳转到下面的error标签, return一个NULL.
    check(node, "node cant be NULL!")       //需要dbg.h宏才能用哦. 如果检查到要移除的node指针为NULL, 则失败.
    //删除节点环节. 分类讨论: 删除list->first, list->last, 和其他中间的node

    if(node==list->first && node==list->last){   //如果list只有一个node, 并且就要删除这个node时.
        list->first=NULL;
        list->last=NULL;
    }else if(node==list->first){     //如果list长度>1, 要删除头节点时.
        list->first = list->first->next;
        check(list->first != NULL, "illegal list! somehow got a first that is NULL. check your list.")//在已经确定list长度＞1的同时, 如果此时list->first->next是NULL, 说明这个list有问题...
        list->first->prev=NULL;
    }else if(node==list->last){     //如果list长度>1, 要删除尾节点时.
        list->last = list->last->prev;
        check(list->last != NULL, "illegal list! somehow got a last that is NULL. check your list.")//same.
        list->last->next = NULL;
    }else{       //删除中间节点
        ListNode* after = node->next;
        ListNode* before = node->prev;
        after->prev = before;
        before->next = after;
    }   

    list->count--;          //更新长度
    result=node->value;     //分类讨论完最后才给result赋值, 是因为一开始就 result=node->value; 的话, 如果上面的check环节有问题, 就会发生非法访问错误.
    free(node);

error:              //btw, 标签只是供goto跳转的, 即使没有出错, 没有触发跳转, 正常从上面执行下来也会执行return语句的. 而不是说一个标签下的语句只有跳转才会执行.
    return result;
}




