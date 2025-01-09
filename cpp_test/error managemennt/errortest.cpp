//cpp处理异常的步骤:
//1.定义异常range. 将可能产生错误的代码放在try块中。
//2.定义异常handling.将异常处理的语句放在catch块中. 异常被传递过来时, 会被catch块捕获。
//3.throw异常. 检测是否发生异常, 若有, throw语句抛出.

//下面的例子设置了防备文件打不开的异常处理.

#include <iostream>
#include <fstream>//提供了文件操作相关的类和函数. 包括ofstream, ifstream, fstream等.
#include <cstdlib>//提供了一些通用的函数, 如exit()函数.
using namespace std;

//ofstream函数用于写文件. 传入文件名和打开模式. 如果文件不存在, 则创建一个新文件. 如果文件存在, 则清空文件内容. 原型: ofstream(const char* filename, ios::openmode mode = ios::out);
//ifstream函数用于读文件. 传入文件名和打开模式. 如果文件不存在, 则会出错. 函数原型: ifstream(const char* filename, ios::openmode mode = ios::in);
//fstream函数用于读写文件. 传入文件名和打开模式. 如果文件不存在, 则会出错. 函数原型: fstream(const char* filename, ios::openmode mode = ios::in | ios::out);
int main(int argc, char **argv){
    ifstream source(argv[1]);

}