# 给riscv'-unknown-elf-gcc写的Makefile. 
# 裸机开发QEMU模拟RISC-V环境下的freestanding程序.

# 用法: make SRC=your_source.c OUT=your_output.out
# Makefile - RISC-V freestanding: 支持编译当前目录下的多个 .c 文件


# 用法举例：
#   make                # 编译所有 *.c -> *.out
#   make SRC=foo.c      # 只编译 foo.c -> foo.out
#   make foo.out        # 直接以目标名编译
#   make clean          # 删除所有 *.out
#   make clean SRC=foo.c    # 删除 foo.out
#   make clean FILE=foo.out # 删除 foo.out
#   make -B SRC=foo.c   # 强制重建
#   make -n SRC=foo.c   # 只显示将执行的命令（dry-run）


CC = riscv64-unknown-elf-gcc

MODE =   # qemu 或 yemu 或 gcc

# 编译选项
CFLAGS = -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -O2
CFLAGS_yemu = -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -O2
CFLAGS_qemu = -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -O2

# 链接选项
# 裸机开发必须指定程序的起始地址, 0x80000000是QEMU默认的加载地址. 0x00000000是yemu默认的加载地址.
LDFLAGS = -Wl,-Ttext=0x80000000
LDFLAGS_qemu = -Wl,-Ttext=0x80000000
LDFLAGS_yemu = -Wl,-Ttext=0x00000000



# 用户可以提供SRC参数. 这一段根据用户提供情况, 生成变量SRCS和OUTS. 如果使用通用模式规则, SRCS和OUTS就没啥用了. 暂且保留.
# 如果在命令行传入 SRC=xxx.c 则只编译那个文件，否则编译当前目录下所有 .c
SRC ?=
# wildcard *.c 得到当前目录所有.c文件名字, 用空格连接.
C_SOURCES := $(wildcard *.c)

# 如果SRC是空的(输入命令没指定SRC), 则SRCS表示所有.c文件.
# strip()去掉变量值的前后空格.
# :=表示立即替换. =表示用到这个变量的时候才替换.
ifeq ($(strip $(SRC)),)
  SRCS := $(C_SOURCES)
# 如果指定了SRC, SRCS=SRC, 只编译这个文件.
else
  SRCS := $(SRC)
endif

# OUTS表示所有要生成的.out文件. 
# patsubst()是替换函数. 把SRCS字符串中的`.c`替换成`.out`
OUTS := $(patsubst %.c,%.out,$(SRCS))






# 默认目标为all, 依赖为OUTS中的所有.out文件. 
# 比如`make`时, OUTS对应当前目录下所有.c文件的.out文件, 执行all, 生成所有.out.
# 比如`make SRC=foo.c`时, OUTS对应foo.out, 执行all, 生成foo.out.
.PHONY: all 
all: $(OUTS)



# 通用模式规则. 
# %是占位符, 会被替换为make后面的参数. 只用在target:prerequisite这两段中. 这两段用了%的话. 这条规则(即完整的三段式)也叫做`模式规则`. 否则叫做普通规则, 比如`all`和`clean`就是普通规则.
# 比如输入`make foo.out`时, %匹配到foo. 然后, %.out被自动替换为foo.out, %.c被自动替换为foo.c.
# $<第一个依赖, 这里是foo.c.
# $@第一个目标, 这里是foo.out.  
# 默认编译为qemu可运行的.out文件. 请自行查看编译和连接选项.
# 使用方式: make MODE=你想要的编译模式 your_source.c
# 请注意ifeq后面必须加一个空格. ifeq (...,...)
%.out: %.c

ifeq ($(MODE),)
# default: qemu
	@echo  "havent specified compile MODE, default to MODE=qemu."
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
else ifeq ($(MODE),qemu)
# qemu
	$(CC) $(CFLAGS_qemu) $(LDFLAGS_qemu) $< -o $@
else ifeq ($(MODE),yemu)
# yemu
	$(CC) $(CFLAGS_yemu) $(LDFLAGS_yemu) $< -o $@
else ifeq ($(MODE),gcc)
# gcc
	gcc $< -o $@
else
	$(error "Unknown MODE: $(MODE). Use 'qemu' or 'yemu'.")
endif




# 这些是使用SRC变量的规则: 

# 这是一个普通规则. 用来编译可供QEMU模拟器运行的.out文件. 编译好的文件叫做`gcc_rv32_qemu_file.out`.  使用方法是`make gcc_rv32_qemu SRC=your_source.c`
# 推荐使用替换: 使用`make MODE=qemu your_source.c`
.PHONY: gcc_rv32_qemu
gcc_rv32_qemu_file.out: $(SRCS)
	$(CC) $(CFLAGS_qemu) $(LDFLAGS_qemu) $< -o $@


# 这是一个普通规则. 用来编译可供我的yemu运行的.out文件. 编译好的文件叫做`gcc_rv32_yemu_file.out`. 使用方法是`make gcc_rv32_yemu SRC=your_source.c`
# 推荐使用替换: 使用`make MODE=yemu your_source.c`
.PHONY: gcc_rv32_yemu
gcc_rv32_yemu_file.out: $(SRCS)
	$(CC) $(CFLAGS_yemu) $(LDFLAGS_yemu) $< -o $@




# clean 规则：
# - 若指定 FILE=xxx 则删除 FILE
# - 否则若指定 SRC=foo.c 则删除 foo.out
# - 否则删除所有 *.out
# 注意: Makefile可以不声明变量直接用. 比如这里的FILE, 如果用户没指定, $(FILE)就是空字符串.
.PHONY: clean
clean:
#如果 FILE 变量非空, 则删除 FILE 指定的文件.
ifneq ($(strip $(FILE)),)
	rm -f $(FILE)
else
# 如果SRC变量非空, 则删除对应的.out文件. 对应命令`make clean SRC=foo.c`
ifneq ($(strip $(SRC)),)
	rm -f $(patsubst %.c,%.out,$(SRCS))
# 如果只运行`make clean`没有指定SRC或FILE, 则删除所有.out
else
	rm -f *.out
endif
endif




# 反汇编规则.
# 使用方法: make dump BIN=yourfile.out 或者 make dump BIN=yourfile.out ALIASES=no(不使用别名, 展示原生指令)
BIN ?=
# 默认不使用-M no-aliases选项.
ALIASES ?= yes
.PHONY: dump
dump:
# 如果没有指定 BIN 变量, 则提示用户如何使用.
ifeq ($(strip $(BIN)),)
	@echo "请使用: make dump BIN=yourfile.out"
else
ifeq ($(ALIASES),no)
	riscv64-unknown-elf-objdump -M no-aliases -d $(BIN)
else
	riscv64-unknown-elf-objdump -d $(BIN)
endif
endif


#QEMU规则. 用法: make qemu BIN=yourfile.out
.PHONY: qemu
qemu:  qemu-system-riscv32 -nographic -M virt -bios none -kernel $(BIN)



.PHONY: help
help:
	@echo "Makefile usage:"
	@echo "  make                 # build all .c -> .out"
	@echo "  make SRC=foo.c       # build only foo.c -> foo.out"
	@echo "  make foo.out         # build by target"
	@echo "  make clean           # remove all .out"
	@echo "  make clean SRC=foo.c # remove foo.out"
	@echo "  make clean FILE=foo.out # remove foo.out"
	@echo "  make -B SRC=foo.c    # force rebuild"
	@echo "  make -n SRC=foo.c    # dry-run (show commands)"

