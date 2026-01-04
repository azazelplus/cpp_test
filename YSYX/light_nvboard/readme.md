# 1.它干啥?
该项目将light流水灯项目连接到nvboard上.

同时它也是一个NVBoard项目示例, 以后的NVBoard项目都可以改它.


流程: 详见nvboard文档.

# 2.如何用? 

## 1. 准备**.v文件**; **仿真cpp文件**; **约束nxdc文件**; **Makefile**

首先, 建立这样的文件结构:
.
├── vsrc
│   └── top_name.v
├── csrc
│   └── 名称无要求.cpp(内容要`#include TOP_NAME.h`.)
├── constr
│   └── top_name.nxdc
└── Makefile

* 其中,top_name.v的格式就那样, 不需要写仿真模块, 输入输出必须是wire.

* 其中,top_name.cpp的格式是直接抄袭nvboard文件夹的example项目的. 改一下top_name为自己的即可.

* 其中, .nxdr的格式参考文档. 绑定好你的.v文件夹输入输出信号到FPGA板子上.

**(经验证auto_bind.cpp是包含在make规则里的, 不需要手动运行脚本生成.)**
* 然后在constr/目录下运行来自nvboard提供的自动生成约束.cpp文件的py脚本`auto_bind.cpp`:
```bash
   python3 $NVBOARD_HOME/scripts/auto_pin_bind.py ./light.nxdc ../auto_bind.cpp
```
从而在主目录生成`auto_bind.cpp`. 

该命令参数:
* `$NVBOARD_HOME/scripts/auto_pin_bind.py` 运行的朋py脚本
* `./light.nxdc`接收的第一个参数: 约束文本
* `../auto_bind.cpp`接收的1第二个参数: 目标文件


* **Makefile**的格式也直接抄, 但是要改一下里面的TOPNAME名字为你的顶层模块名.


## 2. make run.


* 运行make run规则, 把程序烧录到虚拟FPGA板子上.

* 运行结果: 你会看到一个流水灯:
  ![alt text](image.png)




# 3. 用在我的项目, 该改哪里?

`top_name` 包含在:
* csrc目录里的cpp仿真文件(因为要include Vtop_name.h)
* .v文件. 顶层模块名.
* .nxdc约束文件, 第一句必须是top=[top_name]
* Makefile中的TOPNAME.

这4处都要更改为自己的.





