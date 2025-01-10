// 写一个类，声明一个数据成员和一个静态数据成员。让构造函数初始化数据成员，静态数据成员加1，析构函数减1。

// 基于(1)，写程序创建三个对象，展示各自的数据成员和静态数据成员，然后析构各个对象并展示对静态数据成员的影响。

// 修改(2)使`静态成员函数`可以访问`静态数据成员`，同时将`静态数据成员`设为`保护`类型。

#include <iostream>
using namespace std;

class A{

    int data;

    protected:
    static int count;

    public:
    A(int d):data(d){count++;}
    ~A(){count--;}
    void ShowData(){cout<<"data: "<<data<<endl;}
    static void ShowCount(){cout<<"count: "<<count<<endl;}
};

int A::count = 0;

int main(){
    A a1(1);
    A a2(2);
    A a3(3);

    a1.ShowCount();
    a1.ShowData();
    a2.ShowData();
    a3.ShowData();

    return 0;
}