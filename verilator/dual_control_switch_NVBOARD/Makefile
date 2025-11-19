






#顶层模块名(verilog中写的module [name](...))
TOPNAME = dual_control_switch
#约束文件
NXDC_FILES = ./constr/$(TOPNAME).nxdc
#包含路径
INC_PATH ?=	

#使用仿真器为 verilator
VERILATOR = verilator

# verilator编译选项
# -MMD: 让verilator生成依赖文件.d
# --build: 让verilator生成cpp代码后, 自动调用编译器, 编译得到可执行文件.
# -cc: 告诉verilator生成cpp模型. 这是最常用的输出模式, 还有--exe(直接生成可执行文件), --sc(生成SystemC模型)
# tips: `--build -cc`选项会让verilator生成一个Makefile(Vtop.mk), 然后使用make来按照这个Makefile编译cpp文件. 所以事实上一个make可以完成很复杂的事情, 甚至嵌套make.
# -03: 优化等级: 激进
# --x-assign fast 该选项控制verilator遇到verilog语言中`x`未定义的赋值处理方式. fast表示直接随机赋值为0/1, 提高速度. 
# --x-initial fast: 同上, 控制verilog语言中未初始化的寄存器的初始值.
# --noassert: 禁用verilator自带的$assert断言检查, 提高速度. 但会失去一些错误检查功能.
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

# 构建目录. 在这里存放生成的中间文件和可执行文件.
BUILD_DIR = ./build
# 对象文件目录. 在这里存放目标文件(verilator生成的cpp文件, Makefile, 编译后的.o文件)
OBJ_DIR = $(BUILD_DIR)/obj_dir
# 变量`BIN`表示最终生成的可执行文件路径.
BIN = $(BUILD_DIR)/$(TOPNAME)

# 注意: default并不是一个特殊的target名字. Makefile选取文件里的第一个target作为默认目标(即输入`make`所构建的对象). 
default: $(BIN)


# 立即执行函数调用. 立即mkdir BUILD_DIR目录. -p: 如果目录已存在, 则不报错. 如果不存在, 则创建目录.
$(shell mkdir -p $(BUILD_DIR))



# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source. 
# VSRCS变量: vsrcs文件夹内存放的verilog源文件路径. 空格连接. 
# CSRCS变量: csrcs文件夹内存放C/C++源文件路径. +=即追加变量内容. 就是用一个空格连接两个字符串变量. 此处就是所有cpp源文件 + 约束文件.
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard.
#此处的include和cpp的#include类似, 作用是将指定文件的内容复制到当前位置. `nvboard.mk`是NVBoard用到的一些规则.
include $(NVBOARD_HOME)/scripts/nvboard.mk



# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
# 构建可执行文件的规则.
$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))


# `all`是一个约定俗成的target名, 意为构建"总目标", 即一次性构建所有需要的东西. 此处all表示构建default目标. 即$(BIN).
all: default

# run是一个约定俗成的target名, 意为运行程序. 这里它所做的命令是沉默方式运行$(BIN)这个可执行文件.
# `$^`是makefile的关键词. 表示所有依赖文件的列表, 在这里`$^`即为`$(BIN)`, 生成的可执行文件的路径. 
# `@(bash command)`表示执行之后的bash command但不在终端显示命令. 
run: $(BIN)
	@$^		

clean:
	rm -rf $(BUILD_DIR)

.PHONY: default all clean run




include /home/azazel/ysyx-workbench/npc/Makefile



