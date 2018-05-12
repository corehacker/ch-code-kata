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
      if(!r->children[s[index]]) return false;
      if(index == s.length() - 1 && r->children[s[index]]->word) return true;
      return search(r->children[s[index]], s, index + 1);
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

int main() {
  Trie t;
  t.insert("someword");
  t.insert("someotherword");
  t.print();
  cout << "Found? " << t.search("someword") << endl;
  cout << "Found? " << t.search("someword1") << endl;
  cout << "Found? " << t.search("a") << endl;
  cout << "Found? " << t.search("s") << endl;
  cout << "Found? " << t.search("someotherword") << endl;
  cout << "Starts with? " << t.startsWith("some") << endl;
  cout << "Starts with? " << t.startsWith("some1") << endl;
  cout << "Starts with? " << t.startsWith("someword") << endl;
  cout << "Starts with? " << t.startsWith("someother") << endl;
  cout << "Starts with? " << t.startsWith("someotherword") << endl;
  cout << "Starts with? " << t.startsWith("a") << endl;
  return 0;
}