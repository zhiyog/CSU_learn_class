import cv2
import numpy as np
import matplotlib.pyplot as plt

# 二值矩阵 (0 表示黑，1 表示白)
binary_image = np.array([
    [1, 1, 0, 1, 1, 1, 0, 1],
    [1, 1, 0, 1, 0, 1, 0, 1],
    [1, 1, 1, 1, 0, 0, 0, 1],
    [0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 0, 1, 0, 1],
    [0, 0, 0, 1, 0, 1, 0, 1],
    [1, 1, 1, 1, 0, 0, 0, 1],
    [1, 1, 1, 1, 0, 1, 1, 1]
], dtype=np.uint8) * 255  # 将 1 转换为 255（白），0 保持 0（黑）

# 使用 cv2.connectedComponents 进行连通区域标记（4-邻域）
num_labels, labels = cv2.connectedComponents(binary_image, connectivity=4)

# 显示结果并添加网格线和编号
plt.figure(figsize=(10, 5))

# 绘制标记后的连通区域图像
plt.imshow(labels, cmap='nipy_spectral', interpolation='none')

# 添加网格线
plt.grid(which='both', color='black', linestyle='-', linewidth=2)

# 获取图像大小
rows, cols = labels.shape

# 添加每个小格子的序号
for i in range(rows):
    for j in range(cols):
        # 获取当前像素的连通标记
        label_value = labels[i, j]
        plt.text(j, i, str(label_value), ha='center', va='center', color='white', fontsize=12)

# 设置刻度以适应网格线
plt.xticks(np.arange(-0.5, cols, 1), [])
plt.yticks(np.arange(-0.5, rows, 1), [])

# 设置网格线
plt.gca().set_xticks(np.arange(-0.5, cols, 1), minor=True)
plt.gca().set_yticks(np.arange(-0.5, rows, 1), minor=True)
plt.gca().grid(which='minor', color='black', linestyle='-', linewidth=2)

plt.show()

# 保存结果图像
cv2.imwrite('labeled_image_with_grid.png', (labels * (255 // num_labels)).astype(np.uint8))
