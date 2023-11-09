class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int len = prices.size();
        if (len <= 1)
            return 0;
        int minimum = 0, maxprofit = 0;
        if (prices[0] <= prices[1])
        {
            minimum = prices[0];
        }
        for (int i = 1; i < len; ++i)
        {
            // peek
            if (prices[i] > prices[i - 1] &&
                (i == len - 1 || prices[i] >= prices[i + 1]))
            {
                maxprofit += (prices[i] - minimum);
            } else if (prices[i] <= prices[i - 1]) {
                minimum = prices[i];
            }
        }
        return maxprofit;
    }
};