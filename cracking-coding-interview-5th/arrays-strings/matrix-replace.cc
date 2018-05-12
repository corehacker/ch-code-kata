#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

void replace(vector<vector<int>> &m) {
  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      if(m[i][j] == 0) {
        for(int k = 0; k < m[i].size(); k++) {
          m[i][k] = 0;
        }
        break;
      }
    }
  }
}

void print(vector<vector<int>> &m) {
  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      cout << m[i][j] << "   ";
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  vector<vector<int>> m = {
    {1,2,3},
    {4,0,6},
    {7,8,9}
  };

  print(m);
  replace(m);
  print(m);

  return 0;
}