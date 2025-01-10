#include <iostream>

using namespace std;




//Multiple Inheritance(多重继承)

class ClassA{
    public:
    void fn1()
    {
        cout<<"fn1 from ClassA."<<endl;
    }
};

class ClassB{
    public:
    void fn2()
    {
        cout<<"fn2 from ClassB."<<endl;
    }
};


class DerivedFromAandB : public ClassA, public ClassB {
    public:
    void fn3() {
        cout << "Function C from Derived Class" << endl;
    }
};

int main() {
    DerivedFromAandB d;
    d.fn1();  // 从 ClassA 继承
    d.fn2();  // 从 ClassB 继承
    d.fn3();  // Derived 类的成员函数
    return 0;
}



//diamond problem(菱形继承问题): 
//发生下述继承关系, 而B,C分别重写了基类A的成员函数fn1(), D在继承B和C, 这时D的对象调用fn1()时, 编译器不知道应该调用B还是C的fn1(), 这就是菱形继承问题.
//      A
//    /   \
//   B     C
//    \   /
//      D

class A
{
    public:
    void fn1()
    {
        cout<<"fn1 from ClassA."<<endl;
    }
};

class B : public A
{
    public:
    void fn1()  //override(重写), 即在子类中重新定义了基类的成员函数. 这样做会隐藏基类的同名成员函数. B不再继承A的fn1()了.
    {
        cout<<"fn1 from ClassB."<<endl;
    }

};

class C : public A
{
    public:
    void fn1()  //override(重写), 即在子类中重新定义了基类的成员函数. 这样做会隐藏基类的同名成员函数. B不再继承A的fn1()了.
    {
        cout<<"fn1 from ClassC."<<endl;
    }

};

class D : public B, public C
{
};

int main() {
    D d;
    //d.fn1();  //不能确定是从 B 继承的还是从 C 继承的fn1(). `error:"D::fn1" 不明确C/C++(266)`
}




//virtual inheritance(虚拟继承) 可以解决`不明确`的问题.
//不明确的情况1: 多重继承下, 两个基类有同名成员函数.
//不明确的情况2: 使用父类指针指向子类对象(在内存中, 子类的前半部分内容就是父类的结构所以允许这样做), 用指针`->`访问成员函数时, 会调用父类的成员函数, 而不是子类overriding的成员函数(如果有的话).
//例如:
class Father{
    public: void fn(){cout<<"Father's fn()"<<endl;}
};
class Son : public Father{
    public: void fn(){cout<<"Son's fn()"<<endl;}//override fn()
};
//测试结果为:
// int main(){
//     Father *pSon = new Son();
//     pSon->fn();      //输出: Father's fn()
//     return 0;
// }

class Father2{
    public: virtual void fn(){cout<<"Father's fn()"<<endl;};//加上virtual关键字, fn()为`虚函数`, 告诉编译器, 它已经准备好被子类重写了. 在将来的继承中, 如果子类重写了这个函数, 那么调用这个同名函数出现不确定时, 将调用子类重写的函数.
};
class Son2 : public Father2{
    public: void fn(){cout<<"Son's fn()"<<endl;}//override fn()
};
//测试结果为:
// int main(){
//     Father2 *pSon = new Son2();
//     pSon->fn();      //输出: Son's fn()
//     return 0;
// }


















