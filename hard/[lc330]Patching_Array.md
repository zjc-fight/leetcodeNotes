<!--
 * @Date: 2022-08-21 16:15:36
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-08-21 16:33:51
-->
# 按要求补齐数组
[https://leetcode.com/problems/patching-array/](https://leetcode.com/problems/patching-array/)

# 题目描述
```
Given a sorted integer array nums and an integer n, add/patch elements to the array such that any number in the range [1, n] inclusive can be formed by the sum of some elements in the array.

Return the minimum number of patches required.

 

Example 1:

Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.
Example 2:

Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].
Example 3:

Input: nums = [1,2,2], n = 5
Output: 0
 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 104
nums is sorted in ascending order.
1 <= n <= 231 - 1
```

# 解题思路
题目给了一个数组nums和一个数字n，要求向数组里面加入一些数字，使得[1,n]之前都数都能有数组nums的数字加和得到，求最少需要加入多少个数字。

这道题利用贪心算法求解，考虑没有数字缺失的情况：

数组[1] 能覆盖[1,1]；数字[1,2]能覆盖[1,3]；数组[1,2,3]能覆盖[1,6];数组[1,2,3,4]能覆盖[1,10];以此类推，没有数字缺失的情况下，数组能覆盖到的最远距离（最大数字）为数字所有元素之和。

接下来考虑有数字缺失的情况，因为数组是增序排列的，可以遍历数组，逐渐扩充数组能覆盖的最远距离furthest：
1. 如果数字nums[i] <= furthest + 1，则表示不需要增加新的数字就可以继续扩大覆盖的区间，最远距离延伸到furthest + nums[i]
2. 如果数字nums[i] > furthest + 1，则代表furthest + 1不能被覆盖，需要增加数组furthest + 1，然后最远距离就可以延伸到furthest * 2 + 1;

# 代码实现
```c++
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        int len = nums.size();
        int ans = 0, i = 0;
        long long furthest = 0;
        while (furthest < n) {
            if (i < len && nums[i] <= futhest + 1) {
                furthest += nums[i++];
            } else {
                futhest += (furthest + 1);
                ans ++;
            }
        }
        return ans;
    }
};
```