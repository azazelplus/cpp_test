import pandas as pd
import matplotlib.pyplot as plt

# 读取 CSV 文件
data = pd.read_csv('data.csv')

# 检查列是否至少有两列
if data.shape[1] < 2:
    raise ValueError("CSV 文件至少需要两列：第一列为时间，第二列为变量值")

# 提取时间和变量值
time = data.iloc[:, 0]
value = data.iloc[:, 1]

# 绘图
plt.figure(figsize=(10, 5))
plt.plot(time, value, marker='o', linestyle='-', color='blue')
plt.xlabel('Time')
plt.ylabel('Value')
plt.title('Time vs Variable')
plt.grid(True)
plt.tight_layout()
plt.show()
