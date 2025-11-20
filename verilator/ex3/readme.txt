


nvboard的工作流程：

先写好.v

然后复制来一个工程框架, 就是有csrc,  vsrc, constr, Makefile的文件夹

把.v放到vsrc, 然后去修改scrc和constr. 修改的时候你可能会用到的东西: \\wsl.localhost\Ubuntu\home\azazel\ysyx-workbench\nvboard\board\N4, 即引脚绑定图.

第一步先写constr/[你的顶层模块名].nxdc. 很简单你就绑定[你的顶层模块信号] [你在N4查到的nvboard接口名].
 	这个nxdc的文件名必须是[你的顶层模块名].nxdc, 这样make才能正确读取.
	格式必须是```你的顶层模块信号] [你在N4查到的nvboard接口名]```, 中间只能有一个空格!!

第二步去写scrc/下的cpp文件. 这个cpp的名字你随便. 这个文件你主要要修改的就是:
	如果用的模板是组合/时序, 你现在的变了, 需要改一下宏;
	改一下顶层模块名字. 把所有V[]替换一下. 位置包括头文件, 还有nvboard_bind_all_pins函数传入的参数.(因为一会儿make调用verilator生成的C文件中类名为V[你的顶层模块名]) 本来是可以优化成只改一个宏的吧? 我还没准备好...
	2025 11 20 我解决了. 用两级宏. 详见ex2的ex2.cpp
	其他的仿真流程其实都不用动...
	
第三步修改Makefile. 主要修改变量TOPNAME

修改完后make run即可.
















