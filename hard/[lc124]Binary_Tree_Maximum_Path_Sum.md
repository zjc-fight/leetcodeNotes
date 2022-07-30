<!--
 * @Date: 2022-07-30 22:06:49
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-30 22:20:40
-->
# 求二叉树的最大路径和
[https://leetcode.com/problems/binary-tree-maximum-path-sum/](https://leetcode.com/problems/binary-tree-maximum-path-sum/)

# 题目描述
```
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any non-empty path.

 

Example 1:


Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
Example 2:


Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 

Constraints:

The number of nodes in the tree is in the range [1, 3 * 104].
-1000 <= Node.val <= 1000
```
![](https://assets.leetcode.com/uploads/2020/10/13/exx1.jpg)![](https://assets.leetcode.com/uploads/2020/10/13/exx2.jpg)


# 解题思路
二叉树相关的题应该最先想到递归方法求解，本题是要求出二叉树中的最大路径和，针对root结点的树来说，最大路径和有三种情况：
- 最大路径和出现在左子树。
- 最大路径和出现在右子树。
- 最大路径和包括root结点。此时需要知道左右子树到其后代结点的最大路径和
所以可以直接递归求解左右子树，返回左右子树中的最大路径和以及左右子节点到其孩子结点的最大路径和

# 代码实现
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        return maxPathSumTuple(root).first;
    }
    pair<int, int> maxPathSumTuple(TreeNode* root) {
        if (root == nullptr)    return pair<int, int>(INT_MIN, 0);
        pair<int, int> left = maxPathSumTuple(root->left);
        pair<int, int> right = maxPathSumTuple(root->right);
        int max_height_sum = root->val + max(max(left.second, right.second), 0);
        int max_path_sum = max(max(left.first, right.first), root->val + max(0, left.second) + max(0, right.second));
        return pair<int, int>(max_path_sum, max_height_sum);
    }
};
```