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
public:
    void rotate(vector<int>& nums, int k) {
        if(k <= 0) return;
        k = k % nums.size();
        while(k--) {
          nums.insert(nums.begin(), nums.back());
          nums.pop_back();
        }
    }
};

class Solution1 {
public:
    int hammingWeight(uint32_t n) {
        int ones = 0;
        while(n) {
            if(n & 0x1 == 1) ones++;
            n = n >> 1;
        }
        return ones;
    }
};

int main() {
  Solution1 s;
  vector<int> nums = {-1,-100,3,99};
  cout << "hamming: " << s.hammingWeight(0xFFFFFFFF) << endl;
  // for(auto n: nums) cout << n << ", ";
  // cout << endl;
  return 0;
}