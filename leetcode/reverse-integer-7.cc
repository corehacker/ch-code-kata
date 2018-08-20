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
public:
    int reverse(int x) {
        long result = 0;
        bool negative = x < 0 ? true : false;
        vector<int> digits;
        x = negative ? (-1 * x) : x;
        while(x) {
            int digit = x % 10;
            digits.push_back(digit);
            x = x / 10;
        }
        int power = 0;
        while(digits.size()) {
            int multiplier = !power ? 1 : power;
            int d = digits.back();
            long addition = (long) d * multiplier;
            int remaining = INT32_MAX - result;
            // cout << "digit: " << d <<
            //   ", multiplier: " << multiplier << 
            //   ", addition: " << addition << 
            //   ", remaining:" << remaining << 
            //   ", result: " << result << endl;
            if(addition > remaining) return 0;
            result += addition;
            // if(result > INT32_MAX) return 0;
            // if(result < 0) return 0;
            power = multiplier * 10;
            digits.pop_back();
        }
        return negative ? (-1 * result) : result;
    }
};

int main() {
  Solution s;
  cout << s.reverse(1534236469) << endl;
  cout << s.reverse(9999999999) << endl;
  return 0;
}