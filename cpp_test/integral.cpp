//this is a function that calculates the integral of a func given.
// the goal is to exercise the use of `function pointers`!
#include <iostream>
#include <cmath>//this header file offers `sin` function. function prototype: `double sin(double x);`. reminder that `sin` without `()` is a function pointer.
using namespace std;

double integral(
    double (*func)(double),     //need a function pointer. a unary function, in mathamatical terms.
    double a, double b, double dx
){
    double sum = 0;
    for(double i=a; i<b; i+=dx){
        sum += func(i)*dx;
    }
    return sum;
}


double fn1(double x){return 1;}                     //constant function f(x)=1
double fn2(double x){double y = 2*x;return y;}       //linear function f(x)=2x

int main(int argc, char *argv[])
{
    double a = 0;
    double b = 1;
    double pi = 3.1415926;
    double dx = 0.001;

    cout<<
    integral(sin, a, pi, dx)<<"\n"<<    //result is 2
    integral(fn1, a, b, dx)<<"\n"<<     //result is 1
    integral(fn2, a, b, dx)<<"\n"<<     //result is 0.999
    endl;
    return 0;
}
