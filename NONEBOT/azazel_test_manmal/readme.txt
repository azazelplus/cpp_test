这个测试是手动创建一个bot的过程.



一个机器人项目的最小实例中至少需要包含以下内容:

1.入口文件：初始化并运行机器人的 Python 文件(bot.py)
2.配置文件：存储机器人启动所需的配置
3.插件：为机器人提供具体的功能



* 关于python的虚拟环境：
	* 激活虚拟环境 = 把该虚拟环境的路径暂时加到了当前 shell 的 PATH 最前面。
	* 查看当前终端的python环境是哪个：
		* 不用conda： python -c "import sys; print(sys.excutable)"
		* conda：直接

	* 创建新的虚拟环境：
		* 不用conda：  python -m venv .venv --prompt nonebot2
			使用当前激活的python解释器, -m以模块化的方式, 运行模块venv, 在当前目录创建一个.venv文件夹存放这个虚拟环境, 并且将激活提示词设置为nonebot2. 今后你激活这个虚拟环境时, 终端开头会显示类似(nonebot2)PS F:\aza:的样子.
			
		* conda: 直接conda
		
	* 激活某个虚拟环境:
		* 不用conda: 你是用venv创建虚拟环境文件夹的. venv本身不维护一个环境名字注册表. 所以也没有类似管理器的东西可以让你查看电脑上一共有哪些虚拟环境文件夹, 分别在哪里.
		你要在该文件夹路径(假设为/myenv)运行.\Scripts\activate. 即在终端输入source myenv\Scripts\activate.ps1 (虚拟环境.\Scripts里提供了好几个给不同shell用的activate脚本. windows powershell用.ps1, bash用.bat)
		
	* conda:  conda是包管理器, 每个环境都有名字, 而且会自动修改PATH环境变量. 所有环境都被记录在~/anaconda3/envs/
	激活某个环境只需要conda activate myenv
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		