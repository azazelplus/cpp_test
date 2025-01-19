//注意使用方法是在terminal中先编译好binary文件, 然后运行ex18_bubble_sort.exe 1 2 3 4 6 5


//我们顺便在这个文件下学习有关预处理(cpp)的命令. 假设我们在windows cmd环境(vscode提供的terminal即为此.)
//cpp(c preprocessor)是一个C/C++的预处理器程序. 它不是编译器本身，而是编译器的一部分，用于执行代码的预处理操作，例如宏展开、文件包含、条件编译等。
//运行`cpp ex18_bubblesort.c` 会输出该文件经过预处理后的代码. cpp ex18_bubble_sort.c > preprocessed_output.c, 可以保存为一个文件观看.


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//die()一个简单的错误处理函数. 
//它基于库<errno.h>中的errno和perror()函数, 用于输出错误信息并终止程序.
//errno是一个全局变量, 用于存储最近一次系统调用的错误代码.
//如果errno值非0(发生了错误), 说明最近一次系统调用出现了错误.
//perror()函数即present error, 原型: void perror(const char *str); 
//它根据当前errno的值和输入的描述字符串str输出对应的错误信息, 即输出`<str>: <errno对应的错误信息>`
//例如下面的例子, errno=2意味着`ENOENT(表示文件不存在)`, 此时perror("File open error")会输出`File open error: No such file or directory`
// FILE *file = fopen("a_non_existent_file", "r");
//     if (file == NULL) perror("File open error");
void die(const char *message){
    if(errno)   perror(message);//此时error捕获到错误.
    else        printf("ERROR: %s\n", message);//此时error=0, 没有捕获到错误(错误不是由系统调用引起的), 无法用perror()输出错误信息, 只能手动用printf()输出错误.
    exit(1);//终止程序.
}

//(美观起见)定义一个新的类型别名`compare_cb`. 它是一个函数指针类型, 返回值为int, 看为布尔类型(比较结果). 参数为两个int.
//cb=callback(回调). 回调函数的意思就是这个函数是用来使用函数指针被当作另一个函数的参数的.
//typedef给函数指针起别名的格式有些特殊, 不是一般的简单的`typedef int inter`, 而是:
//`typedef [返回类型] (类型别名)(参数列表)`   注意如果返回类型是指针, `*`可以写在类型别名里.
typedef int (*compare_cb)(int a, int b);

//下面实现几个顺序比较函数, 用于不同要求的冒泡排序. 返回布尔值为真时说明顺序正确(不需要交换).
int sorted_order(int a, int b){
    return a>b; //升序排列
}

int reverse_order(int a, int b){
    return a<b; //降序排列
}

//奇怪排序. 这是在干啥? 
int strange_order(int a, int b){
    if(a==0 || b==0) return 0;//如果a或b为0, 则返回0(即不交换).
    else return a%b;//否则返回a%b(即交换).
}

//一个经典的冒泡排序函数. 参数为一个int数组array; 一个int count(数组元素个数); 一个函数指针(用于比较两个整数的大小).
//排序过程中, 比较相邻的两个元素, 如果它们不符合顺序(cmp(target[j], target[j+1]) > 0), 则交换它们的位置。
//由于冒泡排序的基本思想是第i轮排序都会把当前第i大(升序排序时)的元素“冒泡”到最后，因此排序总共需要进行 count 轮，每一轮会让一个元素确定位置。
//最终返回一个排序好的数组指针. 这个数组储存在堆中, 需要手动释放. 
//冒泡函数安放排序数据的数组放在堆中, 这是合适的: 因为堆不是短暂生命周期, 出了bubble_sort()也存在, 可以用返回的target指针访问排序好的内容.
int* bubble_sort(int *array, int count, compare_cb cmp){
    
    int *target = (int*)malloc(count*sizeof(int));//分配大小为数组array的内存. 返回数组开头指针target. 事实上最好在malloc前面显示转换类型, 即(int *)malloc(count*sizeof(int)); 这样可以避免更严格的编译器报错, 如g++.

    //用cpp的new实现更容易.
    //int *target = new(count);

    if(!target) die("Memory error.");//(!target)等价于(target==NULL), 即分配内存失败.

    //使用memcpy()函数(用于内存复制.)将数组array的内容复制到数组target中.
    //原型: void *memcpy(void *dest, const void *src, size_t n);
    memcpy(target, array, count * sizeof(int));

    int temp = 0;//临时变量, 用于实现交换两个相邻元素的值.
    for(int round=0; round<count; round++){
        for(int i=0; i<count-1; i++){
            if(
                !cmp(target[i],target[i+1]) //如果target[i]和target[i+1]不符合顺序.
                )
            {
                temp = target[i];
                target[i]=target[i+1];
                target[i+1]=temp;
            }
        }
    }
    return target;
}


//这个函数用来在main函数中测试bubble_sort()函数, 它会调用bubble函数, 打印结果, 然后自动释放内存.
//它需要的参数即为bubble_sort()函数的三个参数.
void print_bubble(int *array, int count, compare_cb cmp){
    //指针sorted指向排序好的数组.(它指向堆内存.)
    int *sorted = bubble_sort(array, count, cmp);
    if(!sorted) die("Failed to sort as requested.");

    //打印排序好的数组.
    for(int i=0; i<count; i++){
        printf("%d ", sorted[i]);
    }
    printf("\n");

    //释放内存.
    free(sorted);
}


int main(int argc, char *argv[]){
    if(argc<2) die("USAGE: bubble_sort [array you wanna sort, like`1 3 5 2 4 6`]");//linux命令行参数个数至少为2个(第一个参数是二进制程序名bubble_sort), 如果用户只输入了程序名没有跟参数, 则输出提示.(`ERROR: USAGE: bubble_sort 4 3 1 5 6`)


    //先进行读取参数的工作. 
    //要比较的数组个数count被储存在栈中, 而用户输入的数组字符串即`argv`字符串数组, 这些内容已经由操作系统加载并存在`栈`上.
    //用inputs这个指针访问它(inputs 只是 argv + 1 的偏移, 指向的是 argv 数组的内容). 实际上这有点多此一举, 直接用argv指针也可以.只需要从argv[1]开始.
    //然后数组字符串被转为int数组储存在array(动态分配堆内存)中.
    int count = argc-1;

    //remind: **inputs等价于*inputs[]
    char **inputs=argv+1;//inputs指向第一个参数(即第一个数值).
    int *array=(int*)malloc(count*sizeof(int));
    if(!array) die("Memory error.");
    //atoi()函数用于将字符串转换为整数. 原型: int atoi(const char *nptr);
    for(int i=0; i<count; i++){
        array[i]=atoi(inputs[i]);
    }

    //用print_bubble调用bubble_sort()函数.
    print_bubble(array, count, sorted_order);//打印升序排序.
    print_bubble(array, count, reverse_order);//打印降序排序.
    print_bubble(array, count, strange_order);//打印奇怪排序.
    return 0;
}