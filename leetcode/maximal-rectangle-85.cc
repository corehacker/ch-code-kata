#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool checkSubRectangle(int m, int n, int M, int N, vector<vector<char>>& matrix) {
        int i = 0, j = 0;
        bool b = true;
        for(i = m; i <= m + M - 1; i++) {
            for(j = n; j <= n + N - 1; j++) {
                cout << "    positions: (" << i << ", " << j << "): " << matrix[i][j] << endl;
                if(matrix[i][j] != '1') {
                  b = false;
                  break;
                }
            }
            if(!b) break;
        }
        return b;
    }
    
    bool checkRectangleOfSize(int m, int n, int M, int N, vector<vector<char>>& matrix) {
        int i = 0, j = 0;
        bool found = false;
        for(i = 0; i <= M - m; i++) {
            for(j = 0; j <= N - n; j++) {
              cout << "  Rectangle starting from: (" << i << ", " << j << "): " << endl;
                found = checkSubRectangle(i, j, m, n, matrix);
                cout << "  Rectangle starting from: (" << i << ", " << j << "): " << found << endl;
                if(found) break;
            }
            if(found) break;
        }
        cout << endl;
        return found;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int max = 0;
        
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                cout << "Matrix of size: (" << i << ", " << j << "): " << (i * j) << endl;
                bool has = checkRectangleOfSize(i, j, m, n, matrix);
                if(has) {
                    max = (i * j > max ? i * j : max);
                }
            }
        }
        
        return max;
    }
};

int main() {
  Solution s;
  vector<vector<char>> matrix;
  char a1[5] = {'1','0','1','0','0'};
  char a2[5] = {'1','0','1','1','1'};
  char a3[5] = {'1','1','1','1','1'};
  char a4[5] = {'1','0','0','1','0'};
  matrix.push_back(vector<char>(a1, a1 + sizeof(a1)));
  matrix.push_back(vector<char>(a2, a2 + sizeof(a2)));
  matrix.push_back(vector<char>(a3, a3 + sizeof(a3)));
  matrix.push_back(vector<char>(a4, a4 + sizeof(a4)));

  int area = s.maximalRectangle(matrix);
  cout << endl << "Area: " << area << endl;
  return 0;
}