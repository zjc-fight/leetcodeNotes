<!--
 * @Date: 2022-07-27 19:52:05
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-27 20:19:38
-->
# 接雨水问题
[https://leetcode.com/problems/trapping-rain-water/](https://leetcode.com/problems/trapping-rain-water/)

# 题目描述
```
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.

Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9
 

Constraints:

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105
```

# 解题思路
题意是给定一个非负的数组，代表一排柱子的高度图，需求这些柱子组成的凹槽一共可以容纳多少水。

容易看出，每个柱子上方可以容纳水的体积取决于当前柱子的高度height、左边柱子的最大高度left_max和右边柱子的最大高度right_max，当height小于left_max和right_max时，当前柱子容纳的水为min(left_max, right_max) - height。

因此可以用双指针法求解本题，维护左边柱子的最大高度和右边柱子的最大高度，left、right分别代表左右两个指针：
- 当heights[left] <= heights[right]时，则装水的瓶颈在heights[left]，所以先求解hight[left]柱子能装的水：max(left_max - heights[left]， 0)，同时更新left_max=max(left_max, height[left])，并将left右移一位。
- 当heights[left] > heights[right]时，则装水的瓶颈在heights[right]，所以先求解hight[right]柱子能装的水：max(right_max - heights[right]， 0)，同时更新right_max=max(right_max, height[right])，并将right左移一位。

# 代码实现
```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n < 3)  return 0;
        int left_max = 0, right_max = 0;
        int l = 0, r = n - 1, ans = 0;
        while (l < r) {
            if (height[l] <= height[r]) {
                int h = max(left_max - height[l], 0);
                ans += h;
                left_max = max(left_max, height[l++]);
            } else {
                int h = max(right_max - height[r], 0);
                ans += h;
                right_max = max(right_max, height[r--]);
            }
        }
        return ans;
    }
};
```