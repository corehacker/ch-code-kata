#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <algorithm>

using namespace std;

class Solution {
private:
  void jump(vector<int>& nums, int position, int count, int &min) {
    if(position >= nums.size()) return;
    if(position == nums.size() - 1) {
      // cout << "position: " << position << ", count: " << count << ", min: " << min << endl;
      min = count < min ? count : min;
      return;
    }

    for(int pos = 1; pos <= nums[position]; pos++) {
      // cout << "From " << position << ", trying: " << pos << endl;
      jump(nums, position + pos, count + 1, min);
    }
  }

public:
  int jump(vector<int>& nums) {
    int min = INT32_MAX;
    jump(nums, 0, 0, min);
    // cout << "min: " << min << endl;
    return min;
  }

  int jumpdp(vector<int>& nums) {
    if(!nums.size()) return 0;
    if(1 == nums.size()) return 0;
    vector<int> memo(nums.size(), nums.size());
    memo[nums.size() - 1] = 0;
    for(int position = nums.size() - 2; position >= 0; position--) {
      for(int i = nums[position]; i >= 1; i--) {
        if(position + i < nums.size()) {
          memo[position] = min(memo[position], memo[position + i] + 1);
        }
      }
    }
    cout << "Memo: ";
    for(auto m: memo) {
      cout << m << ", ";
    }
    cout << endl;
    return memo[0];
  }
};

int main() {
  Solution s;
  vector<int> nums = {2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4,2,3,1,1,4};
  // nums = {2,3,1,1,4,2,3,1,1,4,2,3,1,1,4};
  // nums = {3,2,1,0,4};
  // nums = {};
  // int min = s.jump(nums);
  int mindp = s.jumpdp(nums);
  cout << "min jumps: " << mindp << endl;
  return 0;
}
