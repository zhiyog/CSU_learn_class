import cv2
import numpy as np


# 高斯加噪函数
def add_gaussian_noise(image, mean=0, std_dev=20):
    """
    对图像添加高斯噪声
    :param image: 输入图像
    :param mean: 高斯噪声的均值
    :param std_dev: 高斯噪声的标准差
    :return: 添加噪声后的图像
    """
    noise = np.random.normal(mean, std_dev, image.shape).astype(np.float32)
    noisy_image = cv2.add(image.astype(np.float32), noise)
    return np.clip(noisy_image, 0, 255).astype(np.uint8)


# 算术均值滤波
def arithmetic_mean_filter(image, kernel_size=3):
    """
    算术均值滤波
    :param image: 输入图像
    :param kernel_size: 滤波器的大小
    :return: 滤波后的图像
    """
    return cv2.blur(image, (kernel_size, kernel_size))


# 几何均值滤波
def geometric_mean_filter(image, kernel_size=3):
    """
    几何均值滤波
    :param image: 输入图像
    :param kernel_size: 滤波器的大小
    :return: 滤波后的图像
    """
    image = image.astype(np.float32) + 1  # 避免对零取对数
    log_image = np.log(image)
    kernel = np.ones((kernel_size, kernel_size), dtype=np.float32) / (kernel_size * kernel_size)
    log_filtered = cv2.filter2D(log_image, -1, kernel)
    geo_mean = np.exp(log_filtered) - 1
    return np.clip(geo_mean, 0, 255).astype(np.uint8)


# 自适应均值滤波
def adaptive_mean_filter(image, kernel_size=3):
    """
    高效实现自适应均值滤波
    :param image: 输入图像
    :param kernel_size: 滤波器的大小
    :return: 滤波后的图像
    """
    kernel = np.ones((kernel_size, kernel_size), dtype=np.float32) / (kernel_size * kernel_size)
    return cv2.filter2D(image, -1, kernel)


# 主流程
if __name__ == "__main__":
    # 读取图像
    image = cv2.imread('image.png', cv2.IMREAD_GRAYSCALE)

    # 检查图像是否成功加载
    if image is None:
        print("图像加载失败，请检查文件路径！")
        exit()

    # 添加高斯噪声
    noisy_image = add_gaussian_noise(image)

    # 应用滤波方法
    arithmetic_filtered = arithmetic_mean_filter(noisy_image)
    geometric_filtered = geometric_mean_filter(noisy_image)
    adaptive_filtered = adaptive_mean_filter(noisy_image)

    # 保存结果图像
    cv2.imwrite("noisy_image.jpg", noisy_image)
    cv2.imwrite("arithmetic_filtered.jpg", arithmetic_filtered)
    cv2.imwrite("geometric_filtered.jpg", geometric_filtered)
    cv2.imwrite("adaptive_filtered.jpg", adaptive_filtered)

    # 显示结果
    cv2.imshow("Original", image)
    cv2.imshow("Noisy Image", noisy_image)
    cv2.imshow("Arithmetic Mean Filtered", arithmetic_filtered)
    cv2.imshow("Geometric Mean Filtered", geometric_filtered)
    cv2.imshow("Adaptive Mean Filtered", adaptive_filtered)

    cv2.waitKey(0)
    cv2.destroyAllWindows()
