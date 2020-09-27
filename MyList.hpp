#ifndef _MYLIST_HPP_
#define _MYLIST_HPP_

#define UNIMPLEMENTED return;

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <limits>

#include "ListNode.hpp"

template<typename T>
class List {
    int size;
    ListNode<T>* head;

public:
    /*
     * Iterator for class List.
     */
    class iterator {
        ListNode<T>* field;

        public:
        //There would be a constructor that does nothing.
            iterator();
            iterator(const iterator& i);
            
            bool operator ==(const iterator& rhs);
            bool operator !=(const iterator& rhs);
            void operator ++();
            void operator --();
            T& operator *();

            iterator begin(void);
            iterator end(void);
    };

    /*
     * Constant iterator is disabled.
     */ 

    /*
     * Different constructor functions for users.
     */

    List() = delete;
    List(T* arr, int size);
    List(std::vector<T> arr);
    List(std::string arr);
    List(List& list);
    List(ListNode<T>* head);

    /*
     * Some basic functions.
     */

    void insertHandler(T value, int position);
    void deleteHandler(T value);
    void updateHandler(T value, T newValue);
    void searchHandler(T value);

    /*
     * Some implementations used to alter the list itself.
     */ 

    void print(void);
    void reverse(void);
    void sort(bool bigger = false);
    void merge(List<T>& list);
    void clear(void);

    friend ListNode<T>* doMerge(ListNode<T>* left, ListNode<T>* right);
    friend ListNode<T>* doSort(ListNode<T>* head);
    friend ListNode<T>* doReverse(ListNode<T>* head);

    T front(void);
    void push_back(T value);
    void pop_back(void);
    void push_front(T value);
    void pop_front(void);
    int listSize(void);
    bool empty(void);

    /*
     * For test.
     */

    void Test(void) {
        std::cout << this->head->val << std::endl;
    }

    ~List();
};

template<typename T>
List<T>::List(std::vector<T> arr) {
    this->head = new ListNode<T>(INT_MIN);
    this->size = 0;
    ListNode<T>* ptr = head;

    for (auto item : arr) {
        ptr->next = new ListNode<T>(item);
        ptr = ptr->next;
        size ++;
    }
}


template<typename T>
void List<T>::print(void) {
    if (this->size == 0) {
        std::cout << "Empty List!" << std::endl;
        return;
    }

    ListNode<T>* ptr = this->head->next;

    while (ptr != nullptr) {
        std::cout << ptr->val << " ";
        ptr = ptr->next;
    }

    std::cout << std::endl;
}


template<typename T>
List<T>::List(T* arr, int size) {
    this->head = new ListNode<T>(INT_MIN);
    this->size = size;
    ListNode<T>* ptr = head;

    for (int i = 0; i < size; i++) {
        ptr->next = new ListNode<T>(*(arr + i));
        ptr = ptr->next;
    }
}


template<typename T>
List<T>::List(List& list) {
    this->head = new ListNode<T>(INT_MIN);
    this->size = 0;
    ListNode<T>* ptr1 = head;
    ListNode<T>* ptr2 = list.head->next;

    while (ptr2 != nullptr) {
        ptr1->next = new ListNode<T>(ptr2->val);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        this->size += 1;
    }
}

template<typename T>
List<T>::List(ListNode<T>* head) {
    this->head = head;
}

template<typename T>
void List<T>::insertHandler(T value, int position) {
    if (position >= size) {
        std::cout << "Sorry, you have inputed wrong posistion! ERROR_1: Index out of bound." << std::endl;
        return;
    } else {
        int i = -1;
        ListNode<T>* ptr = this->head;

        while (i++ != position) {
            ptr = ptr->next;
            this->size += 1;
        }
        ptr->val = value;
    }
}

template<typename T>
void List<T>::deleteHandler(T value) {
    ListNode<T>* ptr = this->head;

    while (ptr->next != nullptr) {
        if (ptr->next->val == value) {
            ListNode<T>* tmp = ptr->next;
            ptr->next = tmp->next;
            delete tmp;
            this->size -= 1;
            return;
        }
        ptr = ptr->next;
    }

    if (ptr->val != value) {
        std::cout << "Could not find any corresponding value to delete. Please Try again" << std::endl;
        return;
    } else { delete ptr; }
}

template<typename T>
void List<T>::searchHandler(T value) {
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
void List<T>::updateHandler(T value, T newValue) {
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
void List<T>::sort(bool isBigger) {
    this->head->next = doSort(this->head->next);
    this->head->next = isBigger == false ? head->next : doReverse(head->next);
}

template<typename T>
void List<T>::reverse(void) {
    this->head->next = doReverse(this->head->next);
}

template<typename T>
void List<T>::merge(List<T>& list) {
    ListNode<T>* ptr = this->head;
    while (ptr->next != nullptr) { ptr = ptr->next; }
    ptr->next = list.head->next;
    this->size += list.size;
    this->head->next = doSort(this->head->next);
}

template<typename T>
ListNode<T>* doSort(ListNode<T>* head) {
    if (head == nullptr || head->next == nullptr) { return head; }

    //Subdevide the list by applying two pointers with different speed.
    ListNode<T>* slow = head, *fast = head -> next -> next;
    ListNode<T>* left, *right;
    while (fast != nullptr && fast -> next != nullptr) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    right = doSort(slow -> next);
    slow -> next = NULL;
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
    return this->size == 0 ? this->head->val : this->head->next->val;
}

template<typename T>
void List<T>::push_back(T value) {
    ListNode<T>* ptr = this->head;
    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }
    this->size += 1;
    ptr->next = new ListNode<T>(value);
}

template<typename T>
void List<T>::pop_back(void) {
    ListNode<T>* ptr = this->head;
    if (this->size == 0) {
        std::cout << "Cannot do pop_back() if a list is empty!" << std:: endl;
        return;
    }
    
    while (ptr->next->next != nullptr) { ptr = ptr->next; }
    ptr->next = nullptr;

    this->size -= 1;
}

template<typename T>
void List<T>::push_front(T value) {
    if (this->size ++ == 0) {
        this->head->next = new ListNode<T>(value);
        return;
    }

    ListNode<T>* tmp = this->head->next->next;
    this->head->next = new ListNode<T>(value);
    this->head->next->next = tmp;
}

template<typename T>
void List<T>::pop_front(void) {
    if (this->size == 0) {
        std::cout << "Cannot do pop_front() if a list is empty!" << std::endl;
        return;
    }
    ListNode<T>* tmp = this->head->next;
    this->head->next = tmp->next;
    delete tmp;
    this->size -= 1;
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
List<T>::~List() {
    ListNode<T>* tmp;
    while (head->next != nullptr) {
        tmp = head->next;
        delete head;
        head = tmp;
    }
    delete head;
}

//For iterators.

template<typename T>
bool List<T>::iterator::operator == (const iterator& rhs) {
    return this->field->val == rhs->field->val;
}

template<typename T>
bool List<T>::iterator::operator != (const iterator& rhs) {
    return this->field->val != rhs->field->val;
}

template<typename T>
T& List<T>::iterator::operator * (void) {
    return this->field->val;
}

template<typename T>
void List<T>::iterator::operator ++ (void) {
    if (this->field->next != nullptr) {
        this->field = this->field->next;
    }
}

template<typename T>
void List<T>::iterator::operator -- (void) {
    UNIMPLEMENTED
}

#endif