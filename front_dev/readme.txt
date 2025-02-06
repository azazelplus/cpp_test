




当前使用vscode上进行前端开发的环境:
使用三个插件
`HTML CSS Support`
`Live Server`	提供实时预览变化.
`Auto Rename Tag`	修改HTML标签的时候同步修改.就是你把<h1>修改为<h2>后, 后面的</h1>自动变为</h2>. (Automatically rename paired HTML/XML tag, same as Visual Studio IDE does.)


tips:
想输入<h1></h1>, 可以直接打一个h1, 自动联想会补全.
输入!, 联想!即为一个标准模板.
写注释时, 输入<!--, 会自动补全-->

快速创建自定义类名/id名的块(div):
	输入div.nav可以自动补全为id="nav"的div块: <div id="nav"><div>
	输入div#nav可以自动补全为class="nav"的div块: <div class="nav"><div>
至于其他类型的标签, 也可以类似地快速创建:
	p.father补全为<p class="father"> <p>
	p#myp	补全为<p id="myp"> <p>

vscode左上角文件->勾选自动保存后, 可以解决很多需要ctrl+s才能刷新的问题. 比如c编译器, html实时预览. 















