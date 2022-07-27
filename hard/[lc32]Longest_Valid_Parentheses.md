<!--
 * @Date: 2022-07-27 08:54:58
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-27 09:05:40
-->
# 寻找最长的有效括号子串
[https://leetcode.com/problems/longest-valid-parentheses/](https://leetcode.com/problems/longest-valid-parentheses/)

# 题目描述
```
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

 

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".

Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

Example 3:

Input: s = ""
Output: 0
 

Constraints:

0 <= s.length <= 3 * 104
s[i] is '(', or ')'.
```

# 解题思路
题意是给定一个只包含$($和$)$的字符串，找出其中最长的有效括号的子串。

一般地，如果题目中出现*最长*、*最短*、*最大*等字眼时，那大概率可以用动态规划解决，所以本题也是一道动态规划题。

定义动态规划数组dp，dp[i]代表以s[i]结束的有效括号子串的最大长度，则动态规划的迭代公式：
1. if s[i] == ')' & s[i-1] == '('，则有 dp[i] = dp[i-2] + 2
2. if s[i] == ')' & s[i-1] == ')' & s[i-dp[i-1]-1] == '(', 则 dp[i] = dp[i-1] + 2 + dp[i-dp[i-1]-2]


# 代码实现
```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int max_length = 0;
        vector<int> dp(n, 0);    // 代表以s[i]结束的可用子串
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')') {
                if (s[i-1] == '(') {
                    dp[i] = 2 + (i >= 2 ? dp[i-2]: 0);
                } else if (dp[i-1] > 0 && i - dp[i-1] - 1 >= 0 &&
                           s[i-dp[i-1]-1] == '(') {
                    dp[i] = dp[i-1] + 2 + (i-dp[i-1]-2 > 0 ? dp[i-dp[i-1]-2]: 0);
                }
                max_length = max(max_length, dp[i]);
            }
        }
        return max_length;
    }
};
```

