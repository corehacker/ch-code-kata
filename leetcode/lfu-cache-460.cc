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

uint64_t getEpochNano() {
	auto epoch = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
}

struct Node{
    int key;
    int value;
    int frequency;
    long timestamp;
    Node *next;
    Node *prev;
    Node(int k, int v, int f, long t) : 
      key(k), value(v), frequency(f), timestamp(t), next(nullptr), prev(nullptr) {}
    void reset() {
        next = nullptr;
        prev = nullptr;
    }
};

class LRUList {
private:
    Node *head;
    Node *tail;

public:
    LRUList() : head(nullptr), tail(nullptr) {}

    void push_back(Node *node) {
        if(!head && !tail) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    Node *pop_front() {
        if(!head && !tail) {
            return nullptr;
        } else {
            Node *ret = head;
            head = head->next;
            if(head) head->prev = nullptr;
            if(!head) tail = nullptr;
            return ret;
        }
    }

    void remove(Node *node) {
        if(!node) return;
        if(node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
        } else if (node == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
    }

    void print() {
        Node *curr = head;
        if(!head && !tail) cout << "[EMPTY]";
        if(head) cout << "[" << head->key << ", " << head->value << "] ";
        while(curr) {
            cout << "(" << curr->key << ", " << curr->value << "), ";
            curr = curr->next;
        }
        if(tail) cout << "[" << tail->key << ", " << tail->value << "] ";
        cout << endl;
    }
};

class NodeCompareFrequency {
public:
  bool operator() (const Node *lhs, const Node *rhs) const {
    return lhs->frequency < rhs->frequency;
  }
};

class NodeCompareTimestamp {
public:
  bool operator() (const Node *lhs, const Node *rhs) const {
    return lhs->timestamp < rhs->timestamp;
  }
};

class LFUCache {
private:
  unordered_map<int, Node *> map;
  priority_queue<Node *, vector<Node *>, NodeCompareFrequency> q;
  LRUList list;
  size_t capacity;

  bool full() {
    return capacity == map.size() ? true : false;
  }

  Node *getEvictionNode() {
    priority_queue<Node *, vector<Node *>, NodeCompareTimestamp> tsQ;
    Node *temp = q.top();
    q.pop();

    tsQ.push(temp);

    while(true) {
      Node *t = q.top();
      if(t->frequency == temp->frequency) {
        q.pop();
        tsQ.push(t);
      } else {
        break;
      }
    }

    Node *evict = tsQ.top();
    tsQ.pop();

    while(tsQ.size()) {
      Node *temp = tsQ.top();
      tsQ.pop();
      q.push(temp);
    }

    return evict;
  }

  void evict() {
    Node *e = getEvictionNode();
    map.erase(e->key);
    list.remove(e);
    delete e;
  }

public:
  LFUCache(int capacity) {
    this->capacity = (size_t) capacity;
  }
  
  int get(int key) {
    if(map.find(key) == map.end()) return -1;
    Node *node = map[key];
    list.remove(node);
    node->reset();

    node->frequency++;
    node->timestamp = getEpochNano();

    list.push_back(node);
    q.push(node);
    return node->value;
  }
  
  void put(int key, int value) {
    Node *node = nullptr;
    if(map.find(key) == map.end()) {
      if(full()) {
        evict();
      }
    }
    node = new Node(key, value, 1, getEpochNano());
    list.push_back(node);
    map.insert(make_pair(key, node));
    q.push(node);
  }
};

int main() {
  return 0;
}