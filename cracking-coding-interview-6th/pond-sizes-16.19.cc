#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <algorithm>

using namespace std;

vector<vector<bool>> initVisited(vector<vector<int>> &grid) {
  vector<vector<bool>> visited;
  for(auto g : grid) {
    visited.push_back(vector<bool>(g.size(), false));
  }
  return visited;
}

void pondSizes(vector<vector<int>> &grid,
               vector<vector<bool>> &visited,
               int i, int j, int &size) {
  if(i >= grid.size() || j >= grid[i].size()) return;
  if(grid[i][j] == 0) {
    if(visited[i][j]) {
      return;
    } else {
      visited[i][j] = true;
      size++;
      pondSizes(grid, visited, i + 1, j, size);
      pondSizes(grid, visited, i, j + 1, size);
      pondSizes(grid, visited, i + 1, j + 1, size);
      pondSizes(grid, visited, i - 1, j, size);
      pondSizes(grid, visited, i, j - 1, size);
      pondSizes(grid, visited, i - 1, j - 1, size);
      pondSizes(grid, visited, i - 1, j + 1, size);
      pondSizes(grid, visited, i + 1, j - 1, size);
    }
  }
}

unordered_set<int> pondSizes(vector<vector<int>> &grid) {
  unordered_set<int> sizes;
  vector<vector<bool>> visited = initVisited(grid);
  for(int i = 0; i < grid.size(); i++) {
    for(int j = 0; j < grid[i].size(); j++) {
      if(!grid[i][j] && !visited[i][j]) {
        int size = 0;
        pondSizes(grid, visited, i, j, size);
        if(size) {
          sizes.insert(size);
        }
      }
    }
  }
  return sizes;
}

int main(int argc, char **argv) {
  vector<vector<int>> grid = {
    {0,2,1,0,0},
    {0,1,0,1,0},
    {0,1,0,1,1},
    {0,0,0,1,0},
    {1,1,1,0,1},
    {1,1,1,1,1},
    {1,1,1,0,1}
  };
  unordered_set<int> sizes = pondSizes(grid);
  cout << "Pnd Sizes: " << endl;
  for(auto s: sizes) {
    cout << s << ", ";
  }
  cout << endl;
  return 0;
}