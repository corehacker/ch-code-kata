#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <regex>
#include <functional>

using namespace std;

void print(set<set<int>> &sums) {
  for(auto entry : sums) {
    for(auto e : entry) {
      cout << e << ", ";
    }
    cout << endl;
  }
  cout << endl;
}

void print(vector<int> &current) {
  for(auto entry : current) {
    cout << entry << ", ";
  }
  cout << endl;
}

int sum(vector<int> &current) {
  int i = 0;
  for(auto n : current)
    i += n;
  return i;
}

void threeSum(vector<int> &nums,
              set<set<int>> &sums,
              vector<int> &current,
              int index) {
  if(current.size() == 3) {
    if(sum(current) == 0) {
      cout << "Current: "; print(current);
      sums.insert(set<int>(current.begin(), current.end()));
    }
  }

  for(int i = index; i < nums.size(); i++) {
    current.push_back(nums[i]);
    threeSum(nums, sums, current, i + 1);
    current.pop_back();
  }
}

set<set<int>> threeSum(vector<int>& nums) {
    set<set<int>> sums;
    vector<int> current;
    threeSum(nums, sums, current, 0);
    return sums;
}



int main() {
  vector<int> nums = {-1, 0, 1, 2, -1, -4};
  set<set<int>> sums = threeSum(nums);
  print(sums);
  return 0;
}