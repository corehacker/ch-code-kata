#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

struct Node {
  Node *next;
  int val;

  Node(int v) : val(v), next(nullptr) {}
};

void print(Node *head) {
  Node *curr = head;
  while(curr) {
    cout << curr->val << ", ";
    curr = curr->next;
  }
  cout << endl;
}

Node *build(vector<int> &array) {
  Node *head = nullptr;
  Node *curr = nullptr;
  for(auto i : array) {
    if(!head) {
      head = new Node(i);
      curr = head;
    } else {
      curr->next = new Node(i);
      curr = curr->next;
    }
  }
  return head;
}

Node *kthToLast(Node *head, int k) {
  if(!head) return nullptr;
  Node *curr = head;
  Node *kth = nullptr;
  while(curr) {
    // cout << "curr: " << curr->val << ", k: " << k << endl;
    if(k == 0) {
      kth = head;
    } else if (k < 0) {
      kth = kth->next;
    }
    if(kth) {
      // cout << "kth: " << kth->val << ", k: " << k << endl;
    }
    curr = curr->next;
    k--;
  }
  return kth;
} 

int main() {
  vector<int> array = {1,2,3,4,5,6,7,8,9,10};
  Node *head = build(array);
  print(head);
  Node *kth = kthToLast(head, 4);
  cout << "Kth to last: " << kth->val << endl;
  return 0;
}