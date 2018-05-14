#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

vector<int> order(vector<vector<int>> &tasks) {
  vector<int> order;
  unordered_set<int> set;

  int l = tasks.size();

  while(set.size() < l) {
    for(int i = 0; i < l; i++) {
      if(set.find(i) != set.end()) continue;
      int j = 0;
      for(j = 0; j < l; j++) {
        if(tasks[i][j]) break;
      }
      if(j == l) {
        set.insert(i);
        order.insert(order.begin(), i);
        for(int k = 0; k < l; k++) {
          tasks[k][i] = 0;
        }
      }
    }
    cout << "Set Size: " << set.size() << endl;
  }
  return order;
}

void print(vector<int> &v, vector<char> &labels) {
  for(int i = 0; i < v.size(); i++) {
    cout << labels[v[i]] << ", ";
  }
  cout << endl;
}

void print(vector<vector<int>> &matrix) {
  int l = matrix.size();
  for(int i = 0; i < l; i++) {
    for(int j = 0; j < l; j++) {
      cout << matrix[i][j] << "  ";
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  vector<vector<int>> input(buildOrderInput);
  vector<char> labels = {'a','b','c','d','e','f','g'};
  print(input);
  vector<int> o = order(input);
  print(o, labels);
  return 0;
}