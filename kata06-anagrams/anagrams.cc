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

using namespace std;

#define WORDS_FILE "./wordlist.txt";

int main() {
  string word;
  unordered_map<string, vector<string>> wordMap;
  string file = WORDS_FILE;
  ifstream wd(file);
  while(getline(wd, word)) {
    if(word.length()) {
      string sorted = word;
      sort(sorted.begin(), sorted.end());
      // cout << word << " | " << sorted << endl;
      wordMap[sorted].push_back(word);
    }
  }

  uint32_t count = 0;
  uint32_t most = 0;
  uint32_t longest = 0;
  string l;
  string m;
  for(auto &entry : wordMap) {
    size_t size = entry.second.size();
    if(size > 1) {
      count++;
      if(size > most) {
        most = size;
        m = entry.first;
      }
      size_t length = entry.second[0].length();
      if(length > longest) {
        longest = length;
        l = entry.first;
      }
    }
  }
  cout << "Count: " << count << ", Most: " << most << ", Longest: " << longest <<  endl;
  for(auto &entry : wordMap[m]) {
    cout << entry << ", ";
  }
  cout << endl;
  for(auto &entry : wordMap[l]) {
    cout << entry << ", ";
  }
  cout << endl;

  return 0;
}

