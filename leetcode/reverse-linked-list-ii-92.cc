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
private:
    void getStartEnd(ListNode *head, int m, int n, 
        ListNode **start, ListNode **end, 
        ListNode **startPrev, ListNode **endNext) {
        ListNode *s = nullptr;
        ListNode *e = head;
        ListNode *sP = nullptr;
        int count = 0;
        while(e) {
            count++;
            if(count == n) break;
            if(count == m - 1) sP = e;
            if(count == m) s = e;
            e = e->next;
        }
        *start = s;
        *end = e;
        *startPrev = sP;
        if(e) *endNext = e->next;
    }
    
    ListNode* reverse(ListNode* head) {
        ListNode *curr = head;
        ListNode *next = head->next;
        while(next) {
            ListNode *temp = next->next;
            next->next = curr;
            curr = next;
            next = temp;
        }
        head->next = nullptr;
        head = curr;
        return head;
    }

public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(n <= m) return head;
        if(!head) return nullptr;
        ListNode *start = nullptr, *end = nullptr, 
            *startPrev = nullptr, *endNext = nullptr;
        getStartEnd(head, m, n, &start, &end, &startPrev, &endNext);
        if(!end) return head;

        ListNode *revTail = start;
        end->next = nullptr;
        ListNode *rev = reverse(start);
        revTail->next = endNext;
        if(startPrev) {
            startPrev->next = rev;
        } else {
            head = rev;
        }
        return head;
    }
};


int main() {
    vector<int> array = {1};
    Solution s;
    ListNode *head = new ListNode(array[0]);
    ListNode *curr = head;
    for(int i = 1; i < array.size(); i++) {
        curr->next = new ListNode(array[i]);
        curr = curr->next;
    }
    print(head);

    ListNode *rev = s.reverseBetween(head, 1,1);
    print(rev);

    return 0;
}