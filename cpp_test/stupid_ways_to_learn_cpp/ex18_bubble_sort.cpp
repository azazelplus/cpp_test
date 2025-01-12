//这是ex18_bubble_sort.c的cpp版本.

#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>//提供标准异常类的定义. 例如std::invalid_argument
#include <functional>//提供了一些模板类和函数对象, 用于函数对象的包装和函数对象的逻辑运算. 例如std::greater<T>和std::less<T>等.
using namespace std;


//错误处理函数. C++强烈推荐使用`异常处理`来处理错误。比传统的错误代码返回和打印错误消息的方式更为强大和灵活。
//C++ 的异常机制通常分为 抛出(throw)和 捕获(catch)两个部分：
//1. 抛出异常. 使用throw语句, 程序会立即`抛出一个异常`。异常可以是任意类型的数据，但通常是一个错误类(cpp基本库提供)对象。然后程序会停止执行, 从抛出点跳转到最近的try-catch块, 寻找能`捕捉`这个异常的代码.
//2. 捕获异常. 当抛出异常时，程序会在当前函数中查找与异常匹配的catch语句。如果找到匹配的catch语句，异常会被捕获，然后执行catch语句中的代码。
//我们以一个int类型的对象作为异常抛出为例.
// try {
//     int a = 42;
//     throw a;  // 抛出 int 类型的异常
// } catch (int err) {  // 捕获 int 类型的异常
//     std::cout << "Caught exception: " << e << std::endl;  // 输出：Caught exception: 42
// }


//throw 后跟一个对象. `std::runtime_error`是标准库提供的异常类, 继承自`std::exception`类, 表示`运行时错误`. 类似的还有`std::logic_error`类, 表示`逻辑错误`.
//这些错误类的构造函数一般需要一个参数(通常是用户提供一个描述错误信息字符串)来创建一个异常对象。传入的message会被输出.


//这里用string而不是char*是因为string更加安全, 有更多的功能.
//传递参数时前面加一个const意味着不允许改变传入的值, &表示`按引用传递`. 如果没有const, `引用传递`会导致参数被修改. `const`搭配`引用传递&`, 既能保证传入的参数不被修改, 又能提高效率.
void die(const string& message)
{
    //这个语句是先用给定字符串`message`构造了一个runtime_error对象, 然后把这个对象throw出去。
    throw runtime_error(message);//抛出异常. invalid_argument是标准异常类, 用于处理无效参数错误.
}

{


}





