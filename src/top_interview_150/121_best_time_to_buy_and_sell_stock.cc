class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len <= 1)   return -1;
        int minimum = prices[0], maxprofit = -1;
        for (int i = 1; i < len; ++i) {
            if (prices[i] < minimum) {
                minimum = prices[i];
            } else {
                maxprofit = max(maxprofit, prices[i] - minimum);
            }
        }
        return maxprofit;
    }
};