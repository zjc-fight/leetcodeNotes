<!--
 * @Date: 2022-07-29 09:01:31
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-29 09:17:42
-->
# 柱状图中最大的矩形
[https://leetcode.com/problems/largest-rectangle-in-histogram/](https://leetcode.com/problems/largest-rectangle-in-histogram/)

# 题目描述
```
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.


Example 1:

Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:

Input: heights = [2,4]
Output: 4
 

Constraints:

1 <= heights.length <= 105
0 <= heights[i] <= 104
```
![example1](https://assets.leetcode.com/uploads/2021/01/04/histogram.jpg)![example2](https://assets.leetcode.com/uploads/2021/01/04/histogram-1.jpg)

# 解题思路
题意是给定一个柱状图，每个柱子的宽度为1，需找出由柱子组成的面积最大的矩形。

如果以height[i]为矩形中的最小高度的柱子，那么就需要求出左边第一个比height[i]小的柱子p、右边第一个比height[i]小的柱子q，则矩形的面积为height[i] * (q - p - 1)。因此只需遍历柱状图中的每一个柱子，然后求出对应的p、q，选择其中面积最大的柱子即可。

针对这种问题，可以用单调栈（单调递增）来求解：
- 如果当前遍历到的柱子i比栈顶的柱子大，则把i压入栈中，继续遍历下一根柱子
- 如果当前遍历到的柱子i比栈顶的柱子小，则找到了右边第一个比栈顶柱子小的柱子，则以栈顶柱子center为矩形的最小高度，栈中的下一个元素left为左边第一个比center矮的柱子，弹出栈顶元素center，求出当前矩形面积heights[center]*(i-left-1)


# 代码实现
```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(-1);   // 末尾加一个哨兵，保证栈内所有元素都能被弹出
        int n = heights.size();
        stack<int> st;
        int ans = 0, i = 0;
        while (i < n) {
            if (st.empty() || heights[i] >= heights[st.top()]) {
                st.push(i++);
            } else if (heights[i] < heights[st.top()]) {
                int center = st.top();              // 以center作为最矮柱子，组成矩形
                st.pop();
                int left = st.empty() ? -1 : st.top();       // 左边第一个比center矮的柱子
                int area = heights[center] * (i - left - 1);
                ans = max(ans, area);
            } else {
                i++;
            }
        }
        return ans;
    }
};
```