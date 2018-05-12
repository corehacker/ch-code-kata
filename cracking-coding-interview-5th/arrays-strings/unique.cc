#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

bool unique1(string s) {
  if(!s.length()) return true;
  if(s.length() == 1) return true;

  unordered_map<char, int> count;
  bool unique = true;

  for(auto c : s) {
    count[c]++;
    if(count[c] == 2) {
      unique = false;
      break;
    }
  }
  return unique;
}

bool unique2(string s) {
  if(!s.length()) return true;
  if(s.length() == 1) return true;
  bool presence[26] = {false};
  bool unique = true;
  for(auto c : s) {
    if(presence[c - 'a']) {
      unique = false;
      break;
    }
    presence[c - 'a'] = true;
  }
  return unique;
}

bool unique(string s) {
  if(!s.length()) return true;
  if(s.length() == 1) return true;
  int presence = 0;
  bool unique = true;
  for(auto c : s) {
    int index = c - 'a';
    if(presence & (1 << index)) {
      unique = false;
      break;
    }
    presence |= (1 << index);
  }
  return unique;
}

int main() {
  vector<string> tests = {"abcde", "sandeep", "", "a", "aa", "ab"};
  vector<int> expected = {1, 0, 1, 1, 0, 1};
  int i = 0;
  for(auto s : tests) {
    bool result = unique(s);
    cout << "Unique \"" << s << "\": " << result << endl;
    assert(unique(s) == expected[i]);
    assert(unique1(s) == expected[i]);
    assert(unique2(s) == expected[i]);
    i++;
  }
  return 0;
}