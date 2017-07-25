/*
leetcode 78
求一个集合的所有子集
思路：
用一个数的二进制形式来表达子集合的元素
注意：
c++ 的 bitset 初始化长度必须是常量 
*/

class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
      vector<vector<int>> ret;
      int n = nums.size();
      int set_b = 0;
      long tar = 1 << n;
      for (int set_b = 0; set_b < tar; set_b++) {
        bitset<128> b(set_b);
        vector<int> subset_v;
        for (int i = 0; i < n; i++) {
          if (b[i]) {
            subset_v.push_back(nums[i]);
          }
        }
        ret.push_back(subset_v);
      }
      return ret;
  }
};