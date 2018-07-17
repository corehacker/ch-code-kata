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

bool isClosing(char c) {
  return (c == ']' || c == '}' || c == ')') ? true : false;
}

bool isValidClosing(char closing, char opening) {
  if(closing == ')' && opening == '(') return true; 
  else if(closing == '}' && opening == '{') return true;
  else if(closing == ']' && opening == '[') return true;
  else return false;
}

bool isValid(string s) {
  vector<char> stack;
  for (auto c : s) {
    if (!isClosing(c)) {
      // cout << "char: " << c << endl;
      stack.push_back(c);
    } else {
      if(!stack.size()) return false;
      char val = stack.back();
      // cout << "char: " << c << ", " << val << endl;
      if (!isValidClosing(c, val))
        return false;
      stack.pop_back();
    }
  }
  return true;
}

void get(unordered_map<char, int> &map, vector<char> &keys,
          vector<string> &p, string perm, int n) {
  // cout << "string: " << s << endl;
  if(perm.length() == n && isValid(perm)) {
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

void recursive(int left, int right, string perm, vector<string> &p) {
  if(!left && !right) {
    cout << "permutation: " << perm << endl;
    p.push_back(perm);
  }

  if(left) recursive(left - 1, right, perm + ')', p);
  if(right) recursive(left + 1, right - 1, perm + '(', p);
}

void recursive(int n, vector<string> &p) {
  string perm;
  recursive(0, n, perm, p);
}


int main(int argc, char const *argv[]) {
  vector<string> p;
  string perm;
  int n = argc == 2 ? stoi(argv[1]) : 3;

  // string s;
  // for(int i = 0; i < n; i++) {
  //   s.push_back('(');
  //   s.push_back(')');
  // }
  // vector<char> keys;
  // unordered_map<char, int> map = create(s, keys);
  // get(map, keys, p, perm, s.length());

  recursive(n, p);

  cout << "Number of parenthesis: " << p.size() << endl;

  return 0;
}