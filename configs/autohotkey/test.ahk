;   ahk文件的注释是`;`. ahk语法相对简单. 无缩进要求. 变量不需要声明类型.`:`表示赋值,函数调用或运算.
;   if语句和其他控制结构, 使用经典的if(条件){语句}结构.
MsgBox("窗口消息: helloworld")


; ^表示ctrl, +表示shift, !表示alt, #表示win键. 组合键用`+`连接. `::`表示定义热键.
; Run("notepad")表示运行notepad程序.  这里的"Notepad"是窗口标题. 如果想要更精确, 可以直接指定路径.
; `Send`表示发送按键. `Sleep`表示等待一段时间.
; `MsgBox`表示弹出消息框. `ExitApp`表示退出脚本.
; 函数WinExist作用: 接收一个字符串为窗口(类)名,然后查询. 如果窗口实例存在, 返回窗口的句柄handle, 也即id. 可以通过工具window spy查看. 否则返回0.
#HotIf !WinExist("Notepad++")
^q::{
    Run("Notepad")
}



; 对于更复杂的程序, 其窗口名称可能会变化. 这时可以使用`ahk_class`来判断窗口类型.
; `窗口类(window class)`是每个应用程序窗口的一个内部标识符, 由操作系统为每个窗口分配.
; autohotkey dash提供了一个小工具叫window spy! 用它来获取窗口的类名. 比如notepad++的类名是`Notepad++`.
; ;下面这个程序实现^n打开notepad++.
#HotIf !WinExist("ahk_class Notepad++")
^n::{
    Run("C:\Program Files\Notepad++\notepad++.exe")
}



;热字符串的用法
; 输入hw并且按下空格/./回车(称为终止符),可以得到hello world字符串.
::hw::hello world

;也可以免除终止符:
:*:hw::hello world

;默认HW会带出来HELLO WORLD. 可以设置为大小写敏感(`C`):
:*C:hw::hello world

;如果hw处于一个字符串之间,,则不会触发替换.可以让字符串之间的hw也响应(`?`):
:*C?:hw::hello world


; 变量和函数
; ahk的变量域很随意, 所有变量都是全局的. 不给函数传参数,也可以访问外部变量. 
; 如果函数里有同名变量, 则优先使用函数体内部变量.
x := 1
MsgBox(x)
myFunc(x){
    return x+1
}
y := myFunc(100)
MsgBox(y)


; 分支.和C相似... 也可以用switch a{case 1: xxx; case 2: xxx; default: xxx}
a := Random(1,100)
if(a>50){
    MsgBox("大于50")
}else if (a>30){
    MsgBox("大于30")
}else {
    MsgBox("小于30")
}

; 用loop [次数]语句实现循环.不写次数的话, 无限循环.. 有一个内置变量称为`A_Index`,表示当前循环的索引.  `break`表示跳出循环.
loop 5{
    MsgBox('A_Index is' A_Index)
}



; 控制窗口
; WinExist()作用: 接收一个字符串为窗口(类)名,然后查询. 如果窗口实例存在, 返回窗口的句柄handle, 也即id. 可以通过工具window spy查看. 否则返回0.
; WinActive()作用: 接收一个窗口实例id. 判断窗口是否处于活动状态. 如果处于活动状态, 返回1, 否则返回0.
; WinActivate()作用: 接收一个窗口实例id. 将窗口激活. 

; 模拟鼠标操作
; Mouseclick()作用: 模拟鼠标点击. 接收一个窗口实例id. 如果窗口处于活动状态, 则在窗口上点击. 否则在屏幕上点击.



WinActivate('计算器')
; 这里的'left'表示鼠标左键, 'right'表示鼠标右键. 1表示点击一次, 0表示不移动鼠标, 'NA'表示不使用窗口坐标.
MouseClick('计算器', 'left', 1, 0, 'NA')