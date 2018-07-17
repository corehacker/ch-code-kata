#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *add(ListNode *head, int val) {
      if(!head) {
        head = new ListNode(val);
        return head;
      } else {
        ListNode *curr = head;
        ListNode *prev = nullptr;
        while(curr) {
          prev = curr;
          curr = curr->next;
        }
        prev->next = new ListNode(val);
        return head;
      }
    }

    void print(ListNode *head) {
      while(head) {
        cout << head->val << ", ";
        head = head->next;
      }
      cout << endl;
    }

    ListNode* deleteDuplicates(ListNode* head) {
        if(!head) return head;
        ListNode *curr = head;
        ListNode *next = head->next;
        
        ListNode *newHead = nullptr;
        ListNode *newCurr = nullptr;
        
        bool duplicate = false;
        while(curr && next) {
            cout << "curr: " << curr->val << ", next: " << next->val << endl;
            if(curr->val == next->val) {
                cout << "Duplicate" << endl;
                duplicate = true;
            } else {
                if(!duplicate) {
                    if(!newHead) {
                        newHead = curr;
                        newCurr = newHead;
                    } else {
                        newCurr->next = curr;
                        newCurr = curr;
                    }
                }

                duplicate = false;
            }

            next = next->next;
            curr = curr->next;
        }
        if(!duplicate) {
            if(!newHead) {
                newHead = curr;
                newCurr = newHead;
            } else {
                newCurr->next = curr;
                newCurr = curr;
            }
        } else {
          if(newHead)
            newCurr->next = nullptr;
        }
        return newHead;
    }
};


int main() {
  Solution s;
  ListNode *head = nullptr;
  head = s.add(head, 1);
  // head = s.add(head, 1);
  // head = s.add(head, 1);
  // head = s.add(head, 2);
  // head = s.add(head, 3);
  // head = s.add(head, 4);
  // head = s.add(head, 4);

  s.print(head);
  ListNode *n = s.deleteDuplicates(head);
  s.print(n);

  return 0;
}