#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

string remove(string s) {
  if(!s.length() || s.length() == 1) return s;

  string res = "";
  bool seen[26] = {false};
  for(auto c : s) {
    // cout << "seen[" << c << " - a]: " << seen[c - 'a'] << endl;
    if(seen[c - 'a']) continue;
    res += c;
    seen[c - 'a'] = true;
  }
  return res;
}

string remove1(string s) {
  if(!s.length() || s.length() == 1) return s;
  bool seen[26] = {false};
  int i = 0;
  int l = s.length();
  for(auto c : s) {
    if(seen[c - 'a']) continue;
    s[i++] = c;
    seen[c - 'a'] = true;
  }
  for(; i < l; i++) {
    s[i] = '\0';
  }
  cout << "Final: " << s << endl;
  return s;
}

int main() {
  vector<string> tests = {"", "a", "abcde", "abcade", "aabbccddee", "aaabbbcccdddeee", "abcdeabcdeabcde", "abcdeedcbaabcdeebcda"};
  vector<string> expected = {"", "a", "abcde", "abcde", "abcde", "abcde", "abcde", "abcde"};
  int i = 0;
  for(auto s : tests) {
    string s1 = s;
    string s2 = s;
    string result = remove(s);
    cout << "Removed \"" << s << "\": " << result << endl;
    assert(remove(s1) == expected[i]);
    assert(remove(s2) == expected[i]);
    i++;
  }

  return 0;
}