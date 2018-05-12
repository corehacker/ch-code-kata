#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>

using namespace std;

bool oneAway1(string s, string t) {
  if(!s.length() && !t.length()) return false;
  if(abs((int) (s.length() - t.length())) > 1) return false;
  int count[26] = {0};
  int i = 0;
  for(i = 0; i < s.length(); i++) {
    count[s[i] - 'a']++;
  }
  for(i = 0; i < t.length(); i++) {
    if(count[t[i] - 'a'] > 0) count[t[i] - 'a']--;
    else count[t[i] - 'a']++;
  }
  int c = 0;
  for(i = 0; i < 26; i++) {
    cout << count[i] << ", ";
    c += count[i];
  }
  cout << endl;
  return c > 0 && c <= 2 ? true : false;
}

bool checkReplace(string s, string t) {
  bool oneReplace = false;
  for(int i = 0; i < s.length(); i++) {
    if(s[i] != t[i]) {
      if(oneReplace)
        return false;
      oneReplace = true;
    }
  }
  return true;
}

bool checkInsert(string s, string t) {
  int i = 0, j = 0;
  cout << "(" << s << ", " << t << ")" << endl;
  while(i < s.length() && j < t.length()) {
    cout << "(" << i << ", " << j << ")" << endl;
    if(s[i] != t[j]) {
      if(i != j)
        return false;
      j++;
    } else {
      i++; j++;
    }
  }
  cout << "---(" << i << ", " << j << ")" << endl;
  return true;
}

bool oneAway(string s, string t) {
  if(!s.length() && !t.length()) return false;
  if(s.length() == t.length())
    return checkReplace(s, t);
  else if (s.length() + 1 == t.length())
    return checkInsert(s, t);
  else if (s.length() - 1 == t.length())
    return checkInsert(t, s);
  return false;
}


int main() {
  vector<string> s = {"", "", "abcde", "abcde", "abcde", "abcde", "pale", "pale", "pales", "pale", "pale", "apple"};
  vector<string> t = {"", "a", "edcba", "abcd", "abcdee", "uvwxy", "ale", "pales", "pale", "bake", "bale", "aple"};
  vector<bool> expected = {false, true, false, true, true, false, true, true, true, false, true, true};
  for(int i = 0; i < s.size(); i++) {
    bool result = oneAway(s[i], t[i]);
    cout << "One Away \"" << s[i] << "\", \"" << t[i] << "\"? " << result << endl << endl;
    assert(result == expected[i]);
  }

  return 0;
}