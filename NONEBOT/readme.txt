venv_nonebot文件夹存的是我创建的venv_nonebot虚拟环境.python3.11.7.






## 开发日志

* 在终端激活这个虚拟环境.
 .\venv_nonebot\scripts\activate
 
* 安装pipx

	* 接下来pip install --user pipx --user
	--user选项: 只在当前用户(azazel)的主目录(.../user/azazel)下安装. 单用户个人电脑没啥区别
	pipx是一个用来全局安装的隔离运行python命令行的应用.


	* 确保你系统的 PATH 环境变量中包含 pipx 安装的 CLI 命令路径。
	pipx ensurepath
	比如说：你用 pipx install nb-cli 安装了 nb 命令，它会被放到一个特定的目录下（不是系统 Python、也不是你自己的虚拟环境），而 ensurepath 会把那个目录加进系统 PATH，确保你能直接用 nb 这个命令。


*  安装nb命令行工具
pipx install nb-cli





