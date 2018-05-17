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
      cout << "char: " << c << endl;
      stack.push_back(c);
    } else {
      char val = stack.back();
      cout << "char: " << c << ", " << val << endl;
      if (!isValidClosing(c, val))
        return false;
      stack.pop_back();
    }
  }
  return true;
}

int main() {
  cout << "Valid? " << isValid("()()[][][][][][[[]]]") << endl;
  return 0;
}