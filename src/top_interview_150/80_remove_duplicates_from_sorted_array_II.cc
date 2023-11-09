class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        if (len <= 2)   return len;
        int prev = 1, i = 2;
        while (i < len) {
            if (nums[prev] != nums[i] || nums[prev-1] != nums[i]) {
                nums[++prev] = nums[i];
            }
            i++;
        }
        return prev+1;
    }
};