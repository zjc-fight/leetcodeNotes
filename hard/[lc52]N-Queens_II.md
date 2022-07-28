<!--
 * @Date: 2022-07-28 08:39:20
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-28 08:56:08
-->
# N皇后问题
[https://leetcode.com/problems/n-queens-ii/](https://leetcode.com/problems/n-queens-ii/)

# 题目描述
```
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.

 

Example 1:

Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.

Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 9
```
![](https://assets.leetcode.com/uploads/2020/11/13/queens.jpg)

# 解题思路
题意是将n个棋子摆在一个n*n的棋盘上，使得棋子不会互相攻击，即任意两颗棋子不在一条直线或斜线上，求一共有多少种解法

这道题可用**回溯算法**求解，可知每一行只能摆一颗棋子，可以用一个数组position[i]记录第i行棋子的摆放位置，
- 如果第i行的棋子和前i-1行的棋子都不冲突，则第i行的棋子摆放是可用的。如果i == n，则找到一种可用的解法；否则，继续遍历第i+1行棋子的摆放位置。
- 如果第i行的棋子和前i-1行的棋子冲突，则第i行的棋子摆放不可用，继续遍历第i行的下一个摆放位置，如果第i行没有位置可摆了，则需要回溯到i-1行棋子，将i-1行的棋子移到下一个位置。如果没有可回溯的棋子，则算法结束。

# 代码实现
```c++
class Solution {
public:
    int totalNQueens(int n) {
        position = vector<int>(n, -1);
        int k = 0, ans = 0;
        while (k >= 0) {
            position[k] += 1;
            if (position[k] == n) {   // 第k行棋子没有摆放位置了，回溯到上一行
                k--;
                continue;
            }
            if (valid(k)) {     // 第k行棋子的位置和前k-1行棋子没有冲突
                if (k == n - 1) {   // 表示找到其中一种解法
                    ans++;
                } else {        // 从头遍历第k+1行棋子的摆放
                    position[++k] = -1;
                }
            }
        }
        return ans;
    }
    bool valid(int x) {
        for (int i = 0; i < x; ++i) {
            if (position[i] == position[x]) return false;
            if (position[x] - position[i] == x - i ||
                position[x] - position[i] == i - x)
                return false;
        }
        return true;
    }
private:
    vector<int> position;     // 保存n行棋子的摆放位置
};
```