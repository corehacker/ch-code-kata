#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
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
private:
  void process(vector<string> &stack) {
    string str;
    string top;
    // print(stack);
    while(true) {
      top = stack.back();
      stack.pop_back();
      if((top[0] >= 'a' && top[0] <= 'z') || (top[0] >= 'A' && top[0] <= 'Z'))
        str.insert(0, top);
      else
        break;
    }
    // cout << "Top: " << top << endl;
    int count = stoi(top);
    string temp;
    while(count--) {
      temp += str;
    }
    // cout << "Temp: " << temp << endl;
    stack.push_back(temp);
  }

  void print(vector<string> &stack) {
    cout << "Stack: ";
    for(auto a: stack) {
      cout << a << ", ";
    }
    cout << endl << endl;
  }

public:
  string decodeString(string s) {
    string number, str;
    vector<string> stack;

    for(auto c: s) {
      // cout << "Processing " << c << ", str: " << str << ", number: " << number << endl;
      if(c >= '0' && c <= '9') {
        if(str.length()) {
          stack.push_back(str);
          str = "";
        }
        number += c;
      } else if(c == '[') {
        stack.push_back(number);
        number = "";
      } else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        str += c;
      } else {
        if(str.length()) {
          stack.push_back(str);
          str = "";
        }
        process(stack);
      }
      // print(stack);
    }
    if(str.length()) {
      stack.push_back(str);
      str = "";
    }
    string res;
    for(auto s: stack)
      res += s;
    return res;
  }
};

int main() {
  Solution s;
  cout << endl << s.decodeString("3[a]2[bc]");
  cout << endl << s.decodeString("3[a2[c]]");
  cout << endl << s.decodeString("2[abc]3[cd]ef");
  cout << endl << s.decodeString("2[abc]3[cd]ef2[abc]3[cd]ef");
  cout << endl << s.decodeString("3[a]2[b4[F]c]");
  return 0;
}