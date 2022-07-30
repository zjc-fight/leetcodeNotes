<!--
 * @Date: 2022-07-30 21:35:26
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-30 21:45:20
-->
# 0-1矩阵中的最大矩形
[https://leetcode.com/problems/maximal-rectangle/](https://leetcode.com/problems/maximal-rectangle/)

# 题目描述
```
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

Example 1:


Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.
Example 2:

Input: matrix = [["0"]]
Output: 0
Example 3:

Input: matrix = [["1"]]
Output: 1
 

Constraints:

rows == matrix.length
cols == matrix[i].length
1 <= row, cols <= 200
matrix[i][j] is '0' or '1'.
``` 
![example1](https://assets.leetcode.com/uploads/2020/09/14/maximal.jpg "example1 图片")

# 解题思路

本题是求0-1矩阵中，由1组成的最大矩阵的面积

稍加思考一下，可以看出本题和[柱状图中的最大矩形面积](%5Blc84%5DLargest_Rectangle_in_Histogram.md)类似，只需要遍历每一行，得到一个对应的heights数组，然后应用单调栈求解即可。

# 代码实现
```c++
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<int> heights(cols+1, 0);
        heights[cols] = -1;
        int ans = 0;
        stack<int> S;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] == '1') {
                    heights[j] += 1;
                } else {
                    heights[j] = 0;
                }
            }
            int j = 0;
            while (j <= cols) {
                if (S.empty() || heights[S.top()] <= heights[j]) {
                    S.push(j++);
                } else {
                    int m = S.top(); S.pop();
                    int left = S.empty() ? -1 : S.top();
                    int area = heights[m] * (j - left - 1);
                    ans = max(ans, area);
                }
            }
            S.pop();
        }
        return ans;
    }
};
```