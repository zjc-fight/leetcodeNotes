<!--
 * @Date: 2022-08-20 18:14:17
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-08-20 22:09:15
-->
# 删除无效的括号
[https://leetcode.com/problems/remove-invalid-parentheses/](https://leetcode.com/problems/remove-invalid-parentheses/)

# 题目描述
```
Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return all the possible results. You may return the answer in any order.

Example 1:

Input: s = "()())()"
Output: ["(())()","()()()"]

Example 2:

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]

Example 3:

Input: s = ")("
Output: [""]
 

Constraints:

1 <= s.length <= 25
s consists of lowercase English letters and parentheses '(' and ')'.
There will be at most 20 parentheses in s.
```

# 解题思路
题意是给一个包含'('、')'和其他字符的字符串，需要删除最少数目的'('和')'，形成一个合法的字符串，即'('、')'能够匹配。

我的思路是采用回溯法，对每一个'('、')'都有删除和保留两种操作，从而形成一棵搜索树，在最后判断得到的字符串是否合法即可。这种朴素的方法时间复杂度$O(2^N)$，需要进行一些优化，在搜索的过程中进行剪枝。

1. 因为是删除最少的'('、')'，可以对字符串进行预处理，找出需要删除的'('、')'的最小个数，记为leftRem、rightRem。并得到字符串中每个'('右边是否含有')'。
2. 当遇到'('或')'时，如果此时删除的括号数已达到leftRem或rightRem，则该括号必须要保留，否则可以删除。
3. 当遇到'('时，如果右边没有')'了，则该括号不能保留。
4. 当遇到')'时，如果已经保留的')'数已经大于或等于'('，则该括号不能保留。

# 代码实现
```c++
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int left = 0, right = 0;
        for (auto ch : s) {
            if (ch == '(') {
                left++;
            } else if (ch == ')') {
                right = left == 0 ? right + 1 : right;
                left = left > 0 ? left - 1 : left;
            }
        }
        int n = s.length(), t = 0;
        remainRight.resize(n);
        for (int i = n - 1; i >= 0; --i) {
            remainRight[i] = t;
            if (s[i] == ')')    t++;
        }
        
        vector<string> ans;
        recurse(s, 0, 0, 0, left, right, "", ans);
        return ans;
    }
    
    void recurse(string s, int index, int leftCount, int rightCount, int leftRem, int rightRem, string express, vector<string>& ans) {
        if (index == s.length()) {
            if (leftRem == 0 && rightRem == 0) {
                if (find(ans.begin(), ans.end(), express) == ans.end()) {
                    ans.push_back(express);
                }
            }
        } else {
            if ((s[index] == '(' && leftRem > 0) || (s[index] == ')' && rightRem > 0)) {
                recurse(s, index+1, leftCount, rightCount, 
                        leftRem - (s[index] == '(' ? 1 : 0),
                        rightRem - (s[index] == ')' ? 1 : 0), 
                        express, ans);
            }
            if (s[index] != '(' && s[index] != ')') {
                recurse(s, index+1, leftCount, rightCount, leftRem, rightRem, 
                        express + s[index], ans);
            } else if (s[index] == '(' && remainRight[index] > 0) {
                recurse(s, index+1, leftCount + 1, rightCount, leftRem, rightRem,
                        express + s[index], ans);
            } else if (s[index] == ')' && rightCount < leftCount) {
                recurse(s, index+1, leftCount, rightCount + 1, leftRem, rightRem,
                        express + s[index], ans);
            }
        }
    }
private:
    vector<int> remainRight;
};
```
