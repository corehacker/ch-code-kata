#include <iostream>
#include <vector>
#include <cstdint>
#include <unistd.h>
#include <cassert>

using namespace std;

class Solution {
private:
  int countOnes(int n) {
    int count = 0;
    while(n > 0) {
      int d = n % 10;
      if(d == 1) count++;
      n = n / 10;
    }
    return count;
  }
public:
  int countDigitOne(int n) {
    int count = 0;
    for(int i = 1; i <= n; i++) {
      count += countOnes(i);
    }
    return count;
  }
};


int main() {
  Solution s;
  vector<int> inputs = {1, 13, 4000};
  vector<int> outputs = {1, 6, 100};

  for(int i = 0; i < inputs.size(); i++) {
    int output = s.countDigitOne(inputs[i]);
    cout << "Count for " << inputs[i] << ": " << output << endl;
    assert(output == outputs[i]);
  }
  
}