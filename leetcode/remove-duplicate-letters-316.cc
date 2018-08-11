#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <fstream>
#include <algorithm>

using namespace std;


class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> letters;
        for(int i = 0; i < s.length(); i++) {
          letters[s[i]] = i;
        }
        for(auto entry : letters) {
          cout << entry.first << ": " << entry.second << endl;
        }

        return "";
    }
};

int main() {
  Solution s;
  s.removeDuplicateLetters("cbacdcbc");
  // cout << "removed: " << endl;
  return 0;
}