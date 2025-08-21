CC = gcc
#定义静态库打包工具为ar(archive)
AR = ar	
#-g生成调试信息方便gdb等使用
CFLAGS = -Wall -g	


#默认target为main.  直接运行`make`等价于`make main` 
#这是一个[转发]目标. 当执行`make`或`make all`时, 会执行`make main`, 而main这个target才真正拥有recipe. 这是一个约定俗成的做法.
all: main	



# `libutils.a`目标: 将`utils.o`构建成静态库. bash命令`ar rcs libutils.a utils.o` 将目标文件`utils.o`打包成`libutils.a`. rcs是选项.
# r: replace, 替换已有对象 c: create, 创建静态库(如果不存在) s: 写入symbol table, 加快link速度.
libutils.a: utils.o
	$(AR) rcs libutils.a utils.o



# `utils.o`目标: 编译单元. 注意头文件`utils.h`也要写进依赖, 这样当utils.h被更改后, make会重新编译utils.o.
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c


# 编译生成可执行文件main. 编译使用main.c, 同时链接libutils.a静态库.
# gcc的-L选项即`在当前目录查找静态/动态库文件.a或.so`
# -lname: 链接名为`libname.a`或`libname.so`的库文件. 
# -l选项不接受完整的文件名, 会自动添加前缀lib和后缀.a/.so, 这是linux的传统命名约定.
main: main.c libutils.a
	$(CC) $(CFLAGS) main.c -L. -lutils -o main

clean:
	rm -f *.o *.a main
	
	
	