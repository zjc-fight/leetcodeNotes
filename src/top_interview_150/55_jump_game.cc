class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        int maximum = nums[0];
        for (int i = 1; i < len; ++i) {
            if (maximum < i) return false;
            maximum = max(maximum, i + nums[i]);
        }
        return true;
    }
};