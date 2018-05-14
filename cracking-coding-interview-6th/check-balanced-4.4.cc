#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

int getHeight(TreeNode *root) {
  if(!root) return -1;
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}

bool balanced(TreeNode *root) {
  if(!root) return true;

  int diff = getHeight(root->left) - getHeight(root->right);
  if(abs(diff) > 1) {
    return false;
  }

  return balanced(root->left) && balanced(root->right);
}

int checkHeight(TreeNode *root) {
  if(!root) return -1;

  int left = checkHeight(root->left);
  if(INT32_MIN == left) return left;

  int right = checkHeight(root->right);
  if(INT32_MIN == right) return right;

  if(abs(left - right) > 1) {
    return INT32_MIN;
  } else {
    return max(left, right) + 1;
  }
}

bool isBalanced(TreeNode *root) {
  return checkHeight(root) != INT32_MIN ? true : false;
}

int main() {
  vector<int> elements = {1,2,-1,4,5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  vector<int> elements1 = {1,2,3,4,5,6,7};
  TreeNode *root = TreeNode::build(elements1);
  root->inorder();
  root->preorder();
  root->postorder();

  cout << "Balanced: " << balanced(root) << endl;
  cout << "Balanced: " << isBalanced(root) << endl;

  return 0;
}