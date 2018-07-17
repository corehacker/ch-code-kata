#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>

using namespace std;

class Solution {
private:
  int lis(vector<int>& nums, int curr, int start) {
    if(start == nums.size()) return 0;

    cout << "curr: " << curr << ", start: " << start << endl;

    int max = 1;
    for(int i = start; i < nums.size(); i++) {
      if(nums[i] > curr) {
        cout << "nums[i]: " << nums[i] << endl;
        int l = 1 + lis(nums, nums[i], i + 1);
        max = l > max ? l : max;
        cout << "max: " << max << endl;
      }
    }

    // cout << "max: " << max << endl;
    return max;
  }

public:
  int lengthOfLIS(vector<int>& nums) {
    if(!nums.size()) return 0;
    int max = 1;
    for(int i = 0; i < nums.size(); i++) {
      int l = lis(nums, nums[i], i + 1);
      max = l > max ? l : max;
      cout << endl;
    }
    cout << "LIS: " << max << endl;
    return max;
  }
};

// class SolutionMemo {
// private:
//   int lis(vector<int>& nums, int curr, int start, vector<int> &memo) {
//     if(start == nums.size()) return 0;

//     if(memo[start] != -1) return memo[start];

//     int max = 1;
//     for(int i = start; i < nums.size(); i++) {
//       if(nums[i] > curr) {
//         int l = 1 + lis(nums, nums[i], i + 1, memo);
//         max = l > max ? l : max;
//       }
//     }
//     memo[start] = max;
//     return memo[start];
//   }

// public:
//   int lengthOfLIS(vector<int>& nums) {
//     if(!nums.size()) return 0;
//     int max = 1;
//     vector<int> memo(nums.size(), -1);
//     for(int i = 0; i < nums.size(); i++) {
//       int l = lis(nums, nums[i], i + 1, memo);
//       max = l > max ? l : max;
//     }
//     cout << "LIS: " << max << endl;
//     return max;
//   }
// };

int main() {
  vector<int> nums = {1,10,9,2,5,3,7,101,18,45,34,465,46,5767,67,6,87,8,65,10,9,2,5,3,7,101,18,45,34,465,46,5767,67,6,87,8,65};
  // vector<int> nums = {10,9,2,5,3,7,101,18};
  // vector<int> nums = {1,2,3,4};

  Solution s;

  s.lengthOfLIS(nums);

  return 0;
}