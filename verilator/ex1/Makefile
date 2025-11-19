# 这个Makefile要求的文件格式是子文件夹vsrc, csrc, constr, build, 其中分别装有$(TOPNAME).v, $(TOPNAME).c, $(TOPNAME).nxdc, auto_bind.cpp
# 需要改动的地方: TOPNAME改成你的. 	NXDC_FILES, VSRCS, CSRCS路径要改一下. 需要链接的库也要自己调整. LDFLAGS


TOPNAME = mux4to1_2bit
NXDC_FILES = constr/$(TOPNAME).nxdc
INC_PATH ?=	
# `?=`意味 如果INC_PATH变量还没有被定义, 则定义其值为""(空). 如果外部已传入, 比如用户输入命令`make INC_PATH=/somepath`, 则该行语句不执行.

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

# 构建目录. 在这里存放生成的中间文件(autobind)和可执行文件.
BUILD_DIR = ./build
# 对象文件目录. 在这里存放目标文件(verilator生成的cpp文件, Makefile, 编译后的.o文件)
OBJ_DIR = $(BUILD_DIR)/obj_dir
# 最终生成的可执行文件路径
BIN = $(BUILD_DIR)/$(TOPNAME)


default: $(BIN)

# 立即执行函数调用. 立即mkdir BUILD_DIR目录. -p: 如果目录已存在, 则不报错. 如果不存在, 则创建目录.
$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

all: default
# `$^`表示所有依赖文件的列表, 此处即=$(BIN). `@(bash command)`表示之后的bash command静默执行.
run: $(BIN)
	@$^		

clean:
	rm -rf $(BUILD_DIR)

.PHONY: default all clean run



