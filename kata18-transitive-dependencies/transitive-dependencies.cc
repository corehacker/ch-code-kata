#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;

struct DependencyNode {
  unordered_set<DependencyNode *> dependents;
  string label;


  DependencyNode(string &label) {
    this->label = label;
  }

  void add(DependencyNode *dependency) {
    dependents.insert(dependency);
  }
};

class DependencyManager {
private:
  unordered_map<string, DependencyNode *> map;

  void get(DependencyNode *dependency, unordered_set<string> &result) {
    for(auto &dependent : dependency->dependents) {
      if(result.find(dependent->label) == result.end()) {
        result.insert(dependent->label);
        get(dependent, result);
      }
    }
  }

  void print(DependencyNode *dependency, uint32_t depth) {
    depth = depth + 1;
    char format[1024] = "\0";
    for (uint32_t i = 0; i <= depth && i < sizeof(format); i++) {
        strncat(format, "  ", (sizeof(format) - (sizeof("  ") * i)));
    }

    printf ("%s%s\n", format, dependency->label.data());
    for(auto dependent : dependency->dependents) {
        print (dependent, depth);
    }
  }

  void add_(string &label, string &dependent) {
    if(!map[label]) {
      map[label] = new DependencyNode(label);
    }
    if(!map[dependent]) {
      map[dependent] = new DependencyNode(dependent);
    }
    map[label]->add(map[dependent]);
  }

public:
  void add(string label, string dependent) {
    add_(label, dependent);
  }

  unordered_set<string> get(string &label) {
    unordered_set<string> result;
    if(map[label]) {
      get(map[label], result);
    }
    return result;
  }

  void print() {
    for(auto &entry : map) {
      print(entry.second, 0);
    }
  }

  void print(string label) {
    unordered_set<string> result =  get(label);
    cout << "Dependencies for \"" << label << "\": ";
    for(auto &label : result) {
      cout << label << " ";
    }
    cout << endl;
  }
};

int main() {
  DependencyManager manager;

  /*
    dep = Dependencies.new
    dep.add_direct('A', %w{ B C } )
    dep.add_direct('B', %w{ C E } )
    dep.add_direct('C', %w{ G   } )
    dep.add_direct('D', %w{ A F } )
    dep.add_direct('E', %w{ F   } )
    dep.add_direct('F', %w{ H   } )
  */
  // manager.add("A", "B");
  // manager.add("A", "C");
  // manager.add("B", "C");
  // manager.add("B", "E");
  // manager.add("C", "G");
  // manager.add("D", "A");
  // manager.add("D", "F");
  // manager.add("E", "F");
  // manager.add("F", "H");
  // manager.print("A");
  // manager.print("B");
  // manager.print("C");
  // manager.print("D");
  // manager.print("E");
  // manager.print("F");

  /*
    A B
    B C
    C A
  */
  manager.add("A", "B");
  manager.add("B", "C");
  manager.add("C", "A");
  manager.print("A");
  manager.print("B");
  manager.print("C");
  return 0;
}