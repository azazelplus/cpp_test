//template是cpp用于编写通用代码的机制. 
//语法: template <typename MyType> 其中`MyType`是用户自己起的, `template` `typename`都是关键字. 后面跟一个函数/类的定义.
//template <typename MyType>只会使紧随其后的第一个函数/类的内容成为模板. 要声明多个函数/类模板, 需要多次使用template <typename MyType>.

#include <iostream>

using namespace std;


//function template 函数模板
template <typename T>
void mySwap(T& a, T& b){
    T temp =a;
    a=b;
    b=temp;
}
//这个函数模板可以交换两个相同类型的变量的值.





//class template 类模板
template <typename T>
class MyClass{
    public:
    T a;
    MyClass(T a) : a(a) {}//这是构造函数的`初始化列表`写法. 语法就是`MyClass(value_of_arg1, value_of_arg2,...) : arg1(value_of_arg1), arg2(value_of_arg2)...{}` 
    void display(){
        cout<<a<<endl;
    }
};
//这个模板类拥有一个成员变量, 可以被初始化为任意类型的值; 然后有一个display()成员函数, 试图用cout输出这个成员变量的值(如果cout能够识别这个类型的值的话).












