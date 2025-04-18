





# 1. 输入输出

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
