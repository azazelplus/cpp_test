#using env: 3.9.18(`python_yolo`)
import torch.nn as nn   # `nn`即nerual network

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
            # 括号内部是nn.Sequential的构造函数的参数列表. nn.Sequential类的对象僵毁按照顺序执行这些层.
            # n.Conv2d()是类nn.Conv2d的构造函数. 构造一个卷积层. 有构造参数: in_channels, out_channels, kernel_size, stride, padding.
            # 此处输入彩色RGB图像, 所以in_channels=3. 输出16个通道(有16个不同的卷积核同时处理数据), 输出16个特征图. 所以out_channels=16. 卷积核大小为3x3, 步长为1, padding为1.
            nn.Conv2d(3,16,kernel_size=3,stride=1,padding=1), # S=1, P=1,可以保持输出的特征图的尺寸不变.(称为等宽卷积)
            nn.ReLU(),  #这一层是卷积层后面的一层激活层. 用于引入非线性因素.
            nn.MaxPool2d(kernel_size=2,stride=2),  #这一层是最大值池化层. 也就是说对于每个2x2的区域, 取最大值作为输出. 自然地, 选择stride=2. 结果就是输出的特征图尺寸长宽减半.
            nn.Conv2d(16,32,kernel_size=3,stride=1,padding=1), #第二个卷积层. 输入16个特征图, 输出32个特征图. 仍然是3x3的卷积核, 等宽卷积.
            nn.ReLU(),  #再来一个激活层
            nn.MaxPool2d(kernel_size=2,stride=2)  #再来一个池化层. 此时图像长宽变为原来的1/4.
        
        
        )

    # 定义全连接层. 我们这个模型最终是分类模型. tongyang
    self.classifier = nn.Sequential(

    )

