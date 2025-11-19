


双控开关用例.
源代码是 top.v, sim_main.cpp.

从源代码构建项目的流程:
准备好这两个文件放在当前目录, 
然后使用verilator命令:

```bash
verilator --cc top.v --exe sim_main.cpp --trace -Wall
```
| 参数                   | 说明                                          |
| -------------------- | ------------------------------------------- |
| `--cc`               | 生成 C++ 模型（不生成 SystemC）                      |
| `top.v`              | 你的顶层 Verilog 模块                             |
| `--exe sim_main.cpp` | 使用 `sim_main.cpp` 作为仿真主程序（Verilator 不自带仿真器） |
| `--trace`            | 启用 VCD 波形生成（启用 tfp/wave.vcd）                |
| `-Wall`              | 打开所有警告                                      |

* 然后使用verilator生成好的文件和makefile编译:

```bash
make -C obj_dir -f Vtop.mk Vtop
```


* 运行仿真:


```bash
./obj_dir/Vtop
```

* 显示波形: (如果你安装了`gtkwave`)

```bash
gtkwave wave.vcd
```






