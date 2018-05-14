#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

void getInorderedList(TreeNode *root, vector<int> &inorder) {
  if(!root) return;
  getInorderedList(root->left, inorder);
  inorder.push_back(root->val);
  getInorderedList(root->right, inorder);
}

bool isValid1(TreeNode *root) {
  vector<int> inorder;
  getInorderedList(root, inorder);
  if(inorder.size() < 2) return true;
  for(int i = 1; i < inorder.size(); i++) {
    if(inorder[i] <= inorder[i - 1])
      return false;
  }
  return true;
}

bool isValidMinMax(TreeNode *root, int min, int max) {
  if(!root) return true;
  if(root->val <= min || root->val > max)
    return false;
  return  isValidMinMax(root->left, min, root->val) &&
          isValidMinMax(root->right, root->val, max);
}

bool isValid2(TreeNode *root) {
  return isValidMinMax(root, INT32_MIN, INT32_MAX);
}

int main() {
  vector<int> elementsValid = {8,4,10,2,6,-1,20};
  vector<int> elementsInvalid = {1,2,3,4,5,6,7};
  TreeNode *validBST = TreeNode::build(elementsValid);
  TreeNode *invalidBST = TreeNode::build(elementsInvalid);
  validBST->inorder();
  invalidBST->inorder();
  // validBST->preorder();
  // validBST->postorder();

  cout << "Valid Method1: " << isValid1(validBST) << endl;
  cout << "Valid Method2: " << isValid2(validBST) << endl;

  cout << "Valid: " << isValid1(invalidBST) << endl;
  cout << "Valid: " << isValid2(invalidBST) << endl;

  return 0;
}