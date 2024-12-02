import cv2
import numpy as np
import matplotlib.pyplot as plt


# Sobel空间域滤波函数
def sobel_space_filter(image):
    # 将图像转换为灰度图（如果图像已经是灰度图则跳过）
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Sobel算子分别在x和y方向上进行卷积
    sobel_x = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=3)  # x方向梯度
    sobel_y = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=3)  # y方向梯度

    # 计算梯度幅值（即边缘强度）
    sobel_edges = cv2.magnitude(sobel_x, sobel_y)

    # 将结果限制在0到255之间，并转换为8位无符号整数
    sobel_edges = np.uint8(np.clip(sobel_edges, 0, 255))

    return sobel_edges


def main():
    # 读取图像（请替换为您图像的路径）
    img = cv2.imread('./建筑物.jpg')

    # 使用Sobel空间域滤波进行边缘检测
    sobel_result = sobel_space_filter(img)

    # 显示原始图像和处理后的图像
    plt.figure(figsize=(12, 6))
    # 设置支持中文的字体
    plt.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体
    plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示问题
    # 原始图像
    plt.subplot(1, 3, 1)
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))  # 将BGR转为RGB以便Matplotlib显示
    plt.title('原始图像')
    plt.axis('off')  # 关闭坐标轴

    # Sobel空间域滤波结果
    plt.subplot(1, 3, 2)
    plt.imshow(sobel_result, cmap='gray')  # 使用灰度图显示
    plt.title('Sobel空间滤波')
    plt.axis('off')  # 关闭坐标轴

    # 显示所有图片
    plt.show()


if __name__ == "__main__":
    main()
