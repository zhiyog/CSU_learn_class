import cv2
import numpy as np
import matplotlib.pyplot as plt


def main():
    # 读取图像，直接以灰度模式读取（0表示灰度模式）
    img = cv2.imread("./建筑物.jpg", 0)

    # 执行傅里叶变换，将图像从空间域转换到频域
    f = np.fft.fft2(img)

    # 为了便于观察频域，低频部分默认位于左上角，使用fftshift将低频信息移动到图像中心
    fshift = np.fft.fftshift(f)

    # 获取图像的行数和列数
    rows, cols = img.shape
    crows, ccols = int(rows / 2), int(cols / 2)

    # 创建高通滤波器，通过将频域的低频部分设为0，达到去除低频信息的效果
    fshift[crows - 30:crows + 30, ccols - 30:ccols + 30] = 0  # 设置中心区域为0，即去除低频

    # 将频域的低频部分移回左上角，准备做逆傅里叶变换
    ifshift = np.fft.ifftshift(fshift)

    # 执行逆傅里叶变换，将频域信号转换回空间域
    iimg = np.fft.ifft2(ifshift)

    # 获取逆傅里叶变换的绝对值结果，因为傅里叶变换返回的是复数，取其幅值
    iimg = np.abs(iimg)

    # 绘制原始图像和经过高通滤波后的结果
    plt.subplot(121)
    plt.imshow(img, cmap='gray')  # 显示原始图像
    plt.title('Original Image')  # 标题
    plt.axis('off')  # 关闭坐标轴

    # 显示高通滤波后的图像
    plt.subplot(122)
    plt.imshow(iimg, cmap='gray')  # 显示处理后的图像
    plt.title('High-Pass Filtered Image')  # 标题
    plt.axis('off')  # 关闭坐标轴

    plt.show()  # 显示图片


if __name__ == '__main__':
    main()  # 调用主函数，开始执行
