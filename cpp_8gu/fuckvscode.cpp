#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    string str[2]={"abb", "ccaa"};

    vector<int> a={1,2,3,4,5};
    list<int> b={1,2,3,4,5};
    stack<int> c;
    c.push(1);
    c.push(2);
    //打印vector a:
    for(int i=0; i<a.size(); ++i){
        cout << a[i] << ' ';
    }
    cout << endl;

    return 0;
}   