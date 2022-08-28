<!--
 * @Date: 2022-08-28 19:29:05
 * @LastEditors: zhangjiuchao zhangjiuchao@bytedance.com
 * @LastEditTime: 2022-08-28 19:35:47
-->
二分查找算法
=======================

# 算法简介
二分查找算法又叫折半查找算法,使用该算法的要求是数据结构是有序的,二分查找算法可以保证在数据规模的对数时间内完成。二分查找算法要求线性表具有随机访问的特点(例如数组），并且能够通过中间元素推测两边元素的状态，以达到缩减数据规模的目的。

# 算法思路
1. 首先确定数组中间元素的下标，mid = (left + right)/2。
2. 将要查找的数target与arr[mid]进行比较
- 如果arr[mid] < target，表示要查找的数在mid的右边，令left = mid + 1。
- 如果arr[mid] > target, 表示要查找的数在mid的左边，令right = mid - 1。
- 如果arr[mid] == target，说明已经找到了要找的值，mid就是要找的值的下标，直接返回mid。
3. 重复步骤1和2，如果出现left > right, 说明数组中不存在要找的数，返回-1。


