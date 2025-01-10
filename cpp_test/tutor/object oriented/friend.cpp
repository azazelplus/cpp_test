


#include <iostream>
#include <cstdlib>
using namespace std;

class Matrix;   //前置声明. 用于友元函数声明.(为啥要前置声明? 因为友元函数声明中用到了Matrix类, 但是Matrix类在友元函数声明之前还没有定义, 所以要先声明.)


/*******************************/
class Vector{
    int* v;     //指向一个整数数组. 默认为private成员
    int size;   //数组的大小. 

    public:
    Vector(int);    //构造函数的声明.cpp中, 声明函数时参数名可以省略, 只需指定类型.
    ~Vector(){delete [] v;}
    Vector(Vector &);
    int GetSize(){return size;}
    void Display();         //输出数组元素
    int& Elem(int i);       //`以引用方式`返回数组中的第i个元素. 用于修改赋值. 
    friend Vector Multiply_friendly(Matrix& m, Vector& v);  //(先往下看, 第二遍再看这行)友元函数声明. 用于矩阵和向量相乘.
};
Vector::Vector(int sz){ //构造函数定义.
    if(size<=0){
        cout<<"Invalid size."<<endl;
        exit(1);
    }
    this->size = sz;    //this是当前对象的指针. 注意::是用来访问成员函数和静态成员变量的, 这里不能替换为`Vector::size;`. 这很好理解, 因为每个对象都拥有一个普通成员变量,Vector::size是不唯一的.
    v = new int[sz];    //从堆中分配一个大小为sz的整数数组.
}

Vector::Vector(Vector &obj){ //一个构造函数重载. 通过引用接受一个Vector对象为参数, 它实际上是`拷贝构造函数`. 使用`引用传递`为了避免对象的拷贝构造, 浪费不必要的时间和内存资源. 其实最好加上const关键字, 防止修改传入的对象. 
    size = obj.size;    //复制对象参数的size
    v = new int[size];  //分配一个新的数组并复制元素.
    memcpy(
        v,                  //目标数组
        obj.v,              //源数组
        size*sizeof(int)    //复制的字节数
    );
}


int& Vector::Elem(int i){
    if(i<0||i>=size){
        cerr<<"Vector index out of range.\n";
        exit(1);
    }
    return v[i];
}

void Vector::Display(){     
    for(int i=0;i<size;i++)
        cout<<v[i]<<" ";
    cout<<endl;
}
/*******************************/


/*******************************/
class Matrix{
    int* m;
    int sizerow;
    int sizecol;

    public:
    Matrix(int,int);    //构造函数之一, 初始化一个i行j列的矩阵.
    Matrix(Matrix &);   //构造函数之二, 拷贝构造函数.
    ~Matrix(){delete[]m;}   //析构函数. 它应当delete所有动态分配内存的成员变量. `delete[] m;` 释放 m 指向的动态分配的内存. sizerow 和 sizecol是类中的普通成员变量,不动态分配的内存, 不需要delete.
    int GetSizeRow(){return sizerow;}
    int GetSizeCol(){return sizecol;}
    void Display();     //输出矩阵元素
    int& Elem(int,int); //返回矩阵中的第i行第j列元素. 以引用方式返回, 用于修改赋值.
    friend Vector Multiply_friendly(Matrix& m, Vector& v);  //(先往下看, 第二遍再看这行)友元函数声明. 用于矩阵和向量相乘.
};

Matrix::Matrix(int i, int j){   //构造函数. 初始化一个i行j列的矩阵.
    if(i<=0||j<=0){
        cerr<<"Invalid size.\n";
        exit(1);
    }
    sizerow = i;
    sizecol = j;
    m = new int[i*j];   //分配一个大小为i*j的整数数组的内存. 但是内容未定义.
}


Matrix::Matrix(Matrix &obj){
    sizerow = obj.sizerow;  //复制对象参数的size
    sizecol = obj.sizecol;  
    m = new int[sizerow*sizecol];  //分配一个新的数组并复制元素.
    memcpy(
        m,                  //目标数组
        obj.m,              //源数组
        sizerow*sizecol*sizeof(int)    //复制的字节数
    );
}

int& Matrix::Elem(int i, int j){
    if(i<0||j<0||i>=sizerow||j>=sizecol){
        cerr<<"Matrix index out of range.\n";
        exit(1);
    }
    return m[i*sizecol+j];
}

/*******************************/


//
Vector Multiply(Matrix& m, Vector& v){  //矩阵和向量相乘m*v. 输出一个结果向量.
    if(m.GetSizeCol()!=v.GetSize()){
        cerr<<"Matrix and vector size mismatch! \n";
        exit(1);
    }
    Vector r(m.GetSizeRow());    //创建一个存放结果的空向量.

    //矩阵和向量相乘.
    for(int i=0;i<m.GetSizeRow();i++){
        r.Elem(i) = 0;  //初始化结果向量的第i个元素为0.
        for(int j=0;j<m.GetSizeCol();j++){
            r.Elem(i) += m.Elem(i,j)*v.Elem(j);  //矩阵和向量相乘的结果.
        }
    }
    return r;
}

//反思这个矩阵和向量相乘的实现:
//Matrix 中的 m 和 Vector 中的 v 是保护数据。由于 Multiply() 不是 Matrix 和 Vector 类的成员, 
//不能直接操纵 m[i][j] 和 v[i]，只能通过 m.Elem(i,j) 和 v.Elem(i) 来访问矩阵和向量的元素。
//Elem() 函数定义中要对下标进行合法性检查，所以，Multiply() 函数要频繁地调用函数和进行下标检查。
//做一次上例中的小乘法，矩阵 (4,3) 乘以向量 (3) 得到向量 (4)，
//其 Elem() 和 Size() 成员函数要调用 3 + 1 + 4 * (1 + (1 + 2) * 3) = 44 次，显然效率不高。
//于是希望乘法不要调用 Elem() 函数，能直接访问两个类的保护数据成员。


//解决方法: 使用友元函数. 对于某个一般函数(不是某个类的成员函数), 在一些类的public里声明它为友元, 这样这个函数就可以访问这些类的保护数据成员了.


Vector Multiply_friendly(Matrix& m, Vector& v){
    if(m.sizecol!=v.size){
        cerr<<"Matrix and vector size mismatch! \n";
        exit(1);
    }
    Vector r(m.sizerow);    //创建一个存放结果的空向量.
    for(int i=0;i<m.sizerow;i++){
        r.Elem(i) = 0;  //初始化结果向量的第i个元素为0.
        for(int j=0;j<m.sizecol;j++){
            r.Elem(i) += m.Elem(i,j)*v.Elem(j);  //矩阵和向量相乘的结果.
        }
    }
    return r;    

}
