<!--
 * @Date: 2022-07-25 18:41:35
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-07-25 19:24:20
-->
# 合并k个有序链表
[https://leetcode.com/problems/merge-k-sorted-lists/](https://leetcode.com/problems/merge-k-sorted-lists/)

# 题目描述
```
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 

Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
Example 2:

Input: lists = []
Output: []
Example 3:

Input: lists = [[]]
Output: []
 

Constraints:

k == lists.length
0 <= k <= 104
0 <= lists[i].length <= 500
-104 <= lists[i][j] <= 104
lists[i] is sorted in ascending order.
The sum of lists[i].length will not exceed 104.
```

# 解题思路
这道题是【合并两个有序链表】的加强版，所以可以沿用合并两个链表的解法，使用分治策略来扩展到k个有序链表的合并;
还有一种方式是基于【小根堆】来做，将每个链表的第一个元素丢进【小根堆】中，每次取出堆顶的元素，然后将下一个元素放进堆中，知道堆为空。


# 代码实现

## 分治策略

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if (n == 0) return nullptr;
        return mergeKLists(lists, 0, n-1);
    }
    
    ListNode* mergeKLists(vector<ListNode*>& lists, int l, int r) {
        if (r - l <= 0) return lists[l];
        int m = l + (r - l) / 2;
        return merge2SortedLists(mergeKLists(lists, l, m), mergeKLists(lists, m+1, r));
    }
    
    ListNode* merge2SortedLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode();
        ListNode* prev = head;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                prev->next = l1;
                l1 = l1->next;
            } else {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }
        if (l1 != nullptr) {
            prev->next = l1;
        } else if (l2 != nullptr) {
            prev->next = l2;
        }
        return head->next;
    }
};
```

## 基于优先队列实现

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
class CustomComparison {
public:
    bool operator() (ListNode* lhs, ListNode* rhs) const {
        return lhs->val > rhs->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        priority_queue<ListNode*, vector<ListNode*>, CustomComparison> pq;
        for (int i = 0; i < n; ++i) {
            if (lists[i] != nullptr) {
                pq.push(lists[i]);
            }
        }
        ListNode* head = new ListNode();
        ListNode* prev = head;
        while (!pq.empty()) {
            ListNode* top = pq.top();
            prev->next = top;
            pq.pop();
            if (top->next != nullptr) {
                pq.push(top->next);
            }
            prev = prev->next;
        }
        return head->next;
    }
};
```