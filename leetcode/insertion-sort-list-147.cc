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
    ListNode *insert(ListNode *head, ListNode *node) {
        if(!node) return head;
        ListNode *temp = new ListNode(node->val);
        if(!head) return temp;
        
        if(temp->val < head->val) {
            temp->next = head;
            return temp;
        }
        
        ListNode *curr = head, *prev = nullptr;
        while(curr) {
            if(temp->val < curr->val) break;
            prev = curr;
            curr = curr->next;
        }

        temp->next = prev->next;
        prev->next = temp;
        
        return head;
    }
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode *sorted = nullptr;
        ListNode *curr = head;
        
        while(curr) {
            sorted = insert(sorted, curr);
            curr = curr->next;
        }
        return sorted;
    }
};


int main() {
    // vector<int> array = {1,2,3,4};
    vector<int> array = {-1};
    Solution s;
    ListNode *head = new ListNode(array[0]);
    ListNode *curr = head;
    for(int i = 1; i < array.size(); i++) {
        curr->next = new ListNode(array[i]);
        curr = curr->next;
    }
    print(head);

    ListNode *rev = s.insertionSortList(head);
    print(rev);

    return 0;
}