#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;

// string replace1(string s) {
//   string res = "";

//   for(auto c: s) {
//     if(c == ' ') {
//       res += "%20";
//     } else {
//       res += c;
//     }
//   }

//   return res;
// }

string replace(string s) {
  int l = s.length();
  int count = 0;
  for(int i = 0; i < l; i++) {
    if(s[i] == ' ') {
      count++;
    }
  }
  if(!count) return s;
  int diff = (3 * count) - count;
  for(int i = 0; i < diff; i++) {
    s += " ";
  }

  int ll = s.length();
  int j = ll - 1;
  for(int i = l - 1; i >= 0; i--) {
    if(s[i] == ' ') {
      s[j--] = '0';
      s[j--] = '2';
      s[j--] = '%';
    } else {
      s[j--] = s[i];
    }
  }
  return s;
}

int main() {
  vector<string> tests = {"", "a", "abcde", "this is a sentence with spaces.", "   ", " ", "      "};
  vector<string> expected = {"", "a", "abcde", "this%20is%20a%20sentence%20with%20spaces.", "%20%20%20", "%20", "%20%20%20%20%20%20"};
  int i = 0;
  for(auto s : tests) {
    cout << "Replace \"" << s << "\": \"" << replace(s) << "\"" << endl;
    assert(replace(s) == expected[i]);
    i++;
  }

  return 0;
}