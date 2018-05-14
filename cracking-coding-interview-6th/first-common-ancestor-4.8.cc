#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

void print(vector<TreeNode *> &p) {
  for(auto &entry : p) {
    cout << entry->val << ", ";
  }
  cout << endl;
}

vector<TreeNode *> pathToRoot(TreeNode *n) {
  TreeNode *curr = n;
  vector<TreeNode *> path;
  while(curr) {
    path.insert(path.begin(), curr);
    curr = curr->parent;
  }
  return path;
}

TreeNode *commonAncestor(TreeNode *root, TreeNode *a, TreeNode *b) {
  vector<TreeNode *> aP = pathToRoot(a),
                     bP = pathToRoot(b);

  if(!aP.size() || !bP.size()) return nullptr;

  print(aP); 
  print(bP);
  int i = 0;
  for(i = 0; i < min(aP.size(), bP.size()); i++) {
    if(aP[i] != bP[i])
      break;
  }
  return aP[i - 1];
}

int main() {
  vector<int> elements = {1,2,3,4,5,6,7};
  TreeNode *root = TreeNode::build(elements);
  root->preorder();

  TreeNode *common = commonAncestor(root, root->find(3), root->find(5));
  cout << "Common: " << common->val << endl;
  return 0;
}