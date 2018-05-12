#include <iostream>
#include <string>
#include <vector>


using namespace std;

bool isValid(vector< vector<unsigned long> > &grid, int rows, int cols) {
    if(rows == grid.size()) return false;
    if(cols == grid[rows].size()) return false;
    return true;
}

bool isEnd(vector< vector<unsigned long> > &grid, int rows, int cols) {
    if(rows == (grid.size() - 1) && cols == (grid[rows].size() - 1)) return true;
    return false;
}

unsigned long countPaths(vector< vector<unsigned long> > &grid, int rows, int cols) {
    if(!isValid(grid, rows, cols)) return 0;
    if(isEnd(grid, rows, cols)) return 1;
    if(grid[rows][cols] > 0) return grid[rows][cols];
    grid[rows][cols] = countPaths(grid, rows + 1, cols) + countPaths(grid, rows, cols + 1);
    return grid[rows][cols];
}

unsigned long countPaths(vector< vector<unsigned long> > &grid) {
    grid[grid.size() - 1][grid[0].size() - 1] = 1;
    for(int i = grid.size() - 1; i >= 0; i--) {
        for(int j = grid[i].size() - 1; j >= 0; j--) {
            if(i == grid.size() - 1 && j < grid[i].size() - 1)
                grid[i][j] = grid[i][j + 1];
            if(j == grid[i].size() - 1 && i < grid.size() - 1)
                grid[i][j] = grid[i + 1][j];
            if(i < grid.size() - 1 && j < grid[i].size() - 1)
                grid[i][j] = grid[i + 1][j] + grid[i][j + 1];

        }
    }
    return grid[0][0];
}

int main(int argc, char **argv) {
    int rows = 10;
    int cols = 10;

    if(argc == 3) {
        string arg = argv[1];
        rows = (stoi(arg) > 0 ? stoi(arg) : rows);
        arg = argv[2];
        cols = (stoi(arg) > 0 ? stoi(arg) : cols);
    }

    vector< vector<unsigned long> > grid;
    for(int i = 0; i < rows; i++) {
        vector<unsigned long> row(cols, 0);
        grid.push_back(row);
    }

    cout << "Paths (Recursive): " << countPaths(grid, 0, 0) << endl;
    cout << "Paths (DP): " << countPaths(grid) << endl;
    return 0;
}