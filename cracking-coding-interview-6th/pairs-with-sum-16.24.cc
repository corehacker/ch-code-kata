#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>

using namespace std;

unordered_set<int> constructSet(vector<int> &nums) {
  unordered_set<int> set;
  for(auto num : nums) {
    set.insert(num);
  }
  return set;
}

unordered_map<int, int> constructPairMap(unordered_set<int> &set, int target) {
  unordered_map<int, int> map;
  for(auto num : set) {
    int diff = target - num;
    auto search = set.find(diff);
    if(search != set.end()) {
      if(num < diff) {
        map[num] = diff;
      } else {
        map[diff] = num;
      }
    }
  }
  return map;
}

vector<vector<int>> pairs(unordered_map<int, int> &map) {
  vector<vector<int>> pairs;
  for(auto e : map) {
    vector<int> pair;
    pair.push_back(e.first);
    pair.push_back(e.second);
    pairs.push_back(pair);
  }
  return pairs;
}

vector<vector<int>> pairs(vector<int> &nums, int target) {
  unordered_set<int> set = constructSet(nums);
  unordered_map<int, int> map = constructPairMap(set, target);
  return pairs(map);
}

int main() {
  vector<int> nums = {1,2,3,4,5,6,7,8,9,-1,-2,-3,-4,-5,-6,-7,-8,-9};
  vector<vector<int>> p = pairs(nums, 0);
  for(auto pair : p) {
    cout << "(" << pair[0] << ", " << pair[1] << ")" << endl;
  }
  return 0;
}