#变量定义
CC = gcc
CFLAGS = -Wall -g

#清理生成的文件
clean:
	rm -f ex*

#默认目标.
#patsubst即pattern substitution, makefile中的字符串模式替换函数, 格式为$(patsubst <pattern>, <replacement>, <text>)
#wildcard即makefile中的万用字符函数, 格式为$(wildcard <表达式>)
all:$(patsubst %.c, %, $(wildcard ex[0-9]*.c))

#生成目标
# % 通配符表示任何字符串.
# $@ 表示当前规则的目标文件.
# $< 表示规则中第一个依赖文件.
%:%.c
	$(CC) $(CFLAGS)  -o $@ $<
