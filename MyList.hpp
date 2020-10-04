#ifndef _MYLIST_HPP_
#define _MYLIST_HPP_

#define UNIMPLEMENTED return;

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <limits>
#include <unordered_map>

#include "ListNode.hpp"
#include "ErrorLog.hpp"

template<typename T>
class List {
    int size;
    ListNode<T>* head;
    ListNode<T>* tail;

    void init(void);

public:
    class const_iterator {
    private:
    /**
     * Because constant property of iterator may be, there should exist two overloading versions for each kind of iterator.
     * Or the system will throw error.
     */
        //bool notEnd;
        // I personally suppose that it may unnecessarily to mark an iterator as end_iterator.
        void assertBoundary(void) {
            if (this->field->next == nullptr) { throw IteratorOutOfIndexException(); }
        }

        void assertBoundary(void) const {
            if (this->field->next == nullptr) { throw IteratorOutOfIndexException(); }
        }

    protected:
        ListNode<T>* field;
        friend class List<T>;

    protected:
        const_iterator() : field(nullptr) {}
        const_iterator(ListNode<T>* node) : field(node) {}

    public:
        const T& operator * (void) const;
        const_iterator& operator ++ (void);
        const_iterator operator ++ (int);
        bool operator == (const const_iterator& it) const;
        bool operator != (const const_iterator& it) const;
    };
    
    class iterator : public const_iterator {
    public:
        T& operator * (void);
        const T& operator * (void) const;
        iterator& operator ++ (void);

        void advance (int distance);

        iterator() : const_iterator() {}
        iterator(ListNode<T>* node) : const_iterator(node) {}
    };
    /*
     * Iterator for class List.
     */

    /*
     * Constant iterator is disabled.
     */ 

    /*
     * Different constructor functions for users.
     */

public:
    iterator begin(void);
    iterator end(void);
    const_iterator begin(void) const;
    const_iterator end(void) const;

    List();
    List(T* arr, int size);
    List(std::vector<T> arr);
    List(std::string arr);
    List(const List& list);
    List(ListNode<T>* head);

    /*
     * Some basic functions.
     */

    void insertHandler(const int& postion, const T& val);
    void insertHandler(const iterator& it, const T& val);
    void deleteHandler(const T& value);
    void deleteHandler(const iterator& left, const iterator& right);
    void updateHandler(const T& value, const T& newValue);
    void updateHandler(const iterator& it, const T& val);
    void searchHandler(const T& value);

    /*
     * Some implementations used to alter the list itself.
     */ 

    void print(void);
    void reverse(void);
    void sort(bool bigger = false);
    void merge(List<T>& list);
    void clear(void);
    void unique(void);

    /**
     * Some manipulation functions with iterator.
     * You can either choose the normal one or manipulate the list by applying the iterator on them. :)
     */

    void erase(const iterator& it);

    friend ListNode<T>* doMerge(ListNode<T>* left, ListNode<T>* right);
    friend ListNode<T>* doSort(ListNode<T>* head);
    friend ListNode<T>* doReverse(ListNode<T>* head);

    T front(void);
    T back(void);
    void push_back(T value);
    void pop_back(void);
    void push_front(T value);
    void pop_front(void);
    int listSize(void);
    bool empty(void);

    bool operator == (List<T> list);
    bool operator != (List<T> list);
    void operator += (T value);
    void operator += (List<T>& list) = delete; // You cannot use this because this is a forward list.

    /*
     * For test.
     */

    void Test(void) {
        std::cout << this->head->val << std::endl;
    }

    ~List();
};

template<typename T>
void List<T>::init(void) {
    this->head = new ListNode<T>(INT_MIN);
    this->tail = new ListNode<T>(INT_MAX);
    this->head->next = this->tail;
    this->tail->pre = this->head;
    this->size = 0;
}

template<typename T>
List<T>::List() {
    this->init();
}

template<typename T>
List<T>::List(std::vector<T> arr) {
    this->init();

    for (auto item : arr) {
        this->push_back(item);
    }
    std::cout << "tail == nullptr" << (tail == nullptr) << std::endl;
}

template<typename T>
List<T>::List(T* arr, int size) {
    this->init();

    for (int i = 0; i < size; i++) {
        this->push_back(arr[i]);
    }
    std::cout << "tail == nullptr" << (tail == nullptr) << std::endl;
}


template<typename T>
List<T>::List(const List& list) {
    this->init();

    for (auto it = list.begin(); it != list.end(); ++it) {
        this->push_back(*it);
    }
    
}

template<typename T>
List<T>::List(ListNode<T>* head) {
    this->init();

    while (head != nullptr) {
        this->push_back(head->val);
        head = head->next;
    }

}

template<typename T>
void List<T>::print(void) {
    if (this->size == 0) {
        std::cout << "Empty List!" << std::endl;
        return;
    }

    for (auto it = this->begin(); it != this->end(); ++it) { std::cout << *it << " "; }

    std::cout << std::endl;
}

template<typename T>
void List<T>::erase(const iterator& it) {
    try {
        it.assertBoundary();
        ListNode<T>* tmp = it.field;
        ListNode<T>* pre = tmp->pre;
        ListNode<T>* next = tmp->next;
        pre->next = next;
        if (tmp == tail) { tail = pre; }
        if (next != nullptr) { next->pre = pre; }

        delete tmp;
        size--;
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
}

template<typename T>
typename List<T>::iterator List<T>::begin(void) {
    return iterator(this->head->next);
}

template<typename T>
typename List<T>::const_iterator List<T>::begin(void) const {
    return const_iterator(this->head->next);
}

template<typename T>
typename List<T>::iterator List<T>::end(void) {
    return iterator(this->tail);
}

template<typename T>
typename List<T>::const_iterator List<T>::end(void) const {
    return const_iterator(this->tail);
}

template<typename T>
void List<T>::insertHandler(const int& position, const T& value) {
    if (position >= size) {
        std::cout << "Sorry, you have inputed wrong posistion! ERROR_1: Index out of bound." << std::endl;
        return;
    } else if (size - 1 == position) {
        this->push_back(value);
        this->size += 1;
        return;
    } else {
        int i = -1;
        ListNode<T>* ptr = this->head;

        while (i++ != position - 1) {
            ptr = ptr->next;
        }
        ListNode<T>* tmp = ptr->next;
        ptr->next = new ListNode<T>(value);
        ptr->next->next = tmp;
        this->size += 1;
    }
}

template<typename T>
void List<T>::insertHandler(const iterator& it, const T& val) {
    ListNode<T>* tmp = new ListNode<T>(val);
    tmp->pre = it.field->pre;
    tmp->next = it.field;
    it.field->pre->next = tmp;
    it.field->pre = tmp;

    this->size += 1;
}

template<typename T>
void List<T>::deleteHandler(const T& value) {
    ListNode<T>* ptr = this->head;

    while (ptr != nullptr) {
        if (ptr->val == value) {
            ListNode<T>* tmp = ptr;
            ptr->pre->next = ptr->next;
            ptr->next->pre = tmp->pre;
            delete tmp;
            tmp = nullptr;
            this->size -= 1;
        }
        ptr = ptr->next;
    }
}

template<typename T>
void List<T>::deleteHandler(const iterator& left, const iterator& right) {
    for (auto it = left; it != right; ++it) {
        this->erase(it);
    }
}

template<typename T>
void List<T>::searchHandler(const T& value) {
    ListNode<T>* ptr = this->head;

    int i = -1;

    while (ptr != nullptr) {
        if (ptr->val == value) {
            std::cout << "Find value at position " << i << std::endl;
            return;
        }
        i++;
        ptr = ptr->next;
    }

    std::cout << "It seems that there is no such thing. Please check your input again." << std::endl;
}

template<typename T>
void List<T>::updateHandler(const T& value, const T& newValue) {
    ListNode<T>* ptr = this->head;

    while (ptr != nullptr) {
        if (ptr->val == value) {
            ptr->val = newValue;
            return;
        }
        ptr = ptr->next;
    }

    std::cout << "It seems that there is no such thing. Please check your input again." << std::endl;
}

template<typename T>
void List<T>::updateHandler(const iterator& it, const T& val) {
    it.field->val = val;
}

template<typename T>
void List<T>::sort(bool isBigger) {
    ListNode<T>* ptr = doSort(this->head->next);
    this->head->next = isBigger == false ? head->next : doReverse(head->next);
    this->init();
    while (ptr->next != nullptr) {
        this->push_back(ptr->val);
        ptr = ptr->next;
    }
}

template<typename T>
void List<T>::reverse(void) {
    ListNode<T>* ptr = doReverse(this->head->next)->next;

    this->init();
    while (ptr != nullptr) {
        this->push_back(ptr->val);
        ptr = ptr->next;
    }
}

template<typename T>
void List<T>::merge(List<T>& list) {
    ListNode<T>* ptr = list.head->next;
    while (ptr != list.tail) {
        this->push_back(ptr->val);
        ptr = ptr->next;
    }

    this->sort();
}

template<typename T>
ListNode<T>* doSort(ListNode<T>* head) {
    if (head == nullptr || head->next == nullptr) { return head; }

    //Subdevide the list by applying two pointers with different speed.
    ListNode<T>* slow = head, *fast = head -> next -> next;
    ListNode<T>* left, *right;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    right = doSort(slow->next);
    slow->next = NULL;
    left = doSort(head);
    return doMerge(left, right);
}

template<typename T>
ListNode<T>* doMerge(ListNode<T>* left, ListNode<T>* right) {
    ListNode<T>* ans = new ListNode<T>(INT_MIN);
    ListNode<T>* ptr = ans;
    while (left != nullptr && right != nullptr) {
        if (left->val <= right->val) {
            ptr->next = left;
            left = left->next;
        } else {
            ptr->next = right;
            right = right->next;
        }
        ptr = ptr->next;
    }
    ptr->next = left != nullptr ? left : right;
    return ans->next;
}

template<typename T>
ListNode<T>* doReverse(ListNode<T>* head) {
    if (head == nullptr || head->next == nullptr) { return head; }
    ListNode<T>* newHead = doReverse(head->next); 
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

template<typename T>
List<T>::List(std::string arr) {
    UNIMPLEMENTED
}

template<typename T>
T List<T>::front(void) {
    return *(this->begin());
}

template<typename T>
T List<T>::back(void) {
    return this->end().field->pre->val;
}

template<typename T>
void List<T>::push_back(T value) {
    this->insertHandler(this->end(), value);
}

template<typename T>
void List<T>::pop_back(void) {
    this->erase(this->end());
}

template<typename T>
void List<T>::push_front(T value) {
    this->insertHandler(this->begin(), value);
}

template<typename T>
void List<T>::pop_front(void) {
    this->erase(this->begin());
}

template<typename T>
int List<T>::listSize(void) {
    return this->size;
}

template<typename T>
bool List<T>::empty(void) {
    return this->size == 0;
}

template<typename T>
void List<T>::clear(void) {
    delete this->head->next;
    this->head->next = nullptr;
    this->size = 0;
}

template<typename T>
const T& List<T>::const_iterator::operator * (void) const {
    return this->field->val;
}

template<typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator ++ (void) {
    try {
        this->assertBoundary();
        this->field = this->field->next;
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return *this;
    //this->assertBoundary();
}

template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator ++ (int) {
    const_iterator old(this->field);
    try {
        ++(*this);
        this->assertBoundary();
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return old;
}

template<typename T>
bool List<T>::const_iterator::operator == (const const_iterator& it) const {
    return this->field == it.field;
}

template<typename T>
bool List<T>::const_iterator::operator != (const const_iterator& it) const {
    return !(*this == it);
}

template<typename T>
T& List<T>::iterator::operator * (void) {
    try {
        this->assertBoundary();
        return this->field->val;
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
        abort();
    }
}

template<typename T>
const T& List<T>::iterator::operator * (void) const {
    try {
        this->assertBoundary();
        return const_iterator::operator*();
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
        abort();
    }
}

template<typename T>
void List<T>::iterator::advance(int distance) {
    while (distance-- > 0) {
        try {
            this->assertBoundary();
            ++(*this);
        } catch (IteratorOutOfIndexException e) {
            std::cout << e.what() << std::endl;
            abort();
        }
    }
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator ++ (void) {
    try {
        this->assertBoundary();
        this->field = this->field->next;
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return *this;
    //this->assertBoundary();
}

template<typename T>
bool List<T>::operator == (List<T> list) {
    if (this->size != list.size) { return false; }

    ListNode<T>* ptr1 = this->head->next;
    ListNode<T>* ptr2 = list.head->next;

    while (ptr1 != nullptr && ptr2 != nullptr) {
        if (ptr1->val != ptr2->val) { return false; }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    return true;
}

template<typename T>
bool List<T>::operator != (List<T> list) {
    return !(this == list);
}

template<typename T>
void List<T>::operator += (T value) {
    this->push_back(value);
}

template<typename T>
List<T>::~List() {
    ListNode<T>* tmp;
    while (head->next != nullptr) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
    delete head;
}

#endif
