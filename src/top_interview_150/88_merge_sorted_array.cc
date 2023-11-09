class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int right = m + n - 1;
        int i = m - 1, j = n - 1;
        while (i >= 0 || j >= 0) {
            if (i < 0) {
                nums1[right--] = nums2[j--];
            } else if (j < 0) {
                nums1[right--] = nums1[i--];
            } else if (nums1[i] < nums2[j]) {
                nums1[right--] = nums2[j--];
            } else {
                nums1[right--] = nums1[i--];
            }
        }
        return;
    }
};