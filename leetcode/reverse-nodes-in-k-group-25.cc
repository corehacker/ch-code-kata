/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int shouldReverse(struct ListNode *node, int count, int k) {
    // printf("shouldReverse | node: %p, count: %d, k: %d\n", node, count, k);
    if(NULL == node) return 0;
    if(count == (k - 1)) return 1;
    return shouldReverse(node->next, ++count, k);
}

struct ListNode *reverseGroup1(struct ListNode *head, int k, struct ListNode **groupHead) {
    struct ListNode *curr = head;
    struct ListNode *nextNext = head->next;
    struct ListNode *next = NULL;
    while((k - 1) > 0) {
        next = nextNext;
        nextNext = nextNext->next;
        curr->next->next = curr;
        curr = next;
        k = k - 1;
    }
    printf("--reverseGroup | k: %d, curr: %d, curr: %p\n", k, curr->val, curr);
    *groupHead = curr;
    head->next = nextNext;
    printf("reverseGroup | head: %d, head->next: %p\n", head->val, head->next);
    printf("reverseGroup | group head: %d, group head->next: %p\n", (*groupHead)->val, (*groupHead)->next);
    return head;
}

struct ListNode *reverseGroup(struct ListNode *head, int k, struct ListNode **groupHead) {
    struct ListNode* prev   = NULL;
    struct ListNode* curr = head;
    struct ListNode* next;
    while (k > 0) {
        next  = curr->next;  
        curr->next = prev;   
        prev = curr;
        curr = next;
        k = k - 1;
    }
    *groupHead = prev;
    head->next = next;
    // printf("reverseGroup | head: %d, head->next: %p\n", head->val, head->next);
    // printf("reverseGroup | group head: %d, group head->next: %p\n", (*groupHead)->val, (*groupHead)->next);
    return head;
}

void print(struct ListNode *head) {
    while(head != NULL) {
        printf("%p (%d, %p) -> ", head, head->val, head->next);
        head = head->next;
    }
    printf("\n");
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if(NULL == head) return NULL;
    if(k <= 1) return head;
    
    // print(head);
    // printf("\n");
    
    struct ListNode *reverse = NULL;
    struct ListNode *next = head;
    struct ListNode *groupHead = NULL;
    struct ListNode *prevTail = NULL;
    while(shouldReverse(next, 0, k)) {
        // printf("reverseKGroup | ++Should reverse: %d, %p\n", next->val, next);
        next = reverseGroup(next, k, &groupHead);
        if(!reverse) {
            reverse = groupHead;
        }
        // print(reverse);
        if(prevTail)
            prevTail->next = groupHead;
        prevTail = next;
        next = next->next;
        if(!next) {
            break;
        }
        // printf("reverseKGroup | --Should reverse: %d, %p\n\n", next->val, next);
    }
    if(!reverse) {
        reverse = head;
    }
    return reverse;
}
