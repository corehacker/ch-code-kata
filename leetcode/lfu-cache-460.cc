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

unsigned long gTime = 0;

unsigned long getEpochNano() {
	// auto epoch = std::chrono::system_clock::now().time_since_epoch();
	// return std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
  return gTime++;
}

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

struct Node{
    int key;
    int value;
    int frequency;
    long timestamp;
    Node(int k, int v, int f, long t) : 
      key(k), value(v), frequency(f), timestamp(t) {}
};

class NodeCompareFrequency {
public:
  bool operator() (const Node *lhs, const Node *rhs) const {
    if(lhs->frequency > rhs->frequency) return true;
    if(lhs->frequency == rhs->frequency && lhs->timestamp > rhs->timestamp) return true;
    return false;
  }
};

class LFUCache {
private:
  unordered_map<int, Node *> map;
  my_priority_queue<Node *, vector<Node *>, NodeCompareFrequency> q;
  size_t capacity;

  bool full() {
    return capacity == map.size() ? true : false;
  }

  Node *getEvictionNode() {
    Node *evict = q.top();
    q.pop();
    return evict;
  }

  void evict() {
    Node *e = getEvictionNode();
    cout << "Evicting - key: " << e->key << ", value: " << e->value << 
      ", frequency: " << e->frequency << ", timestamp: " << e->timestamp << endl;
    map.erase(e->key);
    delete e;
  }

  void replace(int key, int value) {
    Node *node = map[key];
    q.remove(node);

    node->value = value;
    node->frequency++;
    node->timestamp = getEpochNano();

    q.push(node);
  }

public:
  LFUCache(int capacity) {
    this->capacity = (size_t) capacity;
  }

  void print() {
    cout << "***************Cache: " << endl;
    for(auto it: map) {
      cout << "  " << it.first << endl;
      cout << "    value    : " << it.second->value << endl;
      cout << "    timestamp: " << it.second->timestamp << endl;
      cout << "    frequency: " << it.second->frequency << endl;
      cout << endl;
    }
    cout << "*********************" << endl;
  }
  
  int get(int key) {
    if(map.find(key) == map.end()) return -1;
    Node *node = map[key];
    q.remove(node);

    node->frequency++;
    node->timestamp = getEpochNano();

    q.push(node);
    return node->value;
  }
  
  void put(int key, int value) {
    if(map.find(key) == map.end()) {
      if(full()) {
        evict();
      }
      Node *node = new Node(key, value, 1, getEpochNano());
      map.insert(make_pair(key, node));
      q.push(node);
    } else {
      replace(key, value);
    }
  }
};

int main() {
  LFUCache cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  cache.print();
  cout << "Get 1: " << cache.get(1) << endl;
  cache.print();
  cache.put(3,3);
  cache.print();
  cout << "Get 2: " << cache.get(2) << endl;
  cout << "Get 3: " << cache.get(3) << endl;
  cache.print();
  cache.put(4,4);
  cache.print();
  cout << "Get 1: " << cache.get(1) << endl;
  cout << "Get 3: " << cache.get(3) << endl;
  cout << "Get 4: " << cache.get(4) << endl;
  return 0;
}