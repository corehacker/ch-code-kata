#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

using namespace std;

int sum(vector<int> &a) {
  int sum = 0;
  for(auto i : a) {
    sum += i;
  }
  return sum;
}

vector<int> sumSwap(vector<int> &a1, vector<int> &a2) {
  int s1 = sum(a1), s2 = sum(a2);
  vector<int> res;

  for(auto i : a1) {
    for(auto j: a2) {
      int s11 = s1 - i + j, s22 = s2 - j + i;
      if(s11 == s22) {
        cout << "i: " << i << ", j: " << j << ", s11: " << s11 << ", s22: " << s22 << endl;
        res.push_back(i);
        res.push_back(j);
        return res;
      }
    }
  }

  return res;
}

bool getTarget(vector<int> &a1, vector<int> &a2, int &target) {
  int s1 = sum(a1), s2 = sum(a2);
  int diff = s1 > s2 ? s1 - s2 : s2 - s1;
  if(diff % 2 == 0) {
    target = s1 - s2 / 2;
    return true;
  } else {
    return false;
  }
}

unordered_set<int> getContents(vector<int> &a) {
  unordered_set<int> set;
  for(auto i : a) {
    set.insert(i);
  }
  return set;
}

vector<int> findDifference(vector<int> &a1, vector<int> &a2, int target) {
  vector<int> res;
  unordered_set<int> c2 = getContents(a2);
  cout << "set: ";
  for(auto i : c2) {
    cout << i << ", ";
  }
  cout << endl;
  for(auto i : a1) {
    int j = target - i;
    cout << "i: " << i << ", j: " << j << endl;
    if(c2.find(j) != c2.end()) {
      res.push_back(i);
      res.push_back(j);
      return res;
    }
  }
  return res;
}

vector<int> sumSwap2(vector<int> &a1, vector<int> &a2) {
  vector<int> res;
  int target = 0;
  if(!getTarget(a1, a2, target)) return res;
  cout << "target: " << target << endl;
  return findDifference(a1, a2, target);
}

int main() {
  vector<int> a1 = {4,1,2,1,1,2};
  vector<int> a2 = {3,6,3,3};
  vector<int> pair = sumSwap2(a1, a2);
  cout << "Pair: ";
  for(auto i : pair) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}