#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

string reverse(string s) {
  if(!s.length() || s.length() == 1) return s;
  int l = s.length();
  for(int i = 0; i < (l - 1) / 2; i++) {
    auto c = s[i];
    s[i] = s[l - 1 - i];
    s[l - 1 - i] = c;
  }
  return s;
}


int main() {
  vector<string> tests = {"", "a", "abcde"};
  vector<string> expected = {"", "a", "edcba"};
  int i = 0;
  for(auto s : tests) {
    string result = reverse(s);
    cout << "Reverse \"" << s << "\": " << result << endl;
    assert(reverse(s) == expected[i]);
    // assert(unique1(s) == expected[i]);
    // assert(unique2(s) == expected[i]);
    i++;
  }

  return 0;
}