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

void contiguous(vector<int> &a, int &max, int s, int l, vector<int> &res) {
  int sum = 0;
  vector<int> curr;
  cout << "s: " << s << ", l: " << l << ", max: " << max << endl;
  for(int i = s; i < s + l; i++) {
    cout << "  i: " << i << ", a[i]: " << a[i] << endl;
    sum += a[i];
    curr.push_back(a[i]);
  }
  cout << "  sum: " << sum << endl << endl;
  if(sum > max) {
    max = sum;
    res = curr;
  }
}

vector<int> contiguous(vector<int> a) {
  int max = INT32_MIN;
  vector<int> res;
  for(int s = 0; s < a.size(); s++) {
    for(int l = 1; l <= a.size() - s; l++) {
      contiguous(a, max, s, l, res);
    }
  }
  return res;
}

int main(int argc, char **argv) {
  vector<int> a = {2,-8,3,-2,4,-10};
  vector<int> res = contiguous(a);
  cout << "Contiguous: ";
  for(auto r : res) {
    cout << r << ", ";
  }
  cout << endl;
  return 0;
}