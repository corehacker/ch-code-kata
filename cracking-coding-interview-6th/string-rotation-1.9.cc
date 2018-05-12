#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>

using namespace std;

bool isRotation(string s, string t) {
  if(!s.length() && !t.length()) return true;
  if(s.length() != t.length()) return false;

  ostringstream os;
  os << t << t;
  string tt = os.str();
  int i = 0;
  while(i < tt.length()) {
    int j = 0;
    while(j < s.length()) {
      if(s[j] != tt[i + j])
        break;
      j++;
    }
    if(j == s.length()) {
      return true;
    }
    i++;
  }

  return false;
}


int main() {
  vector<string> s = {"", "", "abcde", "abcde", "a", "abcde", "waterbottle", "waterbottle", "waterbottle"};
  vector<string> t = {"", "a", "edcba", "abcd", "a", "eabcd", "erbottlewat", "waterbottle", "erbottlewate"};
  vector<bool> expected = {true, false, false, false, true, true, true, true, false};
  for(int i = 0; i < s.size(); i++) {
    bool result = isRotation(s[i], t[i]);
    cout << "Is rotation \"" << s[i] << "\", \"" << t[i] << "\"? " << result << endl << endl;
    assert(result == expected[i]);
  }

  return 0;
}