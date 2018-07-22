#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

using namespace std;

enum ORIENTATION {
  RIGHT,
  DOWN,
  LEFT,
  UP
};

void resize(vector<vector<char>> &grid, int &gX, int &gY, int &x, int &y) {
  if(x < 0 || x >= gX) {
    grid.insert(grid.begin(), vector<char>(gY, 'w'));
    grid.push_back(vector<char>(gY, 'w'));
    gX += 2;
    if(x < 0) x++;
  }

  if(y < 0 || y >= gY) {
    int i = 0;
    for(int i = 0; i < grid.size(); i++) {
      grid[i].insert(grid[i].begin(), 'w');
      grid[i].push_back('w');
    }
    gY += 2;
    if(y < 0) y++;
  }
}

void move(vector<vector<char>> &grid, int &x, int &y, ORIENTATION &o) {
  if(grid[x][y] == 'w') {
    grid[x][y] = 'b';
    switch(o) {
      case RIGHT:
        x++;
        o = DOWN;
        break;
      case DOWN:
        y--;
        o = LEFT;
        break;
      case LEFT:
        x--;
        o = UP;
        break;
      case UP:
        y++;
        o = RIGHT;
        break;
    }
  } else {
    grid[x][y] = 'w';
    switch(o) {
      case RIGHT:
        x--;
        o = UP;
        break;
      case DOWN:
        y++;
        o = RIGHT;
        break;
      case LEFT:
        x++;
        o = DOWN;
        break;
      case UP:
        y--;
        o = LEFT;
        break;
    }
  }
}

void print(int k) {
  int gX = 10, gY = 10;
  vector<vector<char>> grid(gX, vector<char>(gY, 'w'));
  int x = gX / 2, y = gY / 2;
  ORIENTATION o = RIGHT;
  while(k) {
    // cout << "K: " << k << " (" << x << "," << y << ") " << " (" << gX << "," << gY << ") " << endl;
    if(x < 0 || x >= gX || y < 0 || y >= gY) {
      resize(grid, gX, gY, x, y);
      // cout << "K: " << k << " (" << x << "," << y << ") " << " (" << gX << "," << gY << ")*" << endl;
    }
      
    move(grid, x, y, o);
    k--;
    // usleep(1000);
  }

  for(auto row : grid) {
    for(auto col : row) {
      cout << col;
    }
    cout << endl;
  }
  cout << endl;
}

int main(int argc, char **argv) {
  if(argc == 2) {
    print(atoi(argv[1]));
  } else {
    print(200);
  }
  
  return 0;
}