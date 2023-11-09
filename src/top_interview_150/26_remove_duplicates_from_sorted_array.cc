class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();
        int prev = 0, i = 1;
        while (i < len) {
            if (nums[prev] != nums[i]) {
                nums[++prev] = nums[i];
            }
            i++;
        }
        return prev+1;
    }
};