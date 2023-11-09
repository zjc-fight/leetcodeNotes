class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len = nums.size();
        k = k % len;
        if (k == 0) return;
        // step1 reverse nums[0...len-1]
        int i = 0, j = len - 1;
        while (i < j) {
            swap(nums[i++], nums[j--]);
        }
        // step2 reverse nums[0...k-1]
        i = 0, j = k - 1;
        while (i < j) {
            swap(nums[i++], nums[j--]);
        }
        // step3 reverse nums[k...len-1];
        i = k, j = len - 1;
        while (i < j) {
            swap(nums[i++], nums[j--]);
        }
        return;
    }
};