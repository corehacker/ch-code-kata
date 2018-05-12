#include <iostream>
#include <unordered_map>
#include <string.h>

using namespace std;

struct Node {
    unordered_map<char, Node *> children;
    bool word;
    Node() : word(false) {}
};

class Trie {
private:
    Node *root;
    
    void insert(Node *r, string word, int index) {
      if(index == word.length()) return;
      if(!r->children[word[index]]) {
        r->children[word[index]] = new Node();
      }
      if(index == word.length() - 1) 
        r->children[word[index]]->word = true;
      insert(r->children[word[index]], word, index + 1);
    }

    bool search(Node *r, string s, int index) {
      if(index == s.length()) return false;
      if(s[index] == '.') {
        bool found = false;
        for(auto &node : r->children) {
          found = search(node.second, s, index + 1);
          if(found) break;
          else {
            if(index == s.length() - 1 && node.second->word) {
              found = true;
              break;
            }
          }
        }
        return found;
      } else {
        if(!r->children[s[index]]) return false;
        if(index == s.length() - 1 && r->children[s[index]]->word) return true;
        return search(r->children[s[index]], s, index + 1);
      }
    }

    bool startsWith(Node *r, string s, int index) {
      if(index == s.length()) return true;
      if(!r->children[s[index]]) return false;
      return startsWith(r->children[s[index]], s, index + 1);
    }

    void print(Node *r, int depth) {
      depth = depth + 1;
      char format[1024] = "\0";
      for (uint32_t i = 0; i <= depth && i < sizeof(format); i++) {
          strncat(format, "  ", (sizeof(format) - (sizeof("  ") * i)));
      }

      for(auto &node : r->children) {
        printf ("%s%c\n", format, node.first);
        print(node.second, depth);
      }
    }
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new Node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        insert(root, word, 0);
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        return search(root, word, 0);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        return startsWith(root, prefix, 0);
    }

    void print() {
      print(root, 0);
    }
};

class WordDictionary {
private:
    Trie trie;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        trie.insert(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return trie.search(word);
    }

    void print() {
      trie.print();
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 * 
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 */

int main() {
  WordDictionary w;
  w.addWord("bad");
  w.addWord("dad");
  w.addWord("mad");
  w.print();
  cout << "Found? " << w.search("pad") << endl;
  cout << "Found? " << w.search("bad") << endl;
  cout << "Found? " << w.search(".ad") << endl;
  cout << "Found? " << w.search("b..") << endl;
  cout << "Found? " << w.search("b...") << endl;
  cout << "Found? " << w.search("b.d") << endl;
  cout << "Found? " << w.search("b.x") << endl;
  return 0;
}