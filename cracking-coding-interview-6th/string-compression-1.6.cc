#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>

using namespace std;

string compress(string s) {
  ostringstream os;
  char c = '\0';
  int count = 0;

  for(auto ch : s) {
    if(ch != c) {
      if(count) {
        os << c << count;
        count = 0;
      }
      c = ch;
      count++;
    } else {
      count++;
    }
  }
  if(count) {
    os << c << count;
  }
  return os.str().length() > s.length() ? s : os.str();
}

int main() {
  vector<string> tests = {"", "a", "abcde", "this is a sentence with spaces", "aabcccccaa"};
  vector<string> expected = {"", "a", "abcde", "this is a sentence with spaces", "a2b1c5a2"};
  int i = 0;
  for(auto s : tests) {
    cout << "Replace \"" << s << "\": \"" << compress(s) << "\"" << endl;
    assert(compress(s) == expected[i]);
    i++;
  }

  return 0;
}