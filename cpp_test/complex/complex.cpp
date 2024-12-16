#include <iostream>
#include <math.h>
using namespace std;

class complex{
    public:
        complex(double r = 0, double i = 0)
            : re(r), im(r)  //这一行叫做initialization list初值列. 即": var1(input1), var2(input2)", 这效果和你在下方的函数体{}内写re=r; im=i;是一样的.
            {}
        double real () const {return re;};
        double imag () const {return im;};
        complex& operator += (const complex);   //这一句是啥意思?
    private:
        double re, im;

        friend complex& __doapl (complex*, const complex&); //do assement plus  
};






int main(){
    int a = 5;


    cout << a << endl;
    return 0;
}