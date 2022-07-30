<!--
 * @Date: 2022-07-30 22:47:21
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-30 23:13:51
-->
# 最长连续序列
[https://leetcode.com/problems/longest-consecutive-sequence/](https://leetcode.com/problems/longest-consecutive-sequence/)

# 题目描述
```
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

 

Example 1:

Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
Example 2:

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
 

Constraints:

0 <= nums.length <= 105
-109 <= nums[i] <= 109
```

# 解题思路
本题是要求找出数组中，最长连续序列的长度，并且要求时间复杂度为$O(n)$，即只能遍历一遍数组。

针对数字i，要查找包含数字i的最长连续序列的长度，只需要查看i-1、i+1是否在数组中，然后通过i将包含i-1的连续序列s1、包含i+1的连续序列s2链接起来，由于数字i没有遍历过，所以i-1必为s1的右端点，i+1必为i+1的左端点，所以新连续序列的长度为len(s1) + len(s2) + 1。因此需要一个map，将序列长度保存起来，map[i]表示以i为端点的序列长度：
- 如果i-1、i+1都不存在，则包含i的连续序列长度为1，则map[i] = 1;
- 如果i-1存在、i+1不存在，则包含i的连续序列长度为map[i] = map[i-1] + 1，同时更新s1左结点的长度 map[i - map[i-1]] = map[i-1] + 1
- 如果i-1不存在、i+1存在，则包含i的连续序列长度map[i] = map[i+1] + 1，同时更新s2右结点的长度map[i + map[i+1]] = map[i+1] + 1
- 如果i-1、i+1都存在，则包含i的连续序列长度map[i] = map[i-1] + map[i+1] + 1, 同时更新左右区间结点的长度

# 代码实现
```c++
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return n;
        unordered_map<int, int> um;
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            int num = nums[i];
            if (um.find(num) != um.end()) continue;
            int left = 0, right = 0;
            if (um.find(num-1) != um.end()) {
                left = um[num-1];
            }
            if (um.find(num+1) != um.end()) {
                right = um[num+1];
            }
            int cur_len = left + 1 + right;
            um[num] = cur_len;
            if (left != 0) {
                um[num - left] = cur_len;
            }
            if (right != 0) {
                um[num+right] = cur_len;
            }
            ret = max(ret, cur_len);
        }
        return ret;
    }
};
```
