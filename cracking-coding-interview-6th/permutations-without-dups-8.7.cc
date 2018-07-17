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

void get(string s, vector<string> &p, string &perm) {
  // cout << "string: " << s << endl;
  if(!s.length()) {
    // cout << "permutation: " << perm << endl;
    p.push_back(perm);
    return;
  }
  int l = s.length();
  for(int i = 0; i < s.length(); i++) {
    char c = s[i];
    // cout << "Pushing " << c << ", i: " << i << endl;
    perm.push_back(c);

    string start = s.substr(0, i);
    string end = s.substr(i + 1, (l - i));

    get(start + end, p, perm);

    // cout << "Popping " << c << endl;
    perm.pop_back();
    // sleep(1);
  }

  // cout << endl;
}

int main(int argc, char const *argv[]) {
  vector<string> p;
  string perm;
  get(argc == 2 ? argv[1] : "abcde", p, perm);

  cout << "Number of permutations: " << p.size() << endl;

  return 0;
}