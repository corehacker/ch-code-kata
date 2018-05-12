#include <unordered_map>
#include <string>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
    int key;
    int value;
    Node *next;
    Node *prev;
    Node(int k, int v) : key(k), value(v), next(nullptr), prev(nullptr) {}
    void reset() {
        next = nullptr;
        prev = nullptr;
    }
};

class LRUList {
private:
    Node *head;
    Node *tail;

public:
    LRUList() : head(nullptr), tail(nullptr) {}

    void push_back(Node *node) {
        if(!head && !tail) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    Node *pop_front() {
        if(!head && !tail) {
            return nullptr;
        } else {
            Node *ret = head;
            head = head->next;
            if(head) head->prev = nullptr;
            if(!head) tail = nullptr;
            return ret;
        }
    }

    void remove(Node *node) {
        if(!node) return;
        if(node == head && node == tail) {
            head = nullptr;
            tail = nullptr;
        } else if (node == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (node == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
    }

    void print() {
        Node *curr = head;
        if(!head && !tail) cout << "[EMPTY]";
        if(head) cout << "[" << head->key << ", " << head->value << "] ";
        while(curr) {
            cout << "(" << curr->key << ", " << curr->value << "), ";
            curr = curr->next;
        }
        if(tail) cout << "[" << tail->key << ", " << tail->value << "] ";
        cout << endl;
    }
};

class LRUCache {
private:
    unordered_map<int,Node *> map;
    LRUList list;
    size_t capacity;

    bool full() {
        return capacity == map.size() ? true : false;
    }

public:
    LRUCache(int cap) : capacity((size_t) cap) {
    }

    int get(int key) {
        if(map.find(key) == map.end()) return -1;
        Node *node = map[key];
        list.remove(node);
        node->reset();
        list.push_back(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if(capacity <= 0) return;
        Node *node = nullptr;
        if(map.find(key) == map.end()) {
            if(full()) {
                Node *rem = list.pop_front();
                cout << "Popped from front!" << endl;
                map.erase(rem->key);
                delete rem;
            }
            node = new Node(key, value);
            list.push_back(node);
            map.insert(make_pair(key, node));
        }
    }

    void print() {
        cout << "List: ";
        list.print();

        cout << "[START] Map: " << endl;
        for(auto &entry : map) {
            cout << "  " << entry.first << ": " << entry.second->value << endl;
        }
        cout << "[END] Map: " << endl << endl;
    }
};

int main () {
    // LRUList list;
    // Node *node = nullptr;
    // Node *node1 = new Node(1,2); list.push_back(node1); list.print();
    // Node *node2 = new Node(2,3); list.push_back(node2); list.print();
    // Node *node3 = new Node(3,4); list.push_back(node3); list.print();
    // Node *node4 = new Node(4,5); list.push_back(node4); list.print();

    // list.remove(node2); list.print();
    // list.remove(node3); list.print();
    // list.remove(node1); list.print();
    // list.remove(node4); list.print();

    // list.pop_front(); list.print();

    LRUCache cache(0);
    cache.print();
    cache.put(2,1); cache.print();
    cache.get(2); cache.print();
    cache.put(3,2); cache.print();
    cache.get(2); cache.print();
    cache.get(3); cache.print();
    return 0;
}

// class lru {
//     private:
//         unordered_map<string,string> map;
//         list<string> list;

//     public:
//         void insert(string key, string value) {
//             list.push_front(key);
//             map[key] = value;
//         }

//         string get(string key) {
//             auto it = find(list.begin(), list.end(), key);
//             if(it != list.end()) {
//                 list.erase(it);
//                 list.push_front(key);
//                 return map[key];
//             } else {
//                 return "";
//             }
//         }

//         void print() {
//             for(auto &elem : list) {
//                 cout << elem << ", ";
//             }
//             cout << endl;
//         }
// };

// int main () {
//     lru l;
//     l.insert("1", "1");
//     l.insert("2", "2");
//     l.insert("3", "3");
//     l.print();
//     l.get("2");
//     l.print();
//     return 0;
// }
