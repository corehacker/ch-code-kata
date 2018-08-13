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
#include <queue>
#include <chrono>

using namespace std;

template <typename T, typename Container, typename Comparator>
class my_priority_queue : public priority_queue<T, Container, Comparator> {
public:
  bool remove(const T &value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
      this->c.erase(it);
      make_heap(this->c.begin(), this->c.end(), this->comp);
      return true;
    } else {
      return false;
    }
  }
};

class Solution {
private:
  my_priority_queue<int, vector<int>, less<int>> maxHeap;
  my_priority_queue<int, vector<int>, greater<int>> minHeap;

  double median() {
    if(!maxHeap.size() && !minHeap.size()) return 0;

    if(maxHeap.size() == minHeap.size())
      return ((double) maxHeap.top() + (double) minHeap.top()) / 2;
    else
      return (double) minHeap.top();
  }

  void balance() {
    if(maxHeap.size() > minHeap.size()) {
      minHeap.push(maxHeap.top()); maxHeap.pop();
    }
    if(minHeap.size() - maxHeap.size() > 1) {
      maxHeap.push(minHeap.top()); minHeap.pop();
    }
  }

  void add(int n) {
    if((double) n < median()) {
      maxHeap.push(n);
    } else {
      minHeap.push(n);
    }
    balance();
  }

  void remove(int n) {
    if((double) n < median()) {
      maxHeap.remove(n);
    } else {
      minHeap.remove(n);
    }
    balance();
  }
public:
  vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    vector<double> result;
    if(!nums.size()) return result;
    for(int i = 0; i < nums.size(); i++) {
      if(i >= k) {
        result.push_back(median());
        remove(nums[i - k]);
      }
      add(nums[i]);
    }
    result.push_back(median());
    return result;
  }
};

int main() {
  Solution s;
  vector<int> nums = {1,3,-1,-3,5,3,6,7};
  vector<double> result = s.medianSlidingWindow(nums, 3);
  for(auto a: result) {
    cout << a << ", ";
  }
  cout << endl;
  return 0;
}