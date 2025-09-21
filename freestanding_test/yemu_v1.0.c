// 将编写的.elf转换为可烧录bin文件后载入: 
// riscv64-unknown-elf-objcopy -j .text -O binary prog.out prog.bin
// -j表示只提取.text段, -O binary表示输出为bin格式.




#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <string.h>




//自定义断言宏, 便于调试. 比assert多了打印信息和行号.
//用法: Perror(fp != NULL, "open %s failed", "config.txt");

//do while(0)是个常见的宏定义技巧. 只执行一次, 而且整个宏用大括号, 内部if和else不会不小心匹配到外面的东西.
//stderr, 全局指针. 指向标准错误输出流.
//fprintf()原型: `int fprintf(FILE *stream, const char *format, ...);` 第一个参数是要把内容写到哪里, 常用有stdout, stdin, stderr.
// C语言有字符串拼接功能. 相邻字符串自动拼接: `printf("hello" "world");`等价于`printf("helloworld");`
//#expr, 宏的字符串化操作符, 将expr转换为字符串常量.

//注意: "Assertion failed: %s\nMessage: " format "\nFile: %s, Line: %d\n" 是fprintf的字符串, 其中格式化变量匹配为: #expr匹配%s, ##__VA_ARGS__匹配format中的格式化变量, __FILE__匹配%s, __LINE__匹配%d.
//__FILE__, __LINE__是预定义宏, 分别表示当前文件名和行号.
//__VA_ARGS__是C99标准引入的, 用于表示可变参数宏中的所有参数.
//##__VA_ARGS__ 是个小技巧：如果宏调用时没有额外参数，编译器会把前面的逗号去掉。
//"format : %s"是个字符串字面量拼接.
#define Assert(expr, msg, ...) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "Assertion failed: %s\nMessage: " msg "\nFile: %s, Line: %d\n", \
                    #expr, ##__VA_ARGS__, __FILE__, __LINE__); \
            exit(1); \
        } \
    } while (0)

#define Perror(cond, format, ...) \
    Assert(cond, format ": %s", ##__VA_ARGS__, strerror(errno))




//PC寄存器.
uint32_t R[32], PC;

//我们分配出64byte的内存. 是的, 这非常小.
//它初始存放的数据就是那个最简单prog.c, 也就是_start()函数的汇编指令, 一共7条.
uint8_t M[64] = {
    0x13, 0x05, 0x00, 0x00, 0x93, 0x05, 0x10, 0x04, 0x73, 0x00, 0x10, 0x00,
    0x13, 0x05, 0x10, 0x00, 0x93, 0x05, 0x00, 0x00, 0x73, 0x00, 0x10, 0x00,
    0x67, 0x00, 0x00, 0x00
};



bool halt = false;

void inst_cycle() {
    uint32_t inst = *(uint32_t *)&M[PC];
    if ((inst & 0x7f) == 0x13 && ((inst >> 12) & 0x7) == 0) { // addi
        if (((inst >> 7) & 0x1f) != 0) {
            R[(inst >> 7) & 0x1f] = R[(inst >> 15) & 0x1f] + 
                (((inst >> 20) & 0x7ff) - ((inst & 0x80000000) ? 4096 : 0));
        }
    } else if (inst == 0x00100073) { // ebreak
        if (R[10] == 0) { 
            putchar(R[11] & 0xff); 
        } else if (R[10] == 1) { 
            halt = true; 
        } else { 
            printf("Unsupported ebreak command\n"); 
        }
    } else { 
        printf("Unsupported instruction\n"); 
    }
    PC += 4;
}

int main(int argc, char *argv[]) {
    PC = 0; 
    R[0] = 0; // can be omitted since uninitialized global variables are initialized with 0 in C.

    //读取程序到内存M. super defensive programming!!!!!
    assert(argc >= 2); //检查是否提供了输入文件名.
    FILE *fp = fopen(argv[1], "r");
    assert(fp != NULL); //检查文件是否成功打开.
    int ret = fseek(fp, 0, SEEK_END);   //fseek()函数用于移动文件指针到文件的指定位置. 这里我们将文件指针移动到文件末尾.
    assert(ret != -1);  //检查fseek是否成功.
    long fsize = ftell(fp); //ftell()函数返回当前文件指针的位置. 由于我们之前将文件指针移动到了文件末尾, 因此这里返回的就是文件的大小.
    assert(fsize != -1); //检查ftell是否成功.
    rewind(fp); //将文件指针重新定位到文件开头.
    assert(fsize < 1024); //检查文件大小是否小于1024字节.
    ret  = fread(M, 1, fsize, fp); //fread()函数从文件中读取数据. 这里我们将文件的内容读取到内存M中.
    assert(ret == fsize); //检查是否完整读取了预期数量的字节
    fclose(fp);


    while (!halt) { 
        inst_cycle(); //指令循环
    }
    return 0;
}