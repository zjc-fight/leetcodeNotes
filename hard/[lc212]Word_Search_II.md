<!--
 * @Date: 2022-08-07 11:19:02
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-08-07 11:39:58
-->
# 单词搜索2
[https://leetcode.com/problems/word-search-ii/](https://leetcode.com/problems/word-search-ii/)

# 题目描述
```
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

 

Example 1:


Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]
Example 2:


Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []
 

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 104
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.
```

![](https://assets.leetcode.com/uploads/2020/11/07/search1.jpg)![](https://assets.leetcode.com/uploads/2020/11/07/search2.jpg)

# 解题思路
题意是给定一个包含字母的m*n的网格，以及一个字典，需要找出字典中出现在网格中的字符串

首先针对字典构建一个前缀树，便于在网格中搜索。

先从每个网格的字母作为首字母开始搜索，如果该字母出现在前缀树中，如果当前搜索到的字符串还不包含在字典中，则继续检索相邻的四个网格；如果已搜索到的字符串出现在字典中，则找到一个可用的字符串，在继续检索相邻的四个网格。

# 代码实现
```c++
class TrieNode {
public:
    TrieNode() {
        childrens.resize(26);
        isEnd = false;
    }
    
    bool contains(char ch) {
        return childrens[ch-'a'] != nullptr;
    }
    
    TrieNode* get(char ch) {
        return childrens[ch - 'a'];
    }
    
    vector<TrieNode*> childrens;
    bool isEnd;
    
};

class Solution {
public:
    const int direction[5] = {0, 1, 0, -1, 0};
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        rows = board.size(), cols = board[0].size();
        TrieNode* root = new TrieNode();
        for (auto word : words) {
            TrieNode* node = root;
            for (auto ch : word) {
                if (!(node->contains(ch))) {
                    node->childrens[ch-'a'] = new TrieNode();
                }
                node = node->get(ch);
            }
            node->isEnd = true;
        }
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<string> ans;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                string temp = "";
                if (root->contains(board[i][j])) {
                    visited[i][j] = true;
                    temp += board[i][j];
                    backtrace(board, i, j, ans, visited, root->get(board[i][j]), temp);
                    visited[i][j] = false;
                }
            }
        }
        return ans;
    }
    
    void backtrace(vector<vector<char>>& board, int i, int j, vector<string>& ans, vector<vector<bool>>& visited, TrieNode* node, string cur_str) {
        if (node->isEnd) {
            if (find(ans.begin(), ans.end(), cur_str) == ans.end()) {
                ans.push_back(cur_str);
            }
        }
        for (int x = 0; x < 4; ++x) {
            int next_i = i + direction[x], next_j = j + direction[x+1];
            if (valid(board, next_i, next_j, node) && !visited[next_i][next_j]) {
                visited[next_i][next_j] = true;
                TrieNode* next_node = node->get(board[next_i][next_j]);
                backtrace(board, next_i, next_j, ans, visited, next_node, cur_str+board[next_i][next_j]);
                visited[next_i][next_j] = false;
            }
        }
        return;
    }
    
    bool valid(vector<vector<char>>& board, int i, int j, TrieNode* node) {
        if (i < 0 || i >= rows || j < 0 || j >= cols)   return false;
        if (node->contains(board[i][j]))    return true;
        return false;
    }
    
private:
    int rows, cols;
};
```
