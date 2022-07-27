<!--
 * @Date: 2022-07-25 20:26:58
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-25 20:40:58
-->
# k个一组翻转链表
[https://leetcode.com/problems/reverse-nodes-in-k-group/](https://leetcode.com/problems/reverse-nodes-in-k-group/)


# 题目描述
```
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

 

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]

Example 2:
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]
 

Constraints:

The number of nodes in the list is n.
1 <= k <= n <= 5000
0 <= Node.val <= 1000
```

# 解题思路
题目要求是按k个一组对链表进行翻转，当链表剩余个数不到k个时，则不进行翻转。

可以对链表进行扫描，当扫描到第k个时，对已扫描的k个结点进行常规的链表翻转，然后继续对余下节点进行递归翻转，并将返回的链表链接到前k个结点组成的翻转链表末尾；如果没扫描到第k个，代表已到达链表末尾，则已扫描的节点不进行翻转，直接返回。


# 代码实现
```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr)    return head;
        
        int i;
        ListNode* cur = head;
        for (i = 0; i < k && cur != nullptr; ++i) {
            cur = cur->next;
        }
        if (i < k)  return head;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        ListNode* tail = nullptr;
        cur = head;
        for (i = 0; i < k; ++i) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
            if (i == 0)  tail = prev;
        }
        if (tail != nullptr) {
            tail->next = reverseKGroup(cur, k);
        }
        return prev;
    }
};
```