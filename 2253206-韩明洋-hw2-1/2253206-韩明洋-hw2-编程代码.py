def calculate_structure_degree(image, x, y, size):
    """
    递归计算图像的结构度
    :param image: 图像矩阵
    :param x: 当前子图像的左上角横坐标
    :param y: 当前子图像的左上角纵坐标
    :param size: 当前子图像的边长
    :return: 当前子图像的结构度
    """
    # 如果子图像只有一个像素点，结构度为1
    if size == 1:
        return 1

    # 检查当前子图像的所有像素是否相同
    first_pixel = image[x][y]
    all_same = True
    for i in range(x, x + size):
        for j in range(y, y + size):
            if image[i][j] != first_pixel:
                all_same = False
                break
        if not all_same:
            break

    # 如果所有像素相同，结构度为1
    if all_same:
        return 1

    # 如果像素不相同，将子图像分为四个更小的子图像，递归计算
    sub_size = size // 2
    structure_degree = (
        calculate_structure_degree(image, x, y, sub_size) +
        calculate_structure_degree(image, x, y + sub_size, sub_size) +
        calculate_structure_degree(image, x + sub_size, y, sub_size) +
        calculate_structure_degree(image, x + sub_size, y + sub_size, sub_size)
    )

    # 当前子图像的结构度为四个子图像的结构度之和加1
    return structure_degree + 1


def main():
    # 输入图像大小 N
    N = int(input("请输入图像大小 N（必须是2的幂）："))
    if N <= 0 or (N & (N - 1)) != 0:
        print("输入的 N 不是2的幂！")
        return

    # 输入图像矩阵
    print(f"请输入 {N}x{N} 的图像矩阵（0表示黑色，1表示白色）：")
    image = []
    for _ in range(N):
        row = list(map(int, input().split()))
        if len(row) != N:
            print(f"输入的行长度不正确，应为 {N}！")
            return
        image.append(row)

    # 计算并输出图像的结构度
    structure_degree = calculate_structure_degree(image, 0, 0, N)
    print(f"图像的结构度为：{structure_degree}")


if __name__ == "__main__":
    main()