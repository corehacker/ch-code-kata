
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <regex>
#include <functional>

using namespace std;


class Solution {
private:
    void dfs(vector<vector<char>>& board, int i, int j) {
        if(i < 0 || j < 0 || 
          i >= board.size() || j >= board[i].size() || 
          board[i][j] == 'X' || board[i][j] == ' ') return;
        board[i][j] = ' ';
        dfs(board, i - 1, j);
        dfs(board, i + 1, j);
        dfs(board, i, j - 1);
        dfs(board, i, j + 1);
    }
public:
    void solve(vector<vector<char>>& board) {
        if(board.size() < 3) return;
        if(board[0].size() < 3) return;
        
        int i = 0;
        for(int j = 0; j < board[i].size(); j++) {
            if(board[i][j] == 'O') {
                dfs(board, i, j);
            }
        }
        i = board.size() - 1;
        for(int j = 0; j < board[i].size(); j++) {
            if(board[i][j] == 'O') {
                dfs(board, i, j);
            }
        }
        
        int j = 0;
        for(int i = 0; i < board.size(); i++) {
            if(board[i][j] == 'O') {
                dfs(board, i, j);
            }
        }
        
        j = board[0].size() - 1;
        for(int i = 0; i < board.size(); i++) {
            if(board[i][j] == 'O') {
                dfs(board, i, j);
            }
        }
        
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[i].size(); j++) {
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == ' ') board[i][j] = 'O';
            }
        }
    }
};

void print(vector<vector<char>>& board) {
  for(int i = 0; i < board.size(); i++) {
    for(int j = 0; j < board[i].size(); j++) {
        cout << board[i][j] << "    ";
    }
    cout << endl;
  }
}

int main() {

  Solution s;
  vector<vector<char>>input = {
    {'O','O','O'},
    {'O','O','O'},
    {'O','O','O'}
  };
  print(input);
  s.solve(input);
  cout << endl;

  print(input);

  return 0;
}