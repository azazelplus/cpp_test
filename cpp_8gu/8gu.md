





# 1. 输入输出

* cin >> x 遇到空格、换行符（\n）、制表符（\t）都会停下来.
* 读取一行完整的输入:`getline(cin, x)`. 只在`\n`处才会停下来. (在<string>头文件)
* ASCII中, char数字转换为int数字: 减掉一个`0`即可.
  ```cpp
  char ch = '2'; int x = ch - '0';  // x 现在就是 2 了！
  ```

* 移除字符串中的所有空格:
*   ```cpp
    #include <algorithm>
    // 移除所有空格
    input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    ```


## 1.1 `cout>>x`和`cin<<x`实际上是istream&类型!

👉 `cin >> a >> b` 其实是一个表达式！

在 C++ 里，`cin >> a` 返回的是一个 **`istream&` 类型**（也就是 `cin` 自己本身的引用），所以你可以链式写法：`cin >> a >> b`。

并且！这个输入表达式的结果（最终的 `cin`）是可以用于判断的，**会被转换成一个布尔值（bool）**，规则是：

-   如果输入成功（比如读到了数字），`cin` 就是“真”；
    
-   如果输入失败（比如用户输入了非数字，或者到了文件尾 EOF），`cin` 就是“假”。

举个例子:
```cpp
int main() {
    int a, b;
    while (cin >> a >> b) {
        cout << a + b << endl;
    }
}
```
假设你从控制台输入了这样几行：

`1 2 3 4 hello world 5 6`

那么程序的行为是：

-   第一次 `cin >> a >> b`：读到 1 和 2 ✅，输出 3
    
-   第二次 `cin >> a >> b`：读到 3 和 4 ✅，输出 7
    
-   第三次 `cin >> a >> b`：尝试读 `hello` 转换为 int ❌，**失败了，`cin` 状态变坏，退出 while**
    
-   第四次（其实不会执行了）不会再读！

借此可以对一些题目偷懒!比如:
给定 
t
t 组测试数据。
每组数据有两个整数 
a
a 和 
b
b ，请你求出 
a
+
b
a+b 的值。
时间限制：C/C++ 3秒，其他语言6秒
空间限制：C/C++ 256M，其他语言512M
输入描述：
第一行有一个整数 t\ (\ 1 \leq t \leq 10^5\ ) 。
每行有两个整数 a\ (\ 1 \leq a \leq 10^9\ ) 和 b\ (\ 1 \leq b \leq 10^9\ ) 。
输出描述：
输出 t 行，每行一个整数，代表 a+b 的值。
示例1
输入例子：
3
1 2
114 514
2024 727
输出例子：
3
628
2751
可以不管t:
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    int t;
    cin>>t;
    while (cin >> a >> b) { // 注意 while 处理多个 case
        cout << a + b << endl;
    }
}
```















## 1.2 二维动态数组练习

```cpp
//二维动态数组练习.
#include <iostream>
using namespace std;
int main(){
    int n, m;
    long long int sum=0;
    cin >> n >> m;
    long long int **arr = new long long int*[n];//arr是指向int指针的指针.
    for(int a=0;a<n;a++){
        arr[a]=new long long int[m];//arr[a]是将arr进行了(在动态分配内存后允许的范围内)指针移位运算, 运算后结果仍然是一个指向int指针的指针.
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> arr[i][j];
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            sum += arr[i][j];
        }
    }
    cout << sum << endl;

    for(int k=0;k<n;k++){
        delete[] arr[k];
    }
    delete[] arr;
    //cpp中的`delete`和`delete[]`是操作符, 而不是函数.
    //`delete a`释放单个对象a; `delete[] a`释放数组a. 即把a看成指针,不停尝试移动a并析构, 直到无法移动为止.
}
```















## 1.3 字符串练习

### 1.3.1反转字符串:

```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);    cin.tie(nullptr);
    //默认情况下，C++ 的 IO（cin/cout）为了和 C 的 IO（scanf/printf）保持同步，
    //也就是每次你用 cin 读取时，系统会先自动把 cout 刷新（flush），确保之前的输出都显示出来，再去读输入。
    //把同步关掉后，cin/cout 就不再和 C 的 IO 联动了，去掉了这些额外开销，读写速度会快很多。
    //当然，关了同步后，就不要和 scanf/printf 混着用了，否则可能顺序错乱喵～
    int n;
    cin >> n;
    string s;
    cin >>s;
    reverse(s.begin(), s.end());
    cout<<s<<endl;   
}

#if 0
//如果要求自己实现呢?
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    char* s = new char[n+1];
    for(int i = 0; i < n; i++) {
        scanf(" %c", &s[i]);
    }
    s[n] = '\0'; // 添加字符串结束符

    // 反转字符串
    for(int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - i - 1];
        s[n - i - 1] = temp;
    }
    printf("%s\n",s);
    delete[]s;
}
#endif
```

### 1.3.2 处理多个字符串, 并翻转

单组_二维字符数组
给定一个 n 行 m 列的二维字符数组 a，
请你对行和列都倒置，然后输出之。

输入描述：
第一行有两个整数 n 和 m 。
随后 n 行，每行有 m 个字符，仅包含小写英文字符 。
输出描述：
输出一个二维字符数组。
示例1
输入例子：
3 4
abcd
efgh
ijkl
输出例子：
lkji
hgfe
dcba
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);    cin.tie(nullptr);

    int t; cin>>t;
    while(t--){
        int n; cin>>n;

    }
    
}
```



### 1.3.3 去掉字符串的空格

我们要用到下面几个简便的cpp方法:
- **s.push_back(somechar)**
    所属：std::string（以及 std::vector）的成员函数。

    作用：在字符串 末尾 添加一个字符 c，相当于 s += c;。

    如果超出容量：会在后台重新分配更大的内存，然后再添加。

    用法：
    ```cpp
    string s = "cat";
    s.push_back('!'); // 现在 s == "cat!"
    ```
  - **getline(cin, s)**
    全名：std::getline，在头文件 <string>（或 <iostream>）里声明。

    功能：从输入流（第一个参数）读取一整行字符到字符串（第二个参数 s），直到遇到换行符 \n（但不把 \n 存入 s），并丢弃那个 \n。

    用法举例：
    ```cpp
    string line;
    getline(cin, line);
    // 现在 line 里是刚才输入直到回车前的所有字符
    ```

-   **cin.ignore()**
    所属：cin 是 std::istream 类的一个实例，ignore 是它的成员函数。

    作用：丢弃（忽略）输入流中的 一个字符（默认）或者你指定数量的字符，直到遇到指定的分隔符为止。

    常见用法：
    ```cpp
    cin.ignore();          // 忽略下一个字符（通常是换行符）
    cin.ignore(n, '\n');   // 忽略接下来 n 个字符，或直到遇到 '\n' 为止
    ```
    为什么要用：在 cin >> x; 之后，流里残留一个换行 \n，如果马上用 getline，就会读到那个换行产生一个空行，用 ignore() 把它丢掉.
    
- **s.reserve(n)**
    所属：std::string 的成员函数。

    作用：预先分配（reserve）至少 n 字符的容量（capacity），让后续对 s 的扩容操作更高效，减少内存重新分配次数。

    注意：reserve 不改变当前 s.size()，只改变 s.capacity()；也不会初始化字符。

    用法：
    ```cpp
    string s;
    s.reserve(100);  // 保证接下来 s 最多可容纳 100 个字符而不再触发重新分配
    ```


```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cin.ignore();                // 吃掉 n 后面的换行符
        string s;
        getline(cin, s);             // 读整行，含空格

        // 去掉所有空格
        string tmp;
        tmp.reserve(s.size());//优化速度.

        //c:s的意思是遍历s中的每一个字符!
        for (char c : s) {
            if (c != ' ') tmp.push_back(c);
        }

        // 倒置并输出
        reverse(tmp.begin(), tmp.end());
        cout << tmp << '\n';
    }

    return 0;
}
```


## 1.4 数字格式

### 1.4.1 保留小数位数
单组_保留小数位数
给定一个小数 n ，请你保留 3 位小数后输出。
如果原来的小数位数少于 3 ，需要补充 0 。
如果原来的小数位数多于 3 ，需要四舍五入到 3 位。

输入描述：
第一行有一个小数 n。
输出描述：
输出一个小数，保留 3 位。

示例1

输入例子：
1.23
输出例子：
1.230

示例2

输入例子：
114.514
输出例子：
114.514

```cpp
//使用<iomanip>(io manipulate, 输入输出控制器)提供的丰富功能可以轻松实现.
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    double n; cin>>n;
    cout<<fixed<<setprecision(3)<<n<<endl;
    //fixed     用小数点后固定位数来输出
    //setprecision(x)   保留x位小数,自动四舍五入

    //当然也可以使用printf格式控制字符串:
    printf("%.3f\n",n);//注意这样的printf是存在四舍五入的!

    //如果不想四舍五入呢?
    cout <<fixed<<setprecision(3)//fixed表示固定保留你设置的位数而不使用科学计数法. setprecision(3)表示保留三位小数, 如果有多位则四舍五入
    << floor(n*1000)//先*1000让n的小数点右移三位, 然后剩下的小数点是我们不需要的, 用floor向下取整割掉.
    /10000
    <<endl;
}
```

### 1.4.2 补充前导0
单组_补充前导零
给定一个正整数 n ，请你保留 9 个数位，然后输出。
如果数位少于 9 个，那么需要补充前导零。

输入描述：
第一行有一个整数 n\ (\ 1 \leq n \lt 10^9\ ) 。
输出描述：
输出一个数字，保留 9 个数位。

示例1
输入例子：
123
输出例子：
000000123

示例2
输入例子：
123456789
输出例子：
123456789

```cpp
//使用<iomanip>(io manipulate, 输入输出控制器)提供的丰富功能可以轻松实现.
#include <iostream>
#include <iomanip>
#include <cmath>//floor()向下取整函数. 在c中也有, 在<math.h>中定义.
using namespace std;

int main(){
    int n; cin >> n;
    cout << setw(9)// [输出宽度下限] 设定为9(输出宽度: 要占用多少个字符. 注意, 如果是浮点数, 小数点也是占一个字符的!)
    << setfill('0')// 配合setw()使用, 设定填充字符为0.
    << n
    << endl;
}
```
### 1.4.3 计算圆面积
给定一个圆的半径 r ，请你求出该圆的面积。
保证半径 r 是整数。
如果你的答案和标准答案的误差不超过 10−3，即可通过本题。

输入描述：
第一行有一个整数 n 。
输出描述：
输出一个数字，代表圆的面积。

示例
输入例子：
123
输出例子：
47529.155256

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double r;
    cin>>r;
    double s = r*r * acos(-1);  //用r*r比pow(r)要快很多哦.
    cout<<fixed    //fixed只是改变浮点数的显示方式,不改变精度.
    << setprecision(15)<<//显示15位有效数字. fixed搭配时, 表示15位小数点后数字. 这差不多是double能提供的精度榨干了.
    s<<endl;
}
```




# 2.数据结构

## 2.1 栈

### 2.1.1 实现一个栈
请你实现一个栈。
操作：
push x：将x加x 入栈，保证 x为 int 型整数。
pop：输出栈顶，并让栈顶出栈
top：输出栈顶，栈顶不出栈
输入描述：
第一行为一个正整数 n ，代表操作次数。(1≤n≤100000)
接下来每行为一个字符串 (加上一个要操作的数字)，代表一个操作。保证操作是题目描述中三种中的一种。
push 1就是把1push进去.

输出描述：
如果操作为push，则不输出任何东西。
如果为另外两种，若栈为空，则输出 "error“
否则按对应操作输出。

示例1
输入：
6
push 1
pop
top
push 2
push 3
pop

输出：
1
error
3

```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


//先实现一个链表, 然后提供push(栈顶看为链表头部插入), pop(删除链表头节点), top(读取头节点值), 于是这样就变成一个stack了!

class Node{
    public:
    int data;
    Node* pNext;

    Node(int d): data(d), pNext(nullptr){} //构造函数. 
};


class Stack{
    private:
    Node* head;
    int length;
    public:
    Stack(): head(nullptr), length(0){} //构造函数, 初始化空链表. 
    ~Stack(){
        Node* current = head;
        while(current!=nullptr){
            Node* temp = current;
            current = current->pNext;
            delete temp;
        }
    }

    //入栈: 在链表头加一个节点.
    void push(int data){
        Node* newNode = new Node(data);
        newNode->pNext = head; //新节点的pNext指向当前链表头
        head = newNode; //头指针指向新节点
        length++;
    }

    //出栈: 删除链表头节点.
    int pop(){

        if(!head){
            cout << "error" << endl;
            return -1; //栈空, 无法出栈.
        }else {
            cout << head->data << endl;
            Node* temp = head; //保存当前节点
            head = head->pNext; //头指针指向下一个节点
            delete temp;
        }
        return 0; 
    }
    
    //读取栈顶元素: 返回链表头节点的值.
    void top(){
        if(!head){
            cout<<"error"<< endl;
        }else{
            cout << head->data<< endl;
        }
    }       
};


int main() {
    Stack s;
    int n; cin >> n;
    while(n--){
        string command; cin >> command;

        if(command == "push"){
            int x; cin >> x;
            s.push(x);
        }else if(command == "pop"){
            s.pop();
        }else if(command == "top"){
            s.top();
        }
    }
}
```






### 2.1.2 栈的压入、弹出序列

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。
假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
1. 0<=pushV.length == popV.length <=1000
2. -1000<=pushV[i]<=1000
3. pushV 的所有数字均不相同
示例1
输入：
[1,2,3,4,5],[4,5,3,2,1]

返回值：
true

说明：
可以通过push(1)=>push(2)=>push(3)=>push(4)=>pop()=>push(5)=>pop()=>pop()=>pop()=>pop()
这样的顺序得到[4,5,3,2,1]这个序列，返回true  

示例2
输入：
[1,2,3,4,5],[4,3,5,1,2]

返回值：
false

说明：
由于是[1,2,3,4,5]的压入顺序，[4,3,5,1,2]的弹出顺序，要求4，3，5必须在1，2前压入，且1，2不能弹出，但是这样压入的顺序，1又不能在2之前弹出，所以无法形成的，返回false   

```cpp

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pushV int整型vector 
     * @param popV int整型vector 
     * @return bool布尔型
     */

    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        int n = pushV.size();

        int j =0;//pop序列下标

        stack<int> s;//创建一个空栈


        for(int i=0;i<n;i++){

            if(s.top() != popV[j] || s.empty()){
                s.push(pushV[i]);   //当前不能出栈, 继续循环
            }else{
                while(s.top() == popV[j] || !s.empty() ){ //pop到不能pop为止
                    s.pop();//出栈
                    j++;
                }
            }
        }

        //现在应该是空stack.
        if(s.empty()){
            return true; //合法序列
        }else{
            return false; //不合法序列
        }
    }

};
```












