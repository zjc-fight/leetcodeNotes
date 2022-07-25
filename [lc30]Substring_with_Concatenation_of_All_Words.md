<!--
 * @Date: 2022-07-25 23:14:02
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-25 23:35:40
-->
# 串联所给单词组成的子串
[https://leetcode.com/problems/substring-with-concatenation-of-all-words/](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)

# 题目描述
```
You are given a string s and an array of strings words of the same length. Return all starting indices of substring(s) in s that is a concatenation of each word in words exactly once, in any order, and without any intervening characters.

You can return the answer in any order.

 

Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.

Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []

Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
 

Constraints:

1 <= s.length <= 104
1 <= words.length <= 5000
1 <= words[i].length <= 30
s and words[i] consist of lowercase English letters.
```

# 解题思路
题目给了一个字符串$s$和一个包含相同长度字符串的字典$words$，要求找出$s$中由$words$中单词组成的子串的起始位置。

可以采用滑动窗口的形式进行统计，假设滑动窗口为[left, right]，每次从right开始截取一个长度为wordLength（wordLength为字典中单词的长度）的子串s1，如果s1出现在字典中，且使用次数没超过它在字典中出现的次数，则以步长wordLenth移动right指针，否则以步长wordLength移动left指针；否则，将left直接移到right，重新开始统计。


# 代码实现
```c++
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        n = s.size();
        wordLength = words[0].size();
        wordNum = words.size();
        substringLength = wordLength * wordNum;
        for (string& word : words)  wordCount[word] += 1;
        vector<int> ans;
        for (int i = 0; i < wordLength; ++i) {
            slidingWindow(s, i, ans);
        }
        return ans;
    }
    
    void slidingWindow(string s, int left, vector<int>& ans) {
        int wordUsed = 0;
        bool excess_word = false;
        unordered_map<string, int> wordFound;
        for (int right = left; right <= n - wordLength; right += wordLength) {
            string sub = s.substr(right, wordLength);
            if (wordCount.find(sub) == wordCount.end()) { // sub不在字典中
                wordFound.clear();
                left = right + wordLength;
                excess_word = false;
                wordUsed = 0;
            } else {
                while (right - left == substringLength || excess_word) {   // 如果已经遍历到的字串长度等于substringLength，或者存在多余的可用单词，需要丢弃最左边的单词
                    string leftmostWord = s.substr(left, wordLength);
                    left = left + wordLength;
                    wordFound[leftmostWord] -= 1;
                    if (wordFound[leftmostWord] == wordCount[leftmostWord]) {
                        excess_word = false;
                    } else {
                        wordUsed--;
                    }
                }
                wordFound[sub] += 1;
                if (wordFound[sub] > wordCount[sub]) {
                    excess_word = true;
                } else {
                    wordUsed++;
                }
                if (wordUsed == wordNum && !excess_word) {
                    ans.push_back(left);
                }
            }
        }
    }
private:
    int n;
    int wordLength;
    int wordNum;
    int substringLength;
    unordered_map<string, int> wordCount;
};
```
