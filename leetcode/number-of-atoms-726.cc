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

  void processMultiplier(vector<string> &stack, string &multiplier) {
    int m = multiplier.length() ? stoi(multiplier) : 1;
    vector<string> stage;
    while(true) {
      string atom = stack.back();
      stack.pop_back();
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

  void process(string &atom, string &atomCount, vector<string> &stack, string &multiplier, bool &mult) {
    if(mult) {
      processMultiplier(stack, multiplier);
      mult = false;
    }
    processAtom(atom, atomCount, stack);
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
      if(c >= 'A' && c <= 'Z') {
        process(atom, atomCount, stack, multiplier, mult);
        atom += c;
      } else if(c >= 'a' && c <= 'z') {
        atom += c;
      } else if(c >= '0' && c <= '9') {
        if(mult) {
          multiplier += c;
        } else {
          atomCount += c;
        }
      } else if(c == '(') {
        process(atom, atomCount, stack, multiplier, mult);
        stack.push_back("(");
      } else {
        process(atom, atomCount, stack, multiplier, mult);
        mult = true;
      }
    }
    process(atom, atomCount, stack, multiplier, mult);

    map<string, int> atoms;
    for(auto a : stack) {
      if(atoms.find(a) == atoms.end()) {
        atoms[a] = 1;
      } else {
        atoms[a]++;
      }
    }

    ostringstream os;
    for(auto entry : atoms) {
        os << entry.first << (entry.second == 1 ? "" : to_string(entry.second));
    }
    return os.str();
  }
};

int main() {
  Solution s;
  cout << endl << s.countOfAtoms("H2O");
  cout << endl << s.countOfAtoms("Mg(OH)2");
  cout << endl << s.countOfAtoms("K4(ON(SO3)2)2");
  cout << endl << s.countOfAtoms("(K4(ON(SO3)2)2)");
  cout << endl << s.countOfAtoms("(K4(ON(SO3)2)2)2");
  cout << endl << s.countOfAtoms("(K4(ON(SO3)2)2)2K");
  cout << endl << s.countOfAtoms("(K4(ON(SO3)2)2)2K2");
  cout << endl << s.countOfAtoms("(K4(ON(S(Z2Y2)O3)2)2)2K2(G3R4)");
  cout << endl << s.countOfAtoms("(Ka4(ObNc(Sd(Ze2Yf2)Og3)2)2)2Kh2(Gi3Rj4)");
  cout << endl << s.countOfAtoms("(((U42Se42Fe10Mc31Rh49Pu49Sb49)49V39Tm50Zr44Og6)33((W2Ga48Tm14Eu46Mt12)23(RuRnMn11)7(Yb15Lu34Ra19CuTb2)47(Md38BhCu48Db15Hf12Ir40)7CdNi21(Db40Zr24Tc27SrBk46Es41DsI37Np9Lu16)46(Zn49Ho19RhClF9Tb30SiCuYb16)15)37(Cr48(Ni31)25(La8Ti17Rn6Ce35)36(Sg42Ts32Ca)37Tl6Nb47Rh32NdGa18Cm10Pt49(Ar37RuSb30Cm32Rf28B39Re7F36In19Zn50)46)38(Rh19Md23No22PoTl35Pd35Hg)41)50");
  return 0;
}