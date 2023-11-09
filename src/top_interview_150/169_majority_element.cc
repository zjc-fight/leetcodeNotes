class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int len = nums.size();
        int ele = 0, cnt = 0;
        for (int i = 0; i < len; ++i) {
            if (cnt == 0 || nums[i] == ele) {
                ele = nums[i];
                cnt += 1;
            } else {
                cnt -= 1;
            }
        }
        return ele;
    }
};