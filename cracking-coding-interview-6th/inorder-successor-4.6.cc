#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

TreeNode *successor(TreeNode *node) {
  if(!node) return nullptr;
  if(node->right) {
    node = node->right;
    while(node->left) {
      node = node->left;
    }
    return node;
  } else {
    TreeNode *q = node;
    TreeNode *x = node->parent;
    while(x && x->left != q) {
      q = x;
      x = x->parent;
    }
    return x;
  }
}

int main() {
  // vector<int> elements = {1,2,3,4,5,6,7};
  // vector<pair<int,int>> tests = {{4,2}, {2,5}, {5,1}, {1,6}, {6,3}, {3,7}};

  vector<int> elements = {1,2,3,4,5,6,7,-1,-1,8,9};
  vector<pair<int,int>> tests = {{5,9},{9,1}};
  TreeNode *root = TreeNode::build(elements);
  root->inorder();

  for(auto &test : tests) {
    TreeNode *f = root->find(test.first);
    TreeNode *s = successor(f);
    cout << "Successor of " << f->val << " is " << s->val << endl;
    assert(test.second == s->val);
  }

  return 0;
}