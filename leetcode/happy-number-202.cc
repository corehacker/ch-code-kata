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

class Solution {
  int sumOfSquares(int n) {
    int sum = 0;
    while(n) {
      int digit = n % 10;
      int square = digit * digit;
      sum += square;
      n = n / 10;
    }
    return sum;
  }
public:
    bool isHappy(int n) {
        int sum = n;
        unordered_set<int> seen;
        cout << "sum: " << sum << endl;
        while(true) {
          seen.insert(sum);
          sum = sumOfSquares(sum);
          cout << "sum: " << sum << endl;
          if(seen.find(sum) != seen.end()) return false;
          if(1 == sum) return true;
        }
    }
};


int main(int argc, char **argv) {
  Solution s;
  s.isHappy(argc == 2 ? atoi(argv[1]) : 19);
  return 0;
}