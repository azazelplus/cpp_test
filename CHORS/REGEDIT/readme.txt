这里放着一些我写的.reg脚本. 双击就可以把对应的项(文件夹)和其键值对添加到注册表中.

powershell.reg在`HKEY_CLASSES_ROOT\Directory\Background\shell\`生成项PowerShellUser, 并且在里面配置的键值对以及要执行的命令(子项command)为右键快捷菜单添加"open powershell here."

## 在GUI界面修改注册表

修改注册表最好的方法是这样重写一个项, 而不是在已经存在的那个项文件夹里改键值对, 太麻烦了.
如果非要在GUI操作呢? 好吧。一般你会遇到的第一个问题是权限问题, 只需要右键你要改的注册表文件夹->权限->选择[Administrators]用户组, 将这个用户组的权限选项中的[完全控制]勾选[允许]. 
	* 如果你不被允许这样操作, 你需要先点击[高级], 然后在左上角将[所有者: system]改为Administrators. 然后你就被允许更改权限了.

* [所有者]是什麽意思? 
	* 在windows中, 注册表是某种类似地契的东西.(这是因为要添加注册表的东西太多了, 很多应用程序; system; 你自己(administrators)都会添加东西进去.) 
	每个注册表项(文件夹)都有[所有者]. 只有`有管理员权限的所有者`才能更改权限设置.
* 你所看到的那些用户组都是谁?
| 项目名                                              | 是谁             | 说明                              |
| ------------------------------------------------ | -------------- | ------------------------------- |
| **ALL APPLICATION PACKAGES**                     | 系统预定义组         | 给应用商店 UWP 应用（Win10/11 应用）使用     |
| **未知帐户（S-1-15-xxx）**                             | 已删除或变动的用户      | 系统找不到原来是谁，通常是“以前的某个账户”或“卸载了的应用” |
| **CREATOR OWNER**                                | 当前资源创建者        | 占位符，代表资源创建人，通常是管理员账号            |
| **SYSTEM**                                       | Windows 核心系统进程 | 代表操作系统本身（必须保留）                  |
| **Administrators (DESKTOP-XXXX\Administrators)** | 本机管理员组         | 所有管理员身份的用户，包括你（如果你是管理员）         |
| **Users (DESKTOP-XXXX\Users)**                   | 所有普通用户         | 你在不以管理员身份运行时，也属于这个组             |





