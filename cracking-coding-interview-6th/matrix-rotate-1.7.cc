#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

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

void rotate(vector<vector<int>> &m) {
  for(int layer = 0; layer < m.size() / 2; layer++) {
    int start = layer;
    int end = m.size() - 1 - layer;
    for(int i = start; i < end; i++) {
      int offset = i - start;
      int temp = m[start][i];
      m[start][i] = m[end - offset][start];
      m[end - offset][start] = m[end][end - offset];
      m[end][end - offset] = m[i][end];
      m[i][end] = temp;
    }
  }
}

int main() {
  vector<vector<int>> m = {
    {1,2,3,4},
    {12,13,14,5},
    {11,16,15,6},
    {10,9,8,7}
  };

  print(m);
  rotate(m);
  print(m);

  return 0;
}