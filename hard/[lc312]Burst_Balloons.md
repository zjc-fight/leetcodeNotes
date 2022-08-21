# 戳气球
[https://leetcode.com/problems/burst-balloons/](https://leetcode.com/problems/burst-balloons/)

# 题目描述
```
You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

 

Example 1:

Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
Example 2:

Input: nums = [1,5]
Output: 10
 

Constraints:

n == nums.length
1 <= n <= 300
0 <= nums[i] <= 100
```

# 解题思路
题意是给了一串相邻的气球，每个气球代表对应的数字，需要依次戳破所有的气球，拿到最大的分数，每次戳破一个气球，能到到分数nums[i-1]\*nums[i]\*nums[i+1]。

看到这道题最朴素的方法便是回溯法，每次都可以选择其中任意一个气球戳破，直到戳破所有的气球，得到一种戳破气球的顺序，最后在所有方法中选择得分最大的。简单的回溯法时间复杂度太高，没办法accept。尝试画出搜索树，可以看出含有大量的重复计算。

由此，可以看出本题包含最优子结构，能尝试动态规划方法求解，定义dp[i][j]表示戳破i和j之间的所有气球的最大得分（不包括i，j），假设$k \in (i,j)$是最后一个戳破的气球，则$dp[i][j] = max(dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j])$

在nums首位各插入数字1，则最终结果为dp[0][n-1].

# 代码实现
```c++
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> dp(n+2, vector<int>(n+2));
        for (int l = 2; l < n+2; ++l) {
            for (int i = 0; i < n+2-l; ++i) {
                int j = i + l;
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j]);
                }
            }
        }
        return dp[0][n+1];
    }
};
```