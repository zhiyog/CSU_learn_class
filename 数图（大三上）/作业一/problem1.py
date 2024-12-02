import numpy as np
import cv2

# 读取彩色图像（为 RGB 格式）
image = cv2.imread('图片一.png')

# 获取图像的高度和宽度
height, width = image.shape[:2]

# 1. 灰度化操作
gray_image = np.zeros((height, width), dtype=np.uint8)
for i in range(height):
    for j in range(width):
        r, g, b = image[i, j]
        # 按照公式计算灰度值
        gray_value = 0.299 * r + 0.587 * g + 0.114 * b
        gray_image[i, j] = int(gray_value)

# 2. 二值化操作
binary_image = np.zeros((height, width), dtype=np.uint8)
threshold = 127
for i in range(height):
    for j in range(width):
        # 根据灰度值进行二值化
        binary_image[i, j] = 255 if gray_image[i, j] >= threshold else 0

# 3. 均值化操作 (简单平均滤波)
smoothed_image = np.zeros_like(image, dtype=np.uint8)
kernel_size = 3
offset = kernel_size // 2

for i in range(offset, height - offset):
    for j in range(offset, width - offset):
        # 获取邻域
        region = image[i-offset:i+offset+1, j-offset:j+offset+1]
        # 计算每个通道的均值
        r_mean = np.mean(region[:, :, 0])
        g_mean = np.mean(region[:, :, 1])
        b_mean = np.mean(region[:, :, 2])
        # 更新图像像素值
        smoothed_image[i, j] = [r_mean, g_mean, b_mean]

# 显示结果
cv2.imshow('Original Image', image)
cv2.imshow('Gray Image', gray_image)
cv2.imshow('Binary Image', binary_image)
cv2.imshow('Smoothed Image', smoothed_image)

cv2.waitKey(0)
cv2.destroyAllWindows()
