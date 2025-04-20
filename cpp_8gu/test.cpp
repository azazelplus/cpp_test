#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <stack>
#include <vector>

using namespace std;


//先实现一个链表, 然后提供push(栈顶看为链表头部插入), pop(删除链表头节点), top(读取头节点值), 于是这样就变成一个stack了!

class Node{
    public:
    int data;
    Node* pNext;

    Node(int d): data(d), pNext(nullptr){} //构造函数. 
};


class Stack{
    private:
    Node* head;
    int length;
    public:
    Stack(): head(nullptr), length(0){} //构造函数, 初始化空链表. 
    ~Stack(){
        Node* current = head;
        while(current!=nullptr){
            Node* temp = current;
            current = current->pNext;
            delete temp;
        }
    }

    //入栈: 在链表头加一个节点.
    void push(int data){
        Node* newNode = new Node(data);
        newNode->pNext = head; //新节点的pNext指向当前链表头
        head = newNode; //头指针指向新节点
        length++;
    }

    //出栈: 删除链表头节点.
    int pop(){

        if(!head){
            cout << "error" << endl;
            return -1; //栈空, 无法出栈.
        }else {
            cout << head->data << endl;
            Node* temp = head; //保存当前节点
            head = head->pNext; //头指针指向下一个节点
            delete temp;
        }
        return 0; 
    }

    //读取栈顶元素: 返回链表头节点的值.
    void top(){
        if(!head){
            cout<<"error"<< endl;
        }else{
            cout << head->data<< endl;
        }
    }       
};



// 判断弹出序列是否合法
bool validateStackSequences(int pushV[], int popV[], int n) {
    stack<int> st;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        st.push(pushV[i]);
        while (!st.empty() && st.top() == popV[j]) {
            st.pop();
            ++j;
        }
    }
    return j == n;
}


bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
    int n = pushV.size();

    int j =0;//pop序列下标

    stack<int> s;//创建一个空栈


    for(int i=0;i<n;i++){

        //bool test0=s.top();
        bool test01=popV[j];
        //bool test1=(s.top() != popV[j]);
        bool test2=(s.empty());

        if(s.empty() || s.top() != popV[j]){
            s.push(pushV[i]);   //当前不能出栈, 继续循环
        }else{
            while( !(s.top() != popV[j] || s.empty()) ){ //pop到不能pop为止
                s.pop();//出栈
                j++;
            }
        }
    }

    //现在应该是空stack.
    if(s.empty()){
        return true; //合法序列
    }else{
        return false; //不合法序列
    }
}




//一边压，一边检查栈顶是不是你要的弹出值； 能弹就弹，不能就接着压； 最后栈空了，就是合法序列 ！
int main() {
    vector<int> a={1,2,3,4,5};
    vector<int> b={4,5,3,2,1};
    bool ans = IsPopOrder(a,b);
    cout << ans << endl; //输出1表示合法序列, 0表示不合法序列.
    return 0;
}
    
