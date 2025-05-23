//链表由一个个节点(node)类组成.
//一个class node有两个必须部分: `储存的数据`和`指向下一个node的指针`.
//同时, 一般会给Node类一个static指针, 指向第一个对象.


//我感觉经典的链表结构很不方便在链表尾操作,需要遍历来移动到链表尾, 而双向链表我感觉没必要? 你说为啥我们同时有一个topnode和一个bottomnode呢?这样会不会方便很多? 有机会试一试...看起来很简单.




//这个链表类有丰富的方法, 有append, delete, find, modify, push, pop. 它完全可以当成一个stack, 一个pile, 一个queue, 或者其他数据类型.
//比如它可以看成stack: push(栈顶看为链表头部插入), pop(删除链表头节点), top(读取头节点值).
//也可以看成queue: push(栈顶看为链表头部插入), pop(删除链表尾节点), top(读取头节点值).




#include <iostream>
#include <iomanip>//用于输入输出流的格式化.
using namespace std;

//链表结点类
class Node{
public:
    //int number;     //节点的编号(我们这个例子里不打算加入节点的序号了. 传统链表不需要编号, 如果编号的话维护起来有点麻烦. 删除等操作需要改动后面对象的编号, 凭空多了大量写入操作.)
    int data;       //节点的数据(这个数据要有唯一性...比如学号)
    Node* pNext;    //指向下一个节点的指针
    Node(int d) : data(d), pNext(nullptr){}     //构造函数. 初始化pNext为空指针, 准备在addNode()函数中具体设置为当前链表末端.
};

//链表类
class LinkedList{   
private:
    Node* head;     //指向链表头部的指针
    int length;      //链表现在的长度

public:
    LinkedList(): head(nullptr), length(0){}   //构造函数, 初始化空链表. 即只有一个指向null的指针.
    ~LinkedList(){
        //同addNode(int data)函数, 也是用current指针遍历直到最后一个对象, 在循环中一个个删除node.
        Node* current=head;
        while(current!=nullptr){    //直到current指向空(指向最后一个对象并且再往前一步)为止
            Node* temp = current;   //temp保存上一个current的值
            current=current->pNext; 
            delete temp;            //释放当前Node的内存
        }

    }


    //增: 在链表末尾添加一个Node. 返回值为是否成功.
    void append(int data){
        Node* newNode = new Node(data);//分配堆内存创建了一个newNode, 作为链表的末端, 其pNext被初始化为nullptr是合理的.
        length++;               //链表长度记录+1

        if(head == nullptr){
            head = newNode;     //如果链表为空, 直接将新节点设为头节点.
        }else{
            //建立一个Node* current, 用这个指针遍历到链表的末尾(只有链表末尾的那个Node的pNext是nullptr.)
            Node* current = head;  
            while(current->pNext != nullptr){   //直到current指向的Node是链表结尾.
                current=current->pNext;         //如果current指针所指的对象的pNext不是nullptr, 说明这个对象不是链表最后一个对象.
            }
            //循环结束后, current是指向链表当前最后一个对象的指针. 我们要把这个对象的pNext从null指向我们创建的newNode, 完成append.
            current->pNext=newNode; 
        }
    }




    //删: 删除指定data值的Node. (如果有多个符合该data检索的Node, 则把它们全部删除.)
    void deleteVal(int val){
        //如果是空列表, 无法进行删除.
        if(!head){  
            cout<<"empty list. cant delete no more."<<endl;
            return;
        }

        //检查头节点的data值会不会符合要被删除:  (reminder: head是链表类的成员.)
        if(head->data==val){
            Node* temp = head;
            head = head->pNext;     //改变当前链表头指针.
            delete temp;
            cout<<"head (`"<< val <<"`) node deleted."<<endl;
            return;
        }


    //遍历(head之外的)链表.
        Node* current = head;
        while(current->pNext != nullptr){       //直到current指向最后一个Node
            if(current->pNext->data==val){     //如果发现current所指的对象的下一个对象是要删除的:
                Node* temp=current->pNext;      //留存一下指向下一个对象的指针;(供删除用)
                current->pNext=current->pNext->pNext;   //把current所指的对象的pNext往后接一位.
                delete temp;
                cout<<"a node `"<< val <<"` deleted."<<endl;
            }else
                current = current->pNext;   //move forward
        }
    }


    //查: 查找指定值的node, 如果找到了就返回其指针. (要求每个Node的data值要独一无二有区分性. 否则只返回第一个.)
    Node* findValue(int val){
        Node* current=head;
        while(current!=nullptr){        //直到current指向链表外.
            if(current->data == val){
                return current;    //如果current当前指向的Node符合要求, 返回这个current指针.
            }else{
                current = current->pNext;   //move forward
            }
        }
        cout<<"node `"<< val <<"` not found."<<endl;
        return nullptr;
    }



    //改: 修改指定节点的值. (要求每个Node的data值要独一无二有区分性. 否则只返修改一个.)
    void modifyValue(int oldval, int newval){
        if(findValue(newval)){  //防止新值已经存在(保证data的唯一性)
            cout<<"failed to modify. "<< newval <<" already exists."<<endl;
        }

        //先查找oldval所在节点.
        Node* Node_to_be_modified = findValue(oldval);
        //如果没找到, 函数结束
        if(!Node_to_be_modified){
            cout<<"failed to modify."<<endl;
            return;
        }

        //查找成功后修改值.
        Node_to_be_modified->data = newval;
        cout<<"modification from `"<< oldval<<"` to `"<< newval <<"` successful."<<endl;
    }


    //打: 打印链表中的所有节点数据.
    void printList(){
        Node* current = head;   //老生常谈, 用来遍历的指针.
        while(current){     //current从head跑到链表外.
            cout<<current->data<<" ";
            current = current->pNext;
        }
        cout<<endl;
    }







    //push: 在链表头部插入一个节点.
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
            return 0; //栈空, 无法出栈.
        }else {
            cout << head->data << endl;
            Node* temp = head; //保存当前节点
            head = head->pNext; //头指针指向下一个节点
            delete temp;
        }
    }
    

};


int main(){
    
    LinkedList list;

    //add Nodes
    list.append(123745);
    list.append(110);
    list.append(9999);
    list.append(666);
    list.append(72452);
    list.append(1333);
    list.append(1);

    //print
    list.printList();

    //modify
    list.modifyValue(1, 0);

    //print
    list.printList();

    //delete
    list.deleteVal(110);

    //print
    list.printList();

    //find
    if(list.findValue(666))
        cout<<"node found. the addr is "<<list.findValue(666)<<endl;

    return 0;
}

