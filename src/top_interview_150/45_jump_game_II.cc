class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        dp[n-1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 1; j <= nums[i] && i + j < n; ++j) {
                if (dp[i + j] < 0)    continue;
                if (dp[i] < 0) {
                    dp[i] = dp[i+j]+1;
                } else {
                    dp[i] = min(dp[i], dp[i+j]+1);
                }
            }
        }
        return dp[0];
    }
};