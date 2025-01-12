//cpp风格实现双向链表.

#include <iostream>
#include <stdexcept>

class ListNode{
public:
    ListNode* next;
    ListNode* prev;
    void* value;

    ListNode() : next(nullptr), prev(nullptr), value(nullptr){}
};

class List{
public:
    ListNode* first;
    ListNode* last;
    int count;

    List() : first(nullptr), last(nullptr), count(0){}

    ~List(){
        
    }


};


// Clear the list (free only values)
void clear() {
    ListNode* current = first;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;  // 释放节点内存
        current = next;
    }
    first = last = nullptr;  // 重置链表指针
    count = 0;  // 清空节点计数
}











