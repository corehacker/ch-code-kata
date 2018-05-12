#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

#define CHAR_COUNT (256)

bool palindromePermutation(string s) {
  if(!s.length()) return false;

  int count1[CHAR_COUNT] = {0};
  int i = 0;
  int oneCount = 0;
  int count = 0;
  for(i = 0; i < s.length(); i++) {
    if(s[i] == ' ') continue;
    count1[s[i]]++;
  }
  for(i = 0; i < CHAR_COUNT; i++) {
    if(count1[i] == 1) oneCount++;
    else if(count1[i] % 2 == 0) count++;
    else break;
  }
  if(i < CHAR_COUNT) return false;
  return oneCount <= 1 ? true : false;
}

int main() {
  vector<string> s = {"", "a", "abcde", "tact coa", "madam", "mad am", "tact coat", "tactcoapapa"};
  vector<bool> expected = {false, true, false, true, true, true, false, true};
  for(int i = 0; i < s.size(); i++) {
    cout << "Palindrome Permutation \"" << s[i] << "\"? " << 
      palindromePermutation(s[i]) << endl;
    assert(palindromePermutation(s[i]) == expected[i]);
  }

  return 0;
}