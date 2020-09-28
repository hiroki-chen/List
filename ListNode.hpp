#ifndef _LISTNODE_HPP_
#define _LISTNODE_HPP_

template<typename T>
struct ListNode {
    ListNode* next;
    T val;

    ListNode() : next(nullptr) {}
    ListNode(int _val) : val(_val), next(nullptr) {}
    ListNode(int _val, ListNode* _next) : val(_val), next(_next) {}

    bool operator == (ListNode<T>* head);
    bool operator != (ListNode<T>* head);
    T& operator * (void);
};

#endif