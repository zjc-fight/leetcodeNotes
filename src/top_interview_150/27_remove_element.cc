class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = nums.size();
        int i = 0, j = len - 1;
        while (i <= j) {
            if (nums[i] == val) {
                swap(nums[i], nums[j--]);
            } else {
                i++;
            }
        }
        return j+1;
    }
};