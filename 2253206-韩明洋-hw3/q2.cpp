#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <numeric>
using namespace std;

bool canPartition(vector<int>& nums) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if (total % 2 != 0) return false;
    
    int target = total / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    
    for (int num : nums) {
        for (int j = target; j >= num; --j) {
            if (dp[j - num]) {
                dp[j] = true;
            }
        }
    }
    return dp[target];
}

int main() {
    cout << "===== 分割等和子集 =====" << endl;
    cout << "请输入整数数组（空格分隔，如：1 5 11 5）: ";
    
    string input;
    getline(cin, input);
    
    vector<int> nums;
    istringstream iss(input);
    int num;
    while (iss >> num) {
        nums.push_back(num);
    }
    
    if (nums.empty()) {
        cout << "错误：数组不能为空！" << endl;
        return 1;
    }
    
    bool result = canPartition(nums);
    cout << "是否可以分割成两个等和子集: " << (result ? "true" : "false") << endl;
    
    if (result) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int target = total / 2;
        
        // 正确的方法：使用二维DP记录路径
        vector<vector<bool>> dp(nums.size() + 1, vector<bool>(target + 1, false));
        vector<vector<bool>> selected(nums.size() + 1, vector<bool>(target + 1, false));
        
        // 初始化
        for (int i = 0; i <= nums.size(); i++) {
            dp[i][0] = true;
        }
        
        // 填充DP表
        for (int i = 1; i <= nums.size(); i++) {
            for (int j = 1; j <= target; j++) {
                if (j >= nums[i-1]) {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i-1]];
                    if (dp[i-1][j - nums[i-1]]) {
                        selected[i][j] = true;
                    }
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        
        // 回溯查找分割方案
        vector<int> subset1, subset2;
        int j = target;
        for (int i = nums.size(); i > 0; i--) {
            if (selected[i][j]) {
                subset1.push_back(nums[i-1]);
                j -= nums[i-1];
            } else {
                subset2.push_back(nums[i-1]);
            }
        }
        
        cout << "分割方案: ";
        cout << "[";
        for (size_t i = 0; i < subset1.size(); i++) {
            cout << subset1[i];
            if (i < subset1.size() - 1) cout << ", ";
        }
        cout << "] 和 [";
        for (size_t i = 0; i < subset2.size(); i++) {
            cout << subset2[i];
            if (i < subset2.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    return 0;
}