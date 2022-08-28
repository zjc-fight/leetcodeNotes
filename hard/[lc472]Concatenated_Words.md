# 单词拼接
[https://leetcode.com/problems/concatenated-words/](https://leetcode.com/problems/concatenated-words/)

# 题目描述
```
Given an array of strings words (without duplicates), return all the concatenated words in the given list of words.

A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.


Example 1:

Input: words = ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]
Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]
Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
"dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".

Example 2:

Input: words = ["cat","dog","catdog"]
Output: ["catdog"]
 

Constraints:

1 <= words.length <= 104
1 <= words[i].length <= 30
words[i] consists of only lowercase English letters.
All the strings of words are unique.
1 <= sum(words[i].length) <= 105
```

# 解题思路
题意是给了一个单词列表，需要找出这个列表中满足要求的所有单词，这些单词都是由两个或两个以上列表中其他单词组成的。

如果对前缀树比较了解的话，这道题解起来就比较容易了。首先可以对单词列表构造一颗前缀树，然后对列表中的每个单词都在前缀树中搜寻一遍，就可以快速找到这个单词可以由哪些其他单词连接而成的。

这道题需要注意的点在于，在前缀树搜索单词时，当找到一个单词分割点时，需要考虑断开和不断开两种情形。

# 代码实现
```c++
class TrieNode {
public:
    vector<TrieNode*> children;
    bool is_word;
    TrieNode() {
        children = vector<TrieNode*>(26, nullptr);
        is_word = false;
    }
    
    bool hasChild(char ch) {
        return children[ch-'a'] != nullptr;
    }
    
    TrieNode* getChild(char ch) {
        return children[ch-'a'];
    }
    
    void setChild(char ch, TrieNode* node) {
        children[ch-'a'] = node;
    }
};

class Solution {
public:
    TrieNode* root;
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        root = new TrieNode();
        // 构造前缀树
        for (string& word : words) {
            TrieNode* curNode = root;
            for (char c: word) {
                if (!curNode->hasChild(c)) {
                    TrieNode* newNode = new TrieNode();
                    curNode->setChild(c, newNode);
                }
                curNode = curNode->getChild(c);
            }
            curNode->is_word = true;
        }
        vector<string> ans;
        for (string& word : words) {
            recurse(word, 0, 0, root, ans);
        }
        return ans;
    }
    
    void recurse(string& word, int index, int wordCnt, TrieNode* node, vector<string>& ans) {
        if (index == word.length()) {
            if (wordCnt > 0 && node->is_word) {
                if (find(ans.begin(), ans.end(), word) == ans.end()) {
                    ans.push_back(word);
                }
            }
            return;
        }
        if (node->is_word) {  // 找到单词分割点，执行断开的情绪
            recurse(word, index, wordCnt+1, root, ans);
        }
        // 单词不分割
        if (node->hasChild(word[index])) {
            recurse(word, index+1, wordCnt, node->getChild(word[index]), ans);
        }
    }
};
```