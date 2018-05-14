#include <iostream>
#include <vector>
using namespace std;

  /*
   *  [START] Graph Structure
   *    (0, 0)
   *        --> (1, 0) -> (2, 0) -> (5, 0) -> (6, 0) -> [END]
   *    (1, 0)
   *        --> [END]
   *    (2, 0)
   *        --> [END]
   *    (3, 0)
   *        --> [END]
   *    (4, 0)
   *        --> (3, 0) -> [END]
   *    (5, 0)
   *        --> (3, 0) -> (4, 0) -> [END]
   *    (6, 0)
   *        --> (4, 0) -> [END]
   *    (7, 0)
   *        --> (8, 0) -> [END]
   *    (8, 0)
   *        --> [END]
   *    (9, 0)
   *        --> (10, 0) -> (11, 0) -> (12, 0) -> [END]
   *    (10, 0)
   *        --> [END]
   *    (11, 0)
   *        --> (12, 0) -> [END]
   *    (12, 0)
   *        --> [END]
   *  [START] Graph Structure
   */
  vector<vector<int>> directed1 = {
  /*  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12 */  
    { 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0  }, // 0
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  }, // 1
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  }, // 2
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  }, // 3
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0  }, // 4
    { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  }, // 5
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0  }, // 6
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0  }, // 7
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  }, // 8
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1  }, // 9
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  }, // 10
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1  }, // 11
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  }  // 12
  };

  vector<vector<int>> buildOrderInput = {
    {0,0,0,0,1,0,0},
    {1,0,0,0,1,0,0},
    {1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0},
    {1,1,1,0,0,0,0},
    {0,0,0,0,0,0,0}
  };


struct GraphNode {
  int id;
  int val;
  bool visited;
  vector<GraphNode *> children;

  GraphNode(int id, int val, bool visited) : id(id), val(val), visited(visited) {}

  void print() {
    cout << "      --> ";
    for(auto &node : children) {
      cout << "("  << 
        node->id << ", " <<
        node->val << ") -> ";
    }
    cout << "[END]" << endl;
  }
};

struct Graph {
  vector<GraphNode *> nodes;
  Graph(int n){
    nodes = vector<GraphNode *>(n);
  }
  void print() {
    cout << "[START] Graph Structure" << endl;
    for(auto &node : nodes) {
      cout << "  (" << 
        node->id << ", " <<
        node->val << ")" << endl;
        node->print();

    }
    cout << "[END] Graph Structure" << endl;
  }
  void reset() {
    for(auto &node : nodes) {
      node->visited = false;
    }
  }

  static Graph *build(vector<vector<int>> &adjacency) {
    Graph *G = new Graph(adjacency.size());
    for(int i = 0; i < adjacency.size(); i++) {
      if(!G->nodes[i])
        G->nodes[i] = new GraphNode(i, 0, false);
      for(int j = 0; j < adjacency[i].size(); j++) {
        if(adjacency[i][j]) {
          if(!G->nodes[j])
            G->nodes[j] = new GraphNode(j, 0, false);
          G->nodes[i]->children.push_back(G->nodes[j]);
        }
      }
    }
    return G;
  }
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;

private:
  void inorder(TreeNode *root) {
    if(!root) return;
    inorder(root->left);
    cout << root->val << ", ";
    inorder(root->right);
  }

  void preorder(TreeNode *root) {
    if(!root) return;
    cout << root->val << ", ";
    preorder(root->left);
    preorder(root->right);
  }

  void postorder(TreeNode *root) {
    if(!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << ", ";
  }

  static TreeNode *build(vector<int> &elements, TreeNode *parent, int start) {
    if(start >= elements.size()) return nullptr;

    if(elements[start] == -1) return nullptr;
    TreeNode *root = new TreeNode(elements[start]);
    root->parent = parent;
    root->left = build(elements, root, (2 * start) + 1);
    root->right = build(elements, root, (2 * start) + 2);

    return root;
  }

public:
  TreeNode(int val) : val(val), left(nullptr), right(nullptr), parent(nullptr) {}

  static TreeNode *build(vector<int> &elements) {
    return build(elements, nullptr, 0);
  }

  void inorder() {
    inorder(this);
    cout << endl;
  }

  void preorder() {
    preorder(this);
    cout << endl;
  }
  
  void postorder() {
    postorder(this);
    cout << endl;
  }
};
