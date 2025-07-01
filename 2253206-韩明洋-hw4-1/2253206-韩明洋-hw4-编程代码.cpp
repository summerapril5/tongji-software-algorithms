#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

// 计算直方图最大矩形面积
int getMaxArea(vector<int> heights) {
    heights.push_back(0); // 添加哨兵值
    stack<int> st;
    int maxArea = 0;
    for (int i = 0; i < heights.size(); i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()]; // 当前高度
            st.pop();
            int left = st.empty() ? -1 : st.top(); // 左边界
            int width = i - left - 1; // 宽度
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    return maxArea;
}

int main() {
    int m, n;
    cin >> m >> n;

    // 读取矩阵
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    vector<int> height(n, 0); // 高度数组
    int maxArea = 0;

    // 遍历每一行
    for (int i = 0; i < m; i++) {
        // 更新高度数组
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                height[j] += 1;
            } else {
                height[j] = 0;
            }
        }
        // 计算当前行最大矩形面积
        maxArea = max(maxArea, getMaxArea(height));
    }

    cout << maxArea << endl;
    return 0;
}