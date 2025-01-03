#include <iostream>
using namespace std;
//void Sum(int*& array, int n);

void Sum(int*& array, int n){//不允许int*& array, 会报错
    int sum =0;
    for(int i=0;i<n;i++){
        sum+=*array;
        array++;
        cout<<array<<endl;
    }
    cout<<sum<<endl;
}

void NotChangeValue(int a)
{a=5;}


void ChangeValue(int &a)
{a=5;}

int main(int argc, char *argv[])
{

    int a[10]={1,2,3,4,5,6,7,8,9,0};
    cout<<a<<endl;
    //cout<<&a[0]<<endl;
    //cout<<&a<<endl;
    Sum(a,10);
    cout<<&a<<endl;

    // int b=3;
    // NotChangeValue(b);
    // cout<<b<<endl;

    // int c=3;
    // ChangeValue(c);
    // cout<<c<<endl;


    return 0;
}


