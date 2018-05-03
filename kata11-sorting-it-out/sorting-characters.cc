#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <cstdlib>
#include <vector>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <cctype>

using namespace std;

// Input:
// When not studying nuclear physics, Bambi likes to play
// beach volleyball.
//
// Expected:
// aaaaabbbbcccdeeeeeghhhiiiiklllllllmnnnnooopprsssstttuuvwyyyy
//
// Output:
// aaaaabbbbcccdeeeeeghhhiiiiklllllllmnnnnooopprsssstttuuvwyyyy

int main() {
  unordered_map<char, string> map;
  string text = "When not studying nuclear physics, Bambi likes to play\n"
    "beach volleyball.";

  for(auto &c : text) {
    if(isalpha(c)) {
      char cc = tolower(c);
      map[cc] += cc;
    }
  }

  for(char i = 'a'; i <= 'z'; i++) {
    if(map[i].length()) {
      cout << map[i];
    }
  }
  cout << endl;

  return 0;
}