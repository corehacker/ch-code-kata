#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <regex>
#include <functional>

using namespace std;

#define WORDS_FILE "/usr/share/dict/words";



class WordCache {
private:
  unordered_map<string,bool> mWordMap;

public:
  WordCache() {
  }

  ~WordCache() {
  }

  void add(string &word) {
    mWordMap[word] = true;
  }

  void build() {
    string word;
    string file = WORDS_FILE;
    ifstream wd(file);
    while(getline(wd, word)) {
      if(word.length()) {
        add(word);
      }
    }
  }

  bool has(string &word) {
    return mWordMap[word];
  }
};

WordCache wc;

void print(vector<string> &v) {
  for(auto entry : v) {
    cout << entry << ", ";
  }
  cout << endl << endl;
}

string nearbyCharsForChar(char c) {
  unordered_map<char, string> NEARBY;
  NEARBY['g'] = "ghf";
  NEARBY['i'] = "iok";
  return NEARBY[c];
}

bool isWord(string &word) {
  return wc.has(word);
}

vector<string> buildNearbyCharsList(string &word) {
  vector<string> n;
  for(auto c : word) {
    n.push_back(nearbyCharsForChar(c));
  }
  return n;
}

void buildNearby(vector<string> &nearbyCharsList,
                 int index,
                 string &currentWord,
                 vector<string> &words) {
  if(index == nearbyCharsList.size()) {
    // cout << "End: " << currentWord << endl;
    if(isWord(currentWord)) {
      words.push_back(currentWord);
    }
    return;
  }

  for(int i = 0; i < nearbyCharsList[index].length(); i++) {
    // cout << "index: " << index << ", char: " << nearbyCharsList[index][i] << endl;
    currentWord += nearbyCharsList[index][i];
    buildNearby(nearbyCharsList, index + 1, currentWord, words);
    // currentWord[currentWord.length() - 1] = '\0';
    currentWord.pop_back();
  }
}

vector<string> nearby(string word) {
  vector<string> words;
  vector<string> nearbyCharsList = buildNearbyCharsList(word);
  // cout << "Nearby Chars List: "; print(nearbyCharsList);
  string currentWord = "";
  buildNearby(nearbyCharsList, 0, currentWord, words);
  return words;
}

int main() {
  wc.build();

  vector<string> n = nearby("gigigigigigigigigigigigigigigi");
  cout << "Nearby Words: "; print(n);

  return 0;
}