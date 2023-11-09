class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int n = citations.size();
        int ans = -1;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, min(citations[i], n - i));
        }
        return ans;
    }
};