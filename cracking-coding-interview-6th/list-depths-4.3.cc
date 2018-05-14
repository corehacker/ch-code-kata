#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

void listOfDepths(TreeNode *root, vector<vector<int>> &list, int depth) {
  if(!root) return;

  if(depth == list.size()) {
    list.push_back(vector<int>());
  }
  list[depth].push_back(root->val);
  listOfDepths(root->left, list, depth + 1);
  listOfDepths(root->right, list, depth + 1);
}

vector<vector<int>> listOfDepths(TreeNode *root) {
  vector<vector<int>> list;

  listOfDepths(root, list, 0);

  return list;
}

int main() {
  vector<int> elements = {1,2,3,4,5,6,7,-1,-1,-1,-1,-1,8,-1,9};
  TreeNode *root = TreeNode::build(elements);
  root->inorder();
  root->preorder();
  root->postorder();

  vector<vector<int>> list = listOfDepths(root);
  for(int i = 0; i < list.size(); i++) {
    cout << "@ Depth: ";
    for(int j = 0; j < list[i].size(); j++) {
      cout << list[i][j] << ", ";
    }
    cout << endl;
  }
  return 0;
}