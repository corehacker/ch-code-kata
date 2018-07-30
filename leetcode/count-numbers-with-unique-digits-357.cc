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
private:
  bool isUnique(int n) {
    unordered_set<int> s;
    while(n) {
      int d = n % 10;
      if(s.find(d) != s.end()) return false;
      s.insert(d);
      n = n / 10;
    }
    return true;
  }

public:
  int countNumbersWithUniqueDigits(int n) {
    int N = pow(10, n);
    int count = 0;
    for(int i = 0; i < N; i++) {
      if(isUnique(i)) count ++;
    }
    return count;
  }

  int countUnique(int n) {
    if(n == 0) return 1;
    int count = 10;
    if(n == 1) return count;
    int aggregate = 9;
    for(int i = 2; i <= n; i++) {
      aggregate = aggregate * (9 - i + 2);
      count += aggregate;
    }
    return count;
  }
};

int main() {
  Solution s;
  assert(1 == s.countUnique(0));
  assert(10 == s.countUnique(1));
  assert(91 == s.countUnique(2));

  for(int i = 3; i <= 10; i++) {
    cout << "Unique for 0 <= i < " << (int) pow(10, i) << " is: " << s.countUnique(i) << endl;
  }

  return 0;
}