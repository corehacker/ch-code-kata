#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

#include "graphs.hh"

using namespace std;

void countSteps(vector<int> &steps, int n, int &count) {
  if(n < 0) return;
  if(n == 0) {
    count++;
    return;
  }
  for(int i = 0; i < steps.size(); i++) {
    countSteps(steps, n - steps[i], count);
  }
}

int countSteps(int n, vector<int> &memo) {
  if(n < 0) return 0;
  if(n == 0) return 1;
  if(memo[n]) return memo[n];
  else {
     memo[n] = countSteps(n - 1, memo) + countSteps(n - 2, memo) + countSteps(n - 3, memo);
  }
}

int main(int argc, char const *argv[])
{
  int n = (argc == 2 ? stoi(argv[1]) : 3);
  vector<int> steps = {1,2,3};
  vector<int> memo(n + 1, 0);
  cout << "Count: " << countSteps(n, memo) << endl;
  return 0;
}
