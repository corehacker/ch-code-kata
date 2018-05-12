#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <string.h>

using namespace std;

void print(vector<vector<int>> &m) {
  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      cout << m[i][j] << "   ";
    }
    cout << endl;
  }
  cout << endl << endl;
}

void zero(vector<vector<int>> &m) {
  int rows[m.size()];
  int cols[m[0].size()];

  for(int i = 0; i < m.size(); i++) {
    rows[i] = 0;
  }

  for(int i = 0; i < m[0].size(); i++) {
    cols[i] = 0;
  }
  
  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      if(m[i][j] == 0) {
        rows[i] = 1;
        cols[j] = 1;
      }
    }
  }

  for(int i = 0; i < m.size(); i++) {
    for(int j = 0; j < m[i].size(); j++) {
      if(rows[i] == 1) {
        m[i][j] = 0;
      }
    }
  }

  for(int j = 0; j < m[0].size(); j++) {
    for(int i = 0; i < m.size(); i++) {
      if(cols[j] == 1) {
        m[i][j] = 0;
      }
    }
  }
}

int main() {
  vector<vector<int>> m = {
    {1,2,3,4},
    {12,13,0,5},
    {11,0,15,6},
    {10,9,8,7}
  };

  print(m);
  zero(m);
  print(m);

  return 0;
}