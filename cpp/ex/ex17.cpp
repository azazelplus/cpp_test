#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

#define MAX_DATA 512
#define MAX_ROWS 100



class Address{
public:
	int id;
	bool set;
	string name;
	string email;

	Address(int id = 0): id(id), set(false), name(""), email("")
	{}

	void print() const	//cpp中, `const`关键字可以用在成员函数后, 表示这个函数不允许修改对象的任何成员变量. (即一个只读函数).
	{
		cout << id << "\n" << name << "\n" << email << endl; 
	}
}


//cpp中使用动态数组类vector来代替数组.
class Database{
public:
	vector<Address> rows;	//cpp中的动态数组类vector声明: vector<type> name;
	
	Database()
	{
		rows.reserve(MAX_ROWS);	//vector类的reserve方法, 用于给未来要添加的元素预分配内存. 是在堆上动态分配内存. 其作用可以用new Address[IMAX_ROWS]代替.
					
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			rows.emplace_back(i);//给动态数组初始化MAX_ROWS个元素.
		}


	void create(){
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			rows[i] = Address(i);//此处Address是构造函数.
		}
	}
	
	void set(int id) 	



	}
