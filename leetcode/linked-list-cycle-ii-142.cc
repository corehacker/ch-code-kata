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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


void print(ListNode *head) {
    int count = 0;
    while(head) {
        cout << head->val << ", ";
        head = head->next;
        count++;
        if(count == 10) break;
    }
    cout << endl;
}

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(!head) return nullptr;
        ListNode *fast = head;
        ListNode *slow = head;
        
        while(fast) {
            slow = slow->next;
            if(!fast->next) {
                return nullptr;
            }
            fast = fast->next->next;
            if(slow == fast) {
              slow = head;
              while(fast != slow) {
                fast = fast->next;
                slow = slow->next;
              }
              return slow;
            }
        }
        return nullptr;
    }
};

int main() {
    vector<int> array = {1,2,3,4};
    // vector<int> array = {-1};
    Solution s;
    ListNode *head = new ListNode(array[0]);
    ListNode *curr = head;
    for(int i = 1; i < array.size(); i++) {
        curr->next = new ListNode(array[i]);
        curr = curr->next;
    }
    print(head);
    print(curr);

    curr->next = head;
    print(head);


    ListNode *cycle = s.detectCycle(head);
    cout << "Cycle: " << cycle->val << endl;

    return 0;
}