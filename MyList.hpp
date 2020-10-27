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
protected:
    int size;
    ListNode<T>* head;
    ListNode<T>* tail;

    void init(void);
    std::vector<T> stringify(const std::string& input);

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
            if (this->field == nullptr || this->field->pre == nullptr) { throw IteratorOutOfIndexException(); }
        }

        void assertBoundary(void) const {
            if (this->field == nullptr || this->field->pre == nullptr) { throw IteratorOutOfIndexException(); }
        }

    protected:
        ListNode<T>* field;
        friend class List<T>;
        const List<T>* cur;

    protected:
        const_iterator() : field(nullptr) {}
        const_iterator(ListNode<T>* node) : field(node) {}
        const_iterator(const List<T>* theList, ListNode<T>* node) : cur(theList), field(node) {}

    public:
        const T& operator * (void) const;
        const_iterator& operator ++ (void);
        const_iterator operator ++ (int);
        const_iterator& operator -- (void);
        const_iterator operator -- (int);
        bool operator == (const const_iterator& it) const;
        bool operator != (const const_iterator& it) const;

        void operator += (const int& distance) = delete;
        void operator -= (const int& distance) = delete;
    };
    
    class iterator : public const_iterator {
    public:
        T& operator * (void);
        const T& operator * (void) const;
        iterator& operator ++ (void);
        iterator operator ++ (int);
        iterator& operator -- (void);
        iterator operator -- (int);
        void operator += (const int& distance);
        void operator -= (const int& distance);

        void advance (int distance);

        iterator() : const_iterator() {}
        iterator(ListNode<T>* node) : const_iterator(node) {}
        iterator(const List<T>* cur, ListNode<T>* node) : const_iterator(cur, node) {}
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
    List(ListNode<T>* head);
    List(const std::string& input);
    List(const List& list);

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
    void split(List<T>& a, List<T>& b);
    void merge(List<T>& list);
    void clear(void);
    void unique(void);
    void makeCircle(void);
    
    
    iterator find(const iterator& begin , const iterator& end, const T& value);

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

    T& operator [](int index);
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
class CycleList : public List<T> {
private:
    void makeCycle(void);
public:
    CycleList() = delete;
    CycleList(T* arr, int size) : List<T>(arr, size) { this->makeCycle(); }
    CycleList(std::vector<T> arr) : List<T>(arr) { this->makeCycle(); }
    CycleList(std::string arr) = delete;
    CycleList(const CycleList& list) : List<T>(list) { this->makeCycle(); }
    CycleList(ListNode<T>* head) : List<T>(head) { this->makeCycle(); }
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
}

template<typename T>
List<T>::List(T* arr, int size) {
    this->init();

    for (int i = 0; i < size; i++) {
        this->push_back(arr[i]);
    }
}

template<typename T>
List<T>::List(const std::string& input) {
    this->init();
    *this = List<T>(this->stringify(input));
}

template<typename T>
List<T>::List(const List& list) {
    this->init();

    for (auto it = list.begin(); it != list.end(); it++) {
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
void List<T>::makeCircle(void) {
    if (this->size != 0) {
        this->tail->next = this->head;
    }
}

template<typename T>
void List<T>::print(void) {
    for (auto it = this->begin(); it != this->end(); ++it) { std::cout << *it << " "; }

    std::cout << std::endl;
}

//OK.

template<typename T>
void List<T>::split(List<T>& a, List<T>& b) {
    a.size = (this->size + 1 )>> 1;
    b.size = this->size >> 1;
    if (this->size == 0) { return; }

    //odd traverses all the odd positions, evenHead is the head of the even one.
    ListNode<T>* odd = this->head->next, *even = this->head->next->next, *evenHead = even;

    while (even != head && even->next != head) {
        odd->next = even->next;
        even->next->pre = odd;
        odd = odd->next;
        even->next = odd->next;
        odd->next->pre = even;
        even = even->next;
    }

    a.head = this->head;
    a.tail = odd == this->tail ? odd : odd->next;
    b.head = new ListNode<T>(INT_MIN, evenHead);
    b.tail = new ListNode<T>(INT_MAX, even, nullptr);
    even->pre->next = b.tail;
    this->size = 0;

    //debug
    /*
     * Even is now the head.
     */
}

template<typename T>
void List<T>::erase(const iterator& it) {
    try {
        if (it != this->end()) { it.assertBoundary(); }
        if (it.cur != this) { throw IteratorMisMatchException(); }

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
    } catch (IteratorMisMatchException e) {
        std::cout << e.what() << std::endl;
    }
}

template<typename T>
typename List<T>::iterator List<T>::begin(void) {
    return iterator(this, this->head->next);
}

template<typename T>
typename List<T>::const_iterator List<T>::begin(void) const {
    return const_iterator(this, this->head->next);
}

template<typename T>
typename List<T>::iterator List<T>::end(void) {
    return iterator(this, this->tail);
}

template<typename T>
typename List<T>::const_iterator List<T>::end(void) const {
    return const_iterator(this, this->tail);
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
        ptr->next = new ListNode<T>(value, ptr->next);
        this->size += 1;
    }
}

template<typename T>
void List<T>::insertHandler(const iterator& it, const T& val) {
    try {
        if (this != it.cur) { throw IteratorMisMatchException (); }
        if (it != this->end()) { it.assertBoundary(); }

        ListNode<T>* tmp = new ListNode<T>(val);
        tmp->pre = it.field->pre;
        tmp->next = it.field;
        it.field->pre->next = tmp;
        it.field->pre = tmp;

        this->size += 1;
    } catch (IteratorMisMatchException e) {
        std::cout << e.what() << std::endl;
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    
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
typename List<T>::iterator List<T>::find(const iterator& begin, const iterator& end, const T& value) {
    for (List<T>::iterator it = begin; it != end; it ++) {
        if (it.field->val == value) { return it; }
    }
    return this->end();
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
std::vector<T> List<T>::stringify(const std::string& input) {
    std::string s = input.substr(1, input.size() - 2);
    std::istringstream iss(s);
    std::string buf;
    std::vector<T> ans;

    while (getline(iss, buf, ',')) {
        ans.push_back(stoi(buf));
    }

    return ans;
}

template<typename T>
ListNode<T>* doSort(ListNode<T>* head) {
    /*
     * No need for judge the tail or head as they are definitely the biggest and smallest one in a list.
     * :)
     */ 
    if (head == nullptr || head->next == nullptr) { return head; } 

    //Subdevide the list by applying two pointers with different speed.
    ListNode<T>* slow = head, *fast = head->next->next;
    ListNode<T>* left, *right;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    right = doSort(slow->next);
    slow->next = nullptr;
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
        this->field = this->field->next;
        this->assertBoundary();
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return *this;
}

template<typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator -- (void) {
    try {
        this->assertBoundary();
        this->field = this->field->pre;
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return *this;
}

template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator ++ (int) {
    const_iterator old(this->cur, this->field);
    try {
        this->assertBoundary();
        ++(*this);
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return old;
}

template<typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator -- (int) {
    const_iterator old(this->cur, this->field);
    try {
        --(*this);
        this->assertBoundary();
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return old;
}

template<typename T>
bool List<T>::const_iterator::operator == (const const_iterator& it) const {
    return (this->field == it.field) &&
           (this->cur == it.cur);
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
        return this->cur->begin().field->val;
    }
}

template<typename T>
const T& List<T>::iterator::operator * (void) const {
    try {
        this->assertBoundary();
        return const_iterator::operator*();
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
        return this->cur->begin().field->val;
    }
}

template<typename T>
void List<T>::iterator::advance(int distance) {
    if (distance ==  0) { return; }
    else if (distance > 0) {
        while (distance-- > 0) {
            try {
                this->assertBoundary();
                ++(*this);
            } catch (IteratorOutOfIndexException e) {
                std::cout << e.what() << std::endl;
            }
        }
    } else {
        while (distance++ < 0) {
            try {
                this->assertBoundary();
                --(*this);
            } catch (IteratorOutOfIndexException e) {
                std::cout << e.what() << std::endl;
            }
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
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator ++ (int) {
    iterator old(this->cur, this->field);
    try {
        this->assertBoundary();
        ++(*this);
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return old;
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator -- (void) {
    try {
        this->assertBoundary();
        this->field = this->field->pre;
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator -- (int) {
    iterator old(this->cur, this->field);
    try {
        this->assertBoundary();
        --(*this);
    } catch (IteratorOutOfIndexException e) {
        std::cout << e.what() << std::endl;
    }
    return old;
}

template<typename T>
void List<T>::iterator::operator += (const int& distance) {
    this->advance(distance);
}

template<typename T>
void List<T>::iterator::operator -= (const int& distance) {
    this->advance(distance);
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
T& List<T>::operator [](int index) {
    try {
        if (this->size <= index) { throw ListOutOfIndexException(); }

        int i = -1;
        ListNode<T>* ptr = this->head;
        while (i ++ != index) { ptr = ptr->next; }
        return ptr->val;
    } catch (ListOutOfIndexException e) { std::cout << e.what() << std::endl; }
}

template<typename T>
List<T>::~List() {
    /*
    if (this->size == 0) { return; }
    ListNode<T>* ptr = this->head;

    while (ptr != this->tail) {
        auto tmp = ptr;
        ptr = ptr->next;
        delete tmp;
    }
    if (this->tail != nullptr) { delete this->tail; } */
}


#endif
