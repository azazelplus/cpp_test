#using env: 3.9.18(`python_yolo`)
import torch.nn as nn   # `nn`即nerual network


# python的变量类型是在运行中确定的. 比如本代码中的x是一个torch.Tensor类型的变量. 它的类型是在运行时确定的.


# python的类的构造函数必须是 __init__(self, ...)的形式. 其中self是类的实例对象.
# 类似cpp风格的nn.ReLU(...)看起来是同名构造函数, 实际上内部最终调用的函数名为__init__.(self, ...)

# python中的对象可以像函数一样被调用, 只要它实现了__call__方法. 


# 例如, python中自定义一个类的方式:
# class MyClass:
#     def __init__(self, var):
#         self.var = var
#     def __call__(self, var):
#         print("var is: ", var)
# obj = MyClass(1)  #实例化. 实际上这样默认调用了类定义内部的__init__().
# obj(2)  #这样调用实例对象, 打印出"var is: 2". 实际上这样调用了类定义内部的__call__.




# 设定输入图像尺寸和深度(就是通道数. RGB彩色图像为3, 灰度图像为1), 图片张数BATCH
# 输入图像的尺寸是224x224, 深度是3, 图片张数是32, 分类数是10.
H = 224
W = 224
D = 3
BATCH = 32




# python的类定义用法: class 类名(父类):
# nn.Module是pytorch中定义的所有网络的基类. 使用pytorch时, 每个自定义的neural network都要继承自nn.Module.
# 此处定义了一个类名simple_cnn, 继承了nn.Module.
class simpleCNN(nn.Module):
    # 这里定义了类的构造函数.  self的用法类似cpp的this指针.
    # 在python中, 类的成员函数的第一个参数必须是self.
    def __init__(self,num_class): #num_class是分类数. 
        # super()是python继承机制中一个默认的函数. 用于调用父类的构造函数. 用法: super(子类名, self).函数名(参数列表). 在继承类的定义块中, 可以省略子类名和self.  
        super().__init__()      #这一句实际上调用了`nn.Module`类的构造函数`nn.Module.__init__()`.
        
        # 此处定义神经网络的结构. 具体来说这里给我们的类simpleCNN添加了一个叫features的成员变量, 这个成员变量是一个nn.Sequential对象, 也就是一个容器.
        # nn.Sequential是pytorch中的一个容器(container, torch.nn中的一个类.) 它实际上是一个神将网络层的list. 用于将多个nn.Module组合成一个网络.
        # pytorch.nn还提供其他几个常用的容器, 如nn.Sequential(线性按顺序执行多个层), nn.ModuleList(存储多个层但需要手动调用), nn.ModuleDict(用字典存储多个层, 也需要手动调用).
        self.features = nn.Sequential(
            # 括号内部是nn.Sequential的构造函数的参数列表. nn.Sequential类的对象将会按照顺序执行这些层.
            # n.Conv2d()是类nn.Conv2d的构造函数. 构造一个卷积层. 有构造参数: in_channels, out_channels, kernel_size, stride, padding.
            # 此处输入彩色RGB图像, 所以in_channels=3. 输出16个通道(有16个不同的卷积核同时处理数据), 输出16个特征图. 所以out_channels=16. 卷积核大小为3x3, 步长为1, padding为1.
            nn.Conv2d(3,16,kernel_size=3,stride=1,padding=1), # S=1, P=1,可以保持输出的特征图的尺寸不变.(称为等宽卷积)
            nn.ReLU(),  #这一层是卷积层后面的一层激活层. 用于引入非线性因素.
            nn.MaxPool2d(kernel_size=2,stride=2),  #这一层是最大值池化层. 也就是说对于每个2x2的区域, 取最大值作为输出. 自然地, 选择stride=2. 结果就是输出的特征图尺寸长宽减半.
            nn.Conv2d(16,32,kernel_size=3,stride=1,padding=1), #第二个卷积层. 输入16个特征图, 输出32个特征图. 仍然是3x3的卷积核, 等宽卷积.
            nn.ReLU(),  #再来一个激活层
            nn.MaxPool2d(kernel_size=2,stride=2)  #再来一个池化层. 此时图像长宽变为原来的1/4. 
        )

        # 定义全连接层. 我们这个模型最终是分类模型. 同样地, 我们给simpleCNN类添加了一个叫classifier的成员变量, 它也是一个nn.Sequential类型的容器.
        # 这里注意一点, python没有数据类型检查, 这里H/4必须显式转换为int类型. 因为H/4自动判定为一个浮点数, 而nn.Linear()的参数要求是整数.
        self.classifier = nn.Sequential(
            nn.Linear(BATCH * int(H/4) * int(W/4), 128),  #全连接层. 是一个线性层. 参数列表是nn.Linear(in_features, out_features). 输入是上一层给出的特征图, 大小为N张，H*W/16大小。 输出这里选择128维的特征向量
            nn.ReLU(),  #激活层
            nn.Linear(128,num_class)  #全连接层. 最后的输出层， 实现num_class分类. 输出num_class个类别的概率.
        )


    # 前向传播部分. 这里定义了simpleCNN类的一个方法函数. 用于实现前向传播. 也就是说, 给定输入数据, 通过神经网络, 得到输出结果.
    # 传入的参数x是输入数据图像. 它是torch.Tensor类型. pytorch中最核心的数据结构! 其实就是个多维数组. 在深度学习中常用格式为(Batch, Channel, Height, Width)
        # 它有view方法, 用于改变张量的形状. 参数列表为view()
            # view()
        # 它有size方法, 用于获取张量的形状. 参数列表为:
            # size()返回对象的(Batch, Channel, Height, Width),是一个元组.
            # size(0)返回图片组Batch的大小.
            # size(1)返回图片组Channel的大小.
            # size(2)返回图片组Height的大小.
            # size(3)返回图片组Width的大小.

        
    # simpleCNN.features是一个nn.Sequential类型的容器. 这容器的定义中, 其__call__方法实际上是按照顺序执行了容器中的每一层.
    def forward(self, x):
        x = self.features(x)  # 更新x的值. 让其通过features容器, 得到特征图. 这里调用了features容器对象的__call__方法.
        x = x.view(x.size(0), -1)    # 这里调用了torch.Tensor类的view方法. 改变x的形状. 使其变为一个一维数组.
        x = self.classifier(x)  # 更新x的值. 让其通过classifier容器, 得到分类结果. 这里调用了classifier容器对象的__call__方法.
        return x  # 返回x的值. 也就是分类结果.
