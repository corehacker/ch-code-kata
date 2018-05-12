#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

bool anagram(string s, string t) {
  bool a = true;
  int c1[26] = {0}, c2[26] = {0};
  for(auto c : s) {
    c1[c - 'a']++;
  }
  for(auto c : t) {
    c2[c - 'a']++;
  }
  for(int i = 0; i < 26; i++) {
    if(c1[i] != c2[i]) {
      a = false;
      break;
    }
  }
  return a;
}

int main() {
  vector<string> s = {"", "a", "abcde", "abcde", "abcde", "abcde"};
  vector<string> t = {"", "a", "edcba", "abcd", "abcdee", "uvwxy"};
  vector<bool> expected = {true, true, true, false, false, false};
  for(int i = 0; i < s.size(); i++) {
    cout << "Anagrams \"" << s[i] << "\", \"" << t[i] << "\"? " << anagram(s[i], t[i]) << endl;
    assert(anagram(s[i], t[i]) == expected[i]);
  }

  return 0;
}