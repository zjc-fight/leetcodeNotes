<!--
 * @Date: 2022-08-07 12:50:44
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-08-07 15:59:06
-->
# 滑动窗口的最大值
[https://leetcode.com/problems/sliding-window-maximum/](https://leetcode.com/problems/sliding-window-maximum/)

# 题目描述
```
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length
```

# 解题思路
本题给定一个数组**nums**，需要求长度为k的滑动窗口在数组上的最大值

假设滑动窗口在数组上覆盖的区域为[i, j]，只需要维护[i,j]之间数字的递减队列即可，每次窗口的最大值就取队首位置的元素。当滑动窗口向右滑动一位时，如果nums[i]为队首元素时，则删除队首元素，并将nums[j+1]的元素插入队列中，移除队列中比nums[j+1]小的元素，保持队列依然为一个递减队列。

# 代码实现
```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans;
        deque<int> d;
        int i = 0;
        for (int j = 0; j < n; ++j) {
            while (!d.empty() && d.back() < nums[j])    d.pop_back();
            d.push_back(nums[j]);
            if (j - i + 1 == k) {
                ans.push_back(d.front());
                if (d.front() == nums[i])   d.pop_front();
                i++;
            }
        }
        return ans;
    }
};
```