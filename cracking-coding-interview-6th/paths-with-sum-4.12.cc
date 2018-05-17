#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

int count(TreeNode *root, int target, int current) {
  if(!root) return 0;

  current += root->val;
  int sum = 0;
  if(current == target) sum++;
  sum += count(root->left, target, current);
  sum += count(root->right, target, current);

  return sum;
}

int countPaths(TreeNode *root, int target) {
  if(!root) return 0;
  int rootCount = count(root, target, 0);
  int leftCount = countPaths(root->left, target);
  int rightCount = countPaths(root->right, target);
  return rootCount + leftCount + rightCount;
}

int main() {
  vector<int> elements = {1,2,3,4,5,6,7};
  // vector<int> elements = {10,5,-3,3,2,-1,11,3,-2,-1,1};
  TreeNode *root = TreeNode::build(elements);
  root->inorder();

  int count = countPaths(root, 8);
  cout << "Count: " << count << endl;
  return 0;
}