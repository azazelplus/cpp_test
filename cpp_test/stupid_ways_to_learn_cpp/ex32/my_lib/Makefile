#这是我的库`my_lib`的Makefile.
#对了要是没有make.exe怎麽办?你随便下一些gnuwin32或者mingw64之类的别怕重复, 下载好后把里面的bin里面的make.exe整到环境变量里就行. 别把整个bin的所有可执行文件全加进环境变量了, 可能会冲突, 如果你已经安装了gcc啊之类的.
#哦对了你不想用make.exe?想直接gcc?完全可以你可以忽略这个Makefile了.

#定义变量.(CC, CFLAGS这些都是预设变量)
CC = gcc		#指定编译器为gcc
CFLAGS = -Wall -g	#-Wall：开启所有常见的编译警告。-g：生成调试信息，方便用调试器（如 gdb）调试程序。
SRC_DIR = src		#存放源文件的目录或文件。
BIN_DIR = bin		#指定存放最终可执行文件的目录。
OBJ_DIR = obj		#存放目标文件（.o 文件）的目录。

#源文件和目标文件的定义
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/list.c
OBJ_FILES = $(OBJ_DIR)/main.o $(OBJ_DIR)/list.o
TARGET = $(BIN_DIR)/my_program

#默认目标 all
all: $(TARGET)

#4. 生成目标文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#链接生成可执行文件
$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET)

#清理目标文件和可执行文件
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# 标记伪目标
.PHONY: all clean






