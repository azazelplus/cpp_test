//cpp的智能指针功能. 位于<memory>头文件中.
#include <iostream>
#include <memory>   //引入智能指针类
using namespace std;    //这会让所有的标准库成员都可以不带 std::
using std::unique_ptr;  //这个不需要因为上面已经包含了
using std::make_unique; //这个不需要因为上面已经包含了
//顺带一提,`using namespace std;`和`using std::unique_ptr;`的区别:
//`using namespace std;` 将`std`命名空间下的所有符号(例如，`cout`, `cin`, `vector`, `unique_ptr`, 等)引入当前作用域。在小型程序或示例代码中，`using namespace std;` 可以减少 `std::` 的重复书写，使代码更简洁。但在较大的项目中(尤其是在头文件中)使用它通常不推荐，可能引入不必要的命名冲突。
//`using std::unique_ptr;` 只将`std`命名空间下的`std::unique_ptr`换成`unique_ptr`而已.

//




//memory leak: 动态内存没有及时释放.
//dangling pointer(wild pointer): 未初始化的指针, 或者一个指向动态内存的指针, 结果动态内存被free了. 造成segment fault.




//smart pointer可以避免上述错误.

//smart pointer分为三种. 是一个对象模板. 它封装了一个指向另一个对象的指针.

//unique_ptr:
// template<
//     class T;
//     class Deleter = default_delete<T>
// >class imoqie_ptr;
 


//shared_ptr

//weak_ptr






class MyClass{
public:
    MyClass(){
        cout<<"this is MyClass constructor\n";
    }
    ~MyClass(){
        //do something...
    }

};



//我们以一个简单的rectangle类为例讲解unique_ptr的用法
class Rectangle{
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h){}   //constructor
    ~Rectangle(){}              //类没有动态分配内存，析构函数实际上没有执行清理操作的必要。
    void display() const{       //此处(其实可省略)`const`关键字的作用是声明成员函数为`常量成员函数`. `常量成员函数`承诺`不修改类的成员变量`,且`不调用非常量成员函数`.
        cout << "Rectangle [width=" << width << ", height=" << height << "]\n";
    }
};

int main(){
    //顺带一提: 在 C++ 中，大括号 {} 用于定义一个作用域。每一个大括号内的代码属于同一个作用域，里面声明的变量、对象或指针等都会在大括号的范围内生效，并且在大括号结束时销毁。using命令也只在当前大括号(如果在最外面就是全局的)作用域起作用.
    
    //1.    `std::make_unique<>()`函数模板: 创建unique_ptr和初始化. std::make_unique<类名>(构造函数参数)  返回一个`unique_ptr<类名>`对象.
    unique_ptr<Rectangle> pRect1 = make_unique<Rectangle>(10.0, 5.0);

    //2.    `std::move()`函数: 转移所有权
    unique_ptr<Rectangle> pRect2 = move(pRect1);    //转移所有权, 现在pRect2从pRect1手里夺走了刚生成的那个Rectangle类对象的指针. 现在pRect1为空了.


    //3.    使用unique_ptr管理堆内存.()
    {
        //用`{}`创建一个小作用域.
        unique_ptr<Rectangle> pRect3 = make_unique<Rectangle>(3.0,4.0); //创建一个unique_ptr和初始化.
        pRect3->display();//可以正常显示  
    }
    //脱离作用域, 现在pRect3已经自动销毁, 连带析构了它包含的那个Rectangle对象. 显然预编译阶段就提示pRect3是不存在的了.
    try{
        pRect3->display();  //error: 未定义标识符 "pRect3"C/C++(20)
    }catch(const std::exception& err){
        cout<<"error! "<< err.what()<<endl; //输出错误   
    }

    //4.    使用get()方法获取裸指针. 这样做后, 原先的unique_ptr仍会继续管理它肚子里的对象(指针). 这意味着, 原unique_ptr离开作用域并析构对象后, 这个裸指针就会变成`野指针`!!
    unique_ptr<Rectangle> pRect4 = make_unique<Rectangle>(1.0,2.0); //创建一个unique_ptr和初始化.
    Rectangle* raw_pRect4 = pRect4.get();   //raw_pRect4现在是对象的一个普通指针了.
    raw_pRect4->display();

    //5.    使用release()方法释放指针所有权, 返回裸指针. 和get()方法的区别是release()夺取了目标unique_ptr管理的对象, 现在它变成nullptr.
    unique_ptr<Rectangle> pRect5 = make_unique<Rectangle>(55.0,5.0); //创建一个unique_ptr和初始化.
    Rectangle* raw_pRect5 = pRect5.release();   //raw_pRect5现在是对象的一个普通指针了, 而pRect5==nullptr.    

    //6.    使用reset()方法重置unique_ptr.

    //7.    使用swap()方法交换两个unique_ptr.
}





