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

#define WORDS_FILE "/usr/share/dict/words-lower.txt";

struct Node {
  unordered_map<char, Node *> map;
  bool word;
  Node() : word(false) {}
};

class Trie {
private:
  Node *head;
  unordered_map<char, unordered_map<char, char>> digits;

  bool addChar(Node *head, string &word, int i) {
    if(i == word.length()) {
      return true;
    }
    Node *entry = nullptr;
    if(!head->map[word[i]]) {
      entry = new Node();
      head->map[word[i]] = entry;
    } else {
      entry = head->map[word[i]];
    }
    bool end = addChar(entry, word, i + 1);
    if(end) {
      entry->word = true;
    }
    return false;
  }

  string indent(int spaces) {
    ostringstream os;
    while(spaces--)
      os << " ";
    return os.str();
  }

  void print(Node *head, int spaces) {
    for(auto entry : head->map) {
      if(entry.second) {
        cout << indent(spaces) << entry.first << (entry.second->word ? "*" : "") << endl;
        print(entry.second, spaces + 1);
      }
    }
  }

  string buildWord(vector<char> &curr) {
    ostringstream os;
    for(auto c : curr)
      os << c;
    cout << os.str() << endl;
    return os.str();
  }

  bool mappings(Node *head, string &input, int i, vector<char> &curr, vector<string> &res) {
    if(i == input.length() && head->word) return true;

    if(i == input.length()) return false;

    for(auto cForN: digits[input[i]]) {
      if(head->map[cForN.first]) {
        curr.push_back(cForN.first);
        bool isWord = mappings(head->map[cForN.first], input, i + 1, curr, res);
        if(isWord) {
          res.push_back(buildWord(curr));
        }
        curr.pop_back();
      }
    }
  }

public:
  Trie() {
    head = new Node();
  }

  void addWord(string word) {
    addChar(head, word, 0);
  }

  void print() {
    print(head, 0);
  }

  void build() {
    string word;
    string file = WORDS_FILE;
    ifstream wd(file);
    while(getline(wd, word)) {
      if(word.length()) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        addWord(word);
      }
    }

    unordered_map<char, char> entry;
    entry['a'] = '2';
    entry['b'] = '2';
    entry['c'] = '2';
    digits['2'] = entry;

    entry.clear();
    entry['d'] = '3';
    entry['e'] = '3';
    entry['f'] = '3';
    digits['3'] = entry;

    entry.clear();
    entry['g'] = '4';
    entry['h'] = '4';
    entry['i'] = '4';
    digits['4'] = entry;

    entry.clear();
    entry['j'] = '5';
    entry['k'] = '5';
    entry['l'] = '5';
    digits['5'] = entry;

    entry.clear();
    entry['m'] = '6';
    entry['n'] = '6';
    entry['o'] = '6';
    digits['6'] = entry;

    entry.clear();
    entry['p'] = '7';
    entry['q'] = '7';
    entry['r'] = '7';
    entry['s'] = '7';
    digits['7'] = entry;

    entry.clear();
    entry['t'] = '8';
    entry['u'] = '8';
    entry['v'] = '8';
    digits['8'] = entry;

    entry.clear();
    entry['w'] = '9';
    entry['x'] = '9';
    entry['y'] = '9';
    entry['z'] = '9';
    digits['9'] = entry;
  }

  vector<string> mappings(string digits) {
    vector<string> res;
    vector<char> curr;
    mappings(head, digits, 0, curr, res);
    cout << endl;
    return res;
  }
};

int main(int argc, char **argv) {
  Trie t;
  t.build();
  // t.print();

  if(argc == 2) {
    t.mappings(argv[1]);
  } else {
    t.mappings("2229566426");
  }

  return 0;
}