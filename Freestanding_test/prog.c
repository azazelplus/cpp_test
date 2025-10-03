


//这是一个我们自己规定的freestanding环境程序, 没有main函数, 也没有标准库. 程序从_start函数开始执行.

//ebreak()接受两个立即数arg0, arg1, 并把它们分别放进寄存器a0, a1, 然后执行ebreak指令.(注意不是递归执行自己这个函数而是RV的ebreak指令)
static void ebreak(long arg0, long arg1){
  //asm()内联汇编函数. 每一行""内是一条汇编指令. volatile关键字不允许编译器优化掉这断汇编.
  //%0, %1是占位符, 代表后面输入的参数arg0, arg1.
  //汇编代码之后, 第一个`:`后面是输出操作数, 第二个`:`后面是输入操作数.
  //"i"表示立即数约束: 要求该参数是一个编译时常量.
  //"r"表示寄存器约束: 该参数可以放在任意寄存器中.
  asm volatile(
    "addi a0, x0, %0;"
    "addi a1, x0, %1;"
    "ebreak"
    : 
    : "i"(arg0), "i"(arg1)
  );
}


//即令a0=0, a1=ch, 然后执行ebreak指令. 约定当a0=0时表示打印字符.  
static void putch(char ch){ebreak(0, ch);}

//即令a0=1, a1=code, 然后执行ebreak指令. 约定当a0=1时表示程序结束, a1是返回码. 之后进入死循环.
static void halt(char code){ebreak(1, code); while(1);}

void _start(){
  putch('A');
  halt(0);
}



