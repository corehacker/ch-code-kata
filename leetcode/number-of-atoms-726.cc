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
  void processAtom(string &atom, string &atomCount, vector<string> &stack) {
    if(!atom.length()) return;
    int count = 1;
    if(atomCount.length()) count = stoi(atomCount);
    while(count--) {
      stack.push_back(atom);
    }
    atom = "";
    atomCount = "";
  }

  void process(vector<string> &stack, string &multiplier) {
    int m = multiplier.length() ? stoi(multiplier) : 1;
    vector<string> stage;
    while(true) {
      string atom = stack.back();
      stack.pop_back();
      // cout << "staging " << atom << " " << m << " times" << endl;
      if(atom == "(") break;
      int M = m;
      while(M--) {
        stage.push_back(atom);
      }
    }
    for(int i = stage.size() - 1; i >= 0; i--) {
      stack.push_back(stage[i]);
    }
    multiplier = "";
  }
  void printStack(vector<string> &stack) {
    cout << "Stack: ";
    for(auto s: stack) {
      cout << s << ", ";
    }
    cout << endl << endl;
  }
public:
  string countOfAtoms(string formula) {
    string atom, atomCount, multiplier;
    bool mult = false;
    vector<string> stack;

    for(auto c : formula) {
      // cout << "Processing " << c << ", atom: " << atom << 
      //   ", count: " << atomCount << ", multiplier: " << multiplier << endl;
      if(c >= 'A' && c <= 'Z') {
        if(mult) {
          process(stack, multiplier);
          // cout << "Multiplier after processing: " << multiplier << endl;
          mult = false;
        }
        processAtom(atom, atomCount, stack);
        atom += c;
      } else if(c >= 'a' && c <= 'z') {
        atom += c;
      } else if(c >= '0' && c <= '9') {
        if(mult) {
          // process(stack, multiplier);
          // cout << "Multiplier after processing: " << multiplier << endl;
          multiplier += c;
        } else {
          atomCount += c;
        }
      } else if(c == '(') {
        if(mult) {
          process(stack, multiplier);
          // cout << "Multiplier after processing: " << multiplier << endl;
          mult = false;
        }
        processAtom(atom, atomCount, stack);
        stack.push_back("(");
      } else {
        if(mult) {
          process(stack, multiplier);
          // cout << "Multiplier after processing: " << multiplier << endl;
          mult = false;
        }
        processAtom(atom, atomCount, stack);
        mult = true;
      }
      // printStack(stack);
    }
    if(mult) {
      // cout << "Final mult: " << multiplier << endl;
      process(stack, multiplier);
      mult = false;
    }
    processAtom(atom, atomCount, stack);
    // printStack(stack);

    map<string, int> atoms;
    for(auto a : stack) {
      if(atoms.find(a) == atoms.end()) {
        atoms[a] = 1;
      } else {
        atoms[a]++;
      }
    }

    for(auto entry : atoms) {
      cout << entry.first << ": " << entry.second << endl;
    }
    cout << endl;
    return "";
  }
};

int main() {
  Solution s;
  s.countOfAtoms("H2O");
  s.countOfAtoms("Mg(OH)2");
  s.countOfAtoms("K4(ON(SO3)2)2");
  s.countOfAtoms("(K4(ON(SO3)2)2)");
  s.countOfAtoms("(K4(ON(SO3)2)2)2");
  s.countOfAtoms("(K4(ON(SO3)2)2)2K");
  s.countOfAtoms("(K4(ON(SO3)2)2)2K2");
  s.countOfAtoms("(K4(ON(S(Z2Y2)O3)2)2)2K2(G3R4)");
  s.countOfAtoms("(Ka4(ObNc(Sd(Ze2Yf2)Og3)2)2)2Kh2(Gi3Rj4)");
  return 0;
}