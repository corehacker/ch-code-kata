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

#include "graphs.hh"

using namespace std;

vector<int> generate(vector<int> &set, int k) {
  int count = 0;
  vector<int> picked;
  while(count < set.size() && k) {
    int pick = (k & 0x1);
    if(pick) picked.push_back(set[count]);
    count++;
    k = k >> 1;
  }
  return picked;
}

vector<vector<int>> generate(vector<int> &set) {
  vector<vector<int>> power;
  int n = pow(2, set.size());
  cout << "Power set has " << n << " sets" << endl;

  for(int i = 0; i < n; i++) {
    vector<int> current = generate(set, i);
    power.push_back(current);
  }
  return power;
}

void print(vector<vector<int>> &powerset) {
  for(auto entry : powerset) {
    for(auto e : entry) {
      cout << e << ", ";
    }
    cout << endl;
  }
}

int main(int argc, char const *argv[])
{
  int n = (argc == 2 ? stoi(argv[1]) : 3);
  vector<int> set = {1,2,3,4,5};
  vector<vector<int>> powerset = generate(set);
  cout << "Count: " << powerset.size() << endl;
  print(powerset);
  return 0;
}