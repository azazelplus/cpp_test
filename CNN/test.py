import torch

# python中的文件夹是一个模块. 模块中的函数是可以直接调用的. 模块中的变量也是可以直接调用的.
from my_model.cnn import simpleCNN

x = torch.randn(32, 3, 224, 224)  #生成一个32张224x224的3通道的随机图像.
model = simpleCNN(10)  #实例化一个simpleCNN类的对象. 10是分类数.
output = model(x)
print(output.shape)  #打印输出的张量的尺寸.


# 输出为: torch.Size([32, 10])






