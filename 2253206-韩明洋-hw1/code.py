def combine(n, k):
    def backtrack(start, path):
        if len(path) == k:
            res.append(path.copy())
            return
        for i in range(start, n + 1):
            path.append(i)
            backtrack(i + 1, path)
            path.pop()

    res = []
    backtrack(1, [])
    return res


def main():
    while True:
        try:
            n = int(input("请输入 n 的值（输入 0 退出）："))
            if n == 0:
                print("程序已退出。")
                break
            k = int(input("请输入 k 的值："))
            if k <= 0 or k > n:
                print("k 必须满足 0 < k ≤ n，请重新输入。")
                continue
            result = combine(n, k)
            print(f"所有可能的组合为：{result}")
        except ValueError:
            print("输入无效，请输入整数。")


if __name__ == "__main__":
    main()