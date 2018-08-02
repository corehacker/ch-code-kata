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
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct LessThan
{
  bool operator()(ListNode * left, ListNode * right)
  {
    return left->val < right->val;
  }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode * left, ListNode * right) { return left->val < right->val;};
        priority_queue<ListNode *, vector<ListNode *>, LessThan> pq;

        ListNode *dummy = new ListNode(0);
        for(auto list: lists) {
          pq.push(list);
        }

        ListNode *curr = dummy;
        while(!pq.empty()) {
          curr->next = pq.top();
          pq.pop();
          curr = curr->next;
          if(curr->next) {
            pq.push(curr->next);
          }
        }
        return dummy->next;
    }
};