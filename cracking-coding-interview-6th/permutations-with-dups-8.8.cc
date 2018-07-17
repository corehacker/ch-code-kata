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
#include <unistd.h>

#include "graphs.hh"

using namespace std;

void get(unordered_map<char, int> &map, vector<char> &keys,
          vector<string> &p, string perm, int n) {
  // cout << "string: " << s << endl;
  if(perm.length() == n) {
    cout << "permutation: " << perm << endl;
    p.push_back(perm);
    return;
  }

  for(auto c : keys) {
    int count = map[c];

    if(count > 0) {
      map[c] = count - 1;
      get(map, keys, p, (perm + c), n);
      map[c] = count;
    }
    // sleep(1);
  }

  // cout << endl;
}

unordered_map<char, int> create(string &s, vector<char> &keys) {
  unordered_map<char, int> map;
  for(auto c : s) {
    if(map.find(c) == map.end()) {
      map.insert(make_pair(c, 1));
      keys.push_back(c);
    } else {
      int i = map[c];
      map[c] = i + 1;
    }
  }
  return map;
}

int main(int argc, char const *argv[]) {
  vector<string> p;
  string perm;
  string s = argc == 2 ? argv[1] : "abcde";
  vector<char> keys;
  unordered_map<char, int> map = create(s, keys);
  get(map, keys, p, perm, s.length());

  cout << "Number of permutations: " << p.size() << endl;

  return 0;
}