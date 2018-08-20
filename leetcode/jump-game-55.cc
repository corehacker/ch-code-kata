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
    bool canJump(vector<int>& nums, int start, vector<int>& memo) {
        if(start >= nums.size()) return false;
        if(start == nums.size() - 1) return true;
        if(memo[start] != -1) return memo[start] == 1 ? true : false;
        int jumps = nums[start];
        if(!jumps) {
          memo[start] = 0;
          return false;
        }
        for(int i = 1; i <= jumps; i++) {
            bool can = canJump(nums, start + i, memo);
            if(can) {
                memo[start] = 1;
                return can;
            }
        }
        memo[start] = 0;
        return false;
    }
public:
    bool canJump(vector<int>& nums) {
        if(!nums.size()) return false;
        vector<int> memo(nums.size(), -1);
        
        for(int i = nums.size() - 2; i >= 0; i--) {
            canJump(nums, i, memo);
        }

        cout << "Memo: ";
        for(auto m: memo) {
          cout << m << ", ";
        }
        cout << endl;
        
        return memo[0] == 1 ? true : false;
    }
};

int main() {
  Solution s;
  vector<int> nums = {2,3,1,1,4};
  nums = {3,2,1,0,4};
  nums = {2,1};
  bool can = s.canJump(nums);
  cout << "can? " << can << endl;
  return 0;
}