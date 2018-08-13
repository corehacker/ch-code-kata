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


class MedianFinder {
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
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
      add(num);
    }
    
    double findMedian() {
      return median();
    }
};

int main() {
  MedianFinder mf;
  cout << "Median: " << mf.findMedian() << endl;
  mf.addNum(1);
  cout << "Median: " << mf.findMedian() << endl;
  mf.addNum(2);
  cout << "Median: " << mf.findMedian() << endl;
  mf.addNum(3);
  cout << "Median: " << mf.findMedian() << endl;
  mf.addNum(4);
  cout << "Median: " << mf.findMedian() << endl;
  mf.addNum(5);
  cout << "Median: " << mf.findMedian() << endl;
  mf.addNum(6);
  cout << "Median: " << mf.findMedian() << endl;
  return 0;
}