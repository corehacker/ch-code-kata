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


enum HeapMode {
  MIN_HEAP,
  MAX_HEAP
};

class Heap {
private:
  vector<int> data;
  int size;
  HeapMode  mode;

  int parent(int child) {
    return (child - 1) / 2;
  }

  int left(int parent) {
    return ((2 * parent) + 1);
  }

  int right(int parent) {
    return ((2 * parent) + 2);
  }

  bool hasLeft(int parent) {
    return left(parent) < size;
  }

  bool hasRight(int parent) {
    return right(parent) < size;
  }

  void exchange(int i, int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }

  void heapifyDownMin() {
    int index = 0;
    while(hasLeft(index)) {
      int smallest = left(index);
      if(hasRight(index) && data[right(index)] < data[smallest]) {
        smallest = right(index);
      }

      if(data[index] < data[smallest]) {
        break;
      } else {
        exchange(index, smallest);
      }
      index = smallest;
    }
  }

  void heapifyDownMax() {
    int index = 0;
    while(hasLeft(index)) {
      int largest = left(index);
      if(hasRight(index) && data[right(index)] > data[largest]) {
        largest = right(index);
      }

      if(data[index] > data[largest]) {
        break;
      } else {
        exchange(index, largest);
      }
      index = largest;
    }
  }

  void heapifyDown() {
    switch(mode) {
      case MIN_HEAP:
        heapifyDownMin();
        break;
      case MAX_HEAP:
        heapifyDownMax();
        break;
    }
  }

  void heapifyUpMin() {
    int i = size - 1;
    while(i >= 0 && data[i] < data[parent(i)]) {
      exchange(i, parent(i));
      i = parent(i);
    }
  }

  void heapifyUpMax() {
    int i = size - 1;
    while(i >= 0 && data[i] > data[parent(i)]) {
      exchange(i, parent(i));
      i = parent(i);
    }
  }

  void heapifyUp() {
    switch(mode) {
      case MIN_HEAP:
        heapifyUpMin();
        break;
      case MAX_HEAP:
        heapifyUpMax();
        break;
    }
  }

  string depthSpaces(int depth) {
    ostringstream os;
    while(depth--) {
      os << "  ";
    }
    return os.str();
  }

  void print(int parent, int depth) {
    if(parent >= size) {
      // cout << depthSpaces(depth) << "X" << endl;
      return;
    }
    cout << depthSpaces(depth) << data[parent] << endl;
    
    if(hasRight(parent)) print(right(parent), depth + 1);
    // else cout << depthSpaces(depth) << "X" << endl;

    if(hasLeft(parent)) print(left(parent), depth + 1);
    // else cout << depthSpaces(depth) << "X" << endl;
  }
public:
  Heap() {
    init(100, MIN_HEAP);
  }

  Heap(HeapMode m) {
    init(100, m);
  }

  void init(int initial, HeapMode m) {
    data = vector<int>(initial, INT32_MAX);
    size = 0;
    mode = m;
  }

  void build(vector<int> &items) {
    for(auto item : items) {
      cout << "Adding: " << item << endl;
      add(item);
      // print();
      // cout << endl;
    }
  }

  void print() {
    cout << endl << "HEAP: ";
    for(int i = 0; i < size; i++) {
      cout << data[i] << ", ";
    }
    cout << endl;

    cout << "TREE: " << endl;
    print(0, 0);
  }

  void add(int val) {
    data[size] = val;
    size++;
    heapifyUp();
  }

  int peek() {
    return data[0];
  }

  int poll() {
    int ret = data[0];
    data[0] = data[size - 1];
    data[size - 1] = INT32_MAX;
    size--;
    heapifyDown();
    return ret;
  }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, unsigned int> map;
        unordered_map<unsigned int, vector<int>> inverse;
        for(auto num : nums) {
            if(map.find(num) == map.end()) {
                map[num] = 1;
            } else {
                map[num]++;
            }
        }
        for(auto entry : map) {
          // cout << entry.first << ": " << entry.second << endl;
            inverse[entry.second].insert(inverse[entry.second].begin(), entry.first);
        }
        for(auto entry : inverse) {
            if(entry.second.size()) {
                sort(entry.second.begin(), entry.second.end());
            }
        }
        Heap h(MAX_HEAP);
        for(auto entry : inverse) {
            if(entry.second.size()) {
              // cout << entry.first << ": " << entry.second.size() << endl;
                h.add(entry.first);
                // h.print();
            }
        }
        vector<int> frequent;
        while(true) {
            int next = h.poll();
            vector<int> w = inverse[next];
            sort(w.begin(), w.end());
            for(auto word: w) {
              frequent.push_back(word);
              if(frequent.size() == k) {
                return frequent;
              }
            }
        }
        return frequent;
    }
};

int main() {
  vector<int> words = {1,1,1,2,2,3};
  Solution s;

  vector<int> frequent = s.topKFrequent(words, 2);

  for(auto f : frequent) {
    cout << f << ", ";
  }
  cout << endl;
  return 0;
}