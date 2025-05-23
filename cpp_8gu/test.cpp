
//输入: 第一行是N,K(表示N个字符串, 希望最后输出的字符串长度为K), 
//剩下N行中, 第i行为第i个字符串和要求从这个字符串中最多选出字符的个数xi.
//输出: 一个字符串T, 长度为K.
//本题要求:字符串字典序尽可能小. 字典序是指: 字符串的字母表顺序, 比如`abc` < `abd` < `ac` < `a` < `b` < `c`.
//思路: 维护一个链表, 当链表长度小于K时, 遍历每个字符串的每个字符, 对该字符遍历链表, 如果字典序小于链表某元素, 就可以插在其前面.
//当链表长度达到K后, 遍历每个字符串的每个字符, 对该字符遍历链表, 如果字典序小于链表某元素, 直接替换这个元素, 而不是插在它前面.


#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <stack>
#include <list>
using namespace std;



int main(){

#if 0   
    int N, K;
    cin >> N >> K;
    string str[N];  //N个字符串
    int x[N];       //每个字符串最多能使用的字符个数
    for(int i=0; i<N; ++i){
        cin >> str[i] >> x[i];
    }

#endif

#if 1
    int N=2, K=3;
    int x[2]={2,1};
    string str[2]={"abb", "ccaa"}; //N个字符串
#endif
    //处理:将这N个字符串全部按照字典序排列.
    for(int i=0; i<N; ++i){
        sort(str[i].begin(), str[i].end());
    }
    //此时的字符串是'abb'和'aacc'.

    //cout << '\n' <<str[0] << '\n' <<  str[1] << endl; //打印字符串.


    cout << '\n' <<str[0] << '\n' <<  str[1] << endl; //打印字符串.
    stack<char> s;
    list<char> l;   //现在l是空链表.

    #if 0
    //直接初始化链表l为size为K的全部为最大字典序'z'的链表:
    for(int i=0; i<K; ++i){
        l.push_back('z');
    }
    #endif

    //遍历N个字符串. 对每个字符串:  
    for(int i=0; i<N; ++i){
        int num_i = 0;    //计数:当前字符串使用到的字符个数.
        int len = str[i].length();

        //遍历第i个字符串: 从前往后, 停止遍历: 当前字符串使用字符数量>=x[i]或者已遍历完.
        for(int j=0; j<len&&num_i<x[i]; ++j){
            //遍历第j个字符.
            char c = str[i][j]; //当前字符

            //如果链表长度<K,此时允许插入. 逻辑: 遍历链表, 如果链表某个元素y大于c, 把c插入在y前面.
            if(l.size() < K){
                //遍历链表.
                if(l.empty()){ //如果链表为空, 直接插入c.
                    l.push_back(c); //直接插入c.    
                    //for(auto it=l.begin(); it!=l.end(); ++it){cout << *it;}
                    num_i++;        //当前字符串使用字符数量+1.
                    continue;
                }

                //链表遍历
                for(auto it=l.begin(); it!=l.end(); ++it){
                    //当前遍历链表元素: *it
                    if(*it > c){ //如果链表元素*it大于c, 把c插入在*it前面.
                        l.insert(it, c); //在it指向的元素前插入c. insert()函数将
                        //for(auto it=l.begin(); it!=l.end(); ++it){cout << *it;}
                        num_i++;         //当前字符串使用字符数量+1.
                        break;           //插入完毕, 退出本次对链表遍历循环.
                    }else //如果这是最后一次遍历,说明链表元素*it小于c, 直接插入c.
                    if (it == --l.end()){ //如果it指向链表最后一个元素, 直接插入c.
                        l.push_back(c); //直接插入c.
                        //for(auto it=l.begin(); it!=l.end(); ++it){cout << *it;}
                        num_i++;        //当前字符串使用字符数量+1.
                        break;          //插入完毕, 退出循环.
                        }
                    }
                }else { //如果已经满了. 逻辑: 遍历链表, 如果链表某个元素y大于c, 把c替换掉y.
                //遍历链表.
                for(auto it=l.begin(); it!=l.end(); ++it){
                    if(*it > c){ //如果链表某个元素y大于c, 把c替换掉y.
                        *it = c;   //替换掉y.
                        num_i++;   //当前字符串使用字符数量+1.
                        break;     //替换完毕, 退出循环.
                    }
                }
            }
        }
    }
    //打印字符串l.
    for(auto it=l.begin(); it!=l.end(); ++it){
        cout << *it;
    }

}
