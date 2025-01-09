#include <iostream>
using namespace std;
//void Sum(int*& array, int n);

void Sum(int* array, int n){//不允许int*& array, 会报错
    int sum =0;
    for(int i=0;i<n;i++){
        sum+=*array;
        array++;
        cout<<array<<endl;
    }
    cout<<sum<<endl;
}

// void NotChangeValue(int a)
// {a=5;}


// void ChangeValue(int &a)
// {a=5;}

int main(int argc, char *argv[])
{
    int a[5]={1,2,3,4,5};
    cout<<a<<endl;
    cout<<a[0]<<endl;
    Sum(a,5);
    //a++;      //数组名是常量指针，不允许修改!
    cout<<&a<<endl;

    int*b=a;
    b++;
    cout<<b<<endl;
    cout<<*b<<endl;
    return 0;
}


