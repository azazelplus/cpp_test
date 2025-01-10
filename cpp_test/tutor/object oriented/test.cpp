


#include <iostream>
#include <cstdlib>
using namespace std;


class A; class B;

class A{
    int a;

    public:
    friend A friendly(B& b, A& a);  
};


class B{
    int b;

    public:
    friend A friendly(B& b, A& a);  
};



A friendly(B& b, A& a){
    a.a=5;    //不允许访问
    b.b=5;
}
