#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
  string val;
  Node *next;

  Node(string &val) : val(val), next(nullptr) {
  }
};

class List {
private:
  Node *head;
  Node *tail;

public:
  List() : head(nullptr), tail(nullptr) {}
  
  void insert(string val) {
    if(!head) {
      head = new Node(val);
      tail = head;
    } else {
      tail->next = new Node(val);
      tail = tail->next;
    }
  }

  Node *get(string val) {
    Node *node = head;
    while(node) {
      if(node->val == val) break;
      node = node->next;
    }
    return node;
  }

  void remove(Node *node) {
    if(!node) return;
    Node *curr = head;
    Node *prev = nullptr;
    while(curr) {
      if(curr->val == node->val) break;
      prev = curr;
      curr = curr->next;
    }
    if(prev) {
      prev->next = curr->next;
      if(curr == tail) {
        tail = prev;
      }
      delete curr;
    } else {
      if(head == tail) {
        tail = curr->next;
      }
      head = curr->next;
      delete curr;
    }
  }

  vector<string> values() {
    vector<string> result;
    Node *node = head;
    while(node) {
      result.push_back(node->val);
      node = node->next;
    }
  }

  void print() {
    cout << "[" << (head ? head->val : "null") << "] ";
    Node *node = head;
    while(node) {
      cout << node->val << ", ";
      node = node->next;
    }
    cout << "[" << (tail ? tail->val : "null") << "] ";
    cout << endl;
  }

};

int main() {
  List list;
  list.insert("fred");
  list.insert("wilma");
  list.insert("betty");
  list.insert("barney");
  list.insert("alice");
  list.insert("bob");
  list.print();

  list.remove(list.get("bob"));
  list.print();

  list.remove(list.get("betty"));
  list.print();

  list.remove(list.get("fred"));
  list.print();

  list.remove(list.get("barney"));
  list.print();

  list.remove(list.get("alice"));
  list.print();

  list.remove(list.get("wilma"));
  list.print();
  return 0;
}