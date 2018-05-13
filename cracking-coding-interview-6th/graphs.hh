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


struct Node {
  int id;
  int val;
  bool visited;
  vector<Node *> children;

  Node(int id, int val, bool visited) : id(id), val(val), visited(visited) {}

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
  vector<Node *> nodes;
  Graph(int n){
    nodes = vector<Node *>(n);
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
        G->nodes[i] = new Node(i, 0, false);
      for(int j = 0; j < adjacency[i].size(); j++) {
        if(adjacency[i][j]) {
          if(!G->nodes[j])
            G->nodes[j] = new Node(j, 0, false);
          G->nodes[i]->children.push_back(G->nodes[j]);
        }
      }
    }
    return G;
  }
};


