#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j * j <= i; ++j) {
            if (dp[i - j * j] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
    }
    return dp[n];
}

int main() {
    int n;
    cout << "===== 完全平方数分割 =====" << endl;
    cout << "请输入正整数 n: ";
    cin >> n;
    
    if (n < 0) {
        cout << "错误：请输入非负整数！" << endl;
        return 1;
    }
    
    int result = numSquares(n);
    cout << "和为 " << n << " 的完全平方数的最少数量: " << result << endl;
    
    // 显示可能的组合
    cout << "可能的组合: ";
    vector<int> squares;
    int remaining = n;
    while (remaining > 0) {
        int max_sq = sqrt(remaining);
        for (int i = max_sq; i >= 1; i--) {
            if (numSquares(remaining) == numSquares(remaining - i*i) + 1) {
                squares.push_back(i*i);
                remaining -= i*i;
                break;
            }
        }
    }
    
    for (size_t i = 0; i < squares.size(); i++) {
        cout << squares[i];
        if (i < squares.size() - 1) cout << " + ";
    }
    cout << endl;
    
    return 0;
}