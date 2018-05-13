#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

bool hasRoute(Graph *G, Node *src, Node *dst) {
  if(!G || !src || !dst) return false;
  if(src == dst) return true;

  src->visited = true;
  for(auto &child : src->children) {
    if(!child->visited) {
      bool found = hasRoute(G, child, dst);
      if(found) return true;
    }
  }
  return false;
}

int main() {
  Graph *G = Graph::build(directed1);
  G->print();
  

  vector<pair<pair<int,int>, bool>> routes = {
    {{0, 1}, true},
    {{0, 2}, true},
    {{0, 3}, true},
    {{0, 4}, true},
    {{0, 5}, true},
    {{0, 6}, true},
    {{0, 7}, false},
    {{0, 8}, false},
    {{0, 9}, false},
    {{0, 10}, false},
    {{0, 11}, false},
    {{0, 12}, false},
    {{1, 0}, false},
    {{1, 2}, false},
    {{1, 3}, false},
    {{1, 4}, false},
    {{1, 5}, false},
    {{1, 6}, false},
    {{1, 7}, false},
    {{1, 8}, false},
    {{1, 9}, false},
    {{1, 10}, false},
    {{1, 11}, false},
    {{1, 12}, false},
    {{2, 0}, false},
    {{2, 1}, false},
    {{2, 3}, false},
    {{2, 4}, false},
    {{2, 5}, false},
    {{2, 6}, false},
    {{2, 7}, false},
    {{2, 8}, false},
    {{2, 9}, false},
    {{2, 10}, false},
    {{2, 11}, false},
    {{2, 12}, false},
    {{9, 10}, true},
    {{9, 11}, true},
    {{9, 12}, true},
    {{10, 0}, false},
    {{10, 1}, false},
    {{10, 2}, false},
    {{10, 3}, false},
    {{10, 4}, false},
    {{10, 5}, false},
    {{10, 6}, false},
    {{10, 7}, false},
    {{10, 8}, false},
    {{10, 9}, false},
    {{10, 11}, false},
    {{10, 12}, false},
    {{7, 8}, true},
    {{8, 7}, false},
  };

  for(auto test : routes) {
    cout << "Route: (" << test.first.first << ", " << test.first.second << ")" << endl;
    G->reset();
    assert(hasRoute(G, G->nodes[test.first.first], G->nodes[test.first.second]) == test.second);
  }

  delete G;
  return 0;
}