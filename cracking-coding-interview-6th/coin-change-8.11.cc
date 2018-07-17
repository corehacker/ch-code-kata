#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

int coin(vector<int> &coins, int amount) {
  vector<int> memo(amount + 1);
  memo[0] = 1;

  for(auto c : coins) {
    for(int i = 1; i <= amount; i++) {
      if(i >= c)
        memo[i] += memo[i - c];
    }
  }
  return memo[amount];
}

int main() {
  vector<int> coins = {1,2,5};
  int amount = 5;
  cout << "Ways: " << coin(coins, amount) << endl;
  return 0;
}