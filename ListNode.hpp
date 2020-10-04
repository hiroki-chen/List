#ifndef _LISTNODE_HPP_
#define _LISTNODE_HPP_

template<typename T>
struct ListNode {
    ListNode* next;
    ListNode* pre;
    T val;

    ListNode() : next(nullptr) {}
    ListNode(int _val) : val(_val), pre(nullptr), next(nullptr) {}
    ListNode(int _val, ListNode* _next) : val(_val), next(_next) {}
    ListNode(int _val, ListNode* _pre, ListNode* _next) : val(_val), pre(_pre), next(_next) {}
    ListNode(const ListNode<T>* rhs) : val(rhs->val), pre(rhs->pre), next(rhs->next) {}
};

#endif