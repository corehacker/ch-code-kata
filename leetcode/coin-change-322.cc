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
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memo(amount + 1, amount + 1);
        memo[0] = 0;
        for(int i = 1; i <= amount; i++) {
          for(auto c: coins) {
            if(c <= i) {
              memo[i] = min(memo[i], memo[i - c] + 1);
            }
          }
        }
        return memo[amount] > amount ? -1 : memo[amount];
    }
};

int main() {
  Solution s;
  vector<int> coins = {186,419,83,408};
  // coins = {1, 2, 5};
  int num = s.coinChange(coins, 6249);
  // int num = s.coinChange(coins, 11);
  cout << "min coins: " << num << endl;
  return 0;
}