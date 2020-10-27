#ifndef _MYSTACK_HPP_
#define _MYSTACK_HPP_

#include "/Users/chenhaobin/Documents/NKU/DataStructure/List/MyList.hpp"

template <typename T>
class Stack {
    List<T> content;

public:
    //Constructors.
    Stack() : content(List<T>()) {}
    Stack(const std::vector<T> arr) : content(List<T>(arr)) {}
    Stack(const T* arr) : content(List<T>(arr)) {}
    Stack(const int& size, const T& data) : content(List<T>(std::vector<T>(size, data))) {}

    //Basic handlers.
    typename List<T>::iterator begin(void);
    typename List<T>::iterator end(void);
    typename List<T>::iterator begin(void) const;
    typename List<T>::iterator end(void) const;
    
    Stack<T> push(const T& val);
    T pop(void);
    T top(void);
    int size(void);

    bool empty(void);
};

template<typename T>
typename List<T>::iterator Stack<T>::begin(void) {
    return this->content.begin();
}

template<typename T>
typename List<T>::iterator Stack<T>::end(void) {
    return this->content.end();
}

template<typename T>
typename List<T>::iterator Stack<T>::begin(void) const {
    return this->content.begin();
}

template<typename T>
typename List<T>::iterator Stack<T>::end(void) const {
    return this->content.end();
}

template<typename T>
Stack<T> Stack<T>::push(const T& val) {
    this->content.push_front(val);
    return *this;
}

template<typename T>
T Stack<T>::pop(void) {
    T ans = this->content.front();
    this->content.pop_front();
    return ans;
}

template<typename T>
T Stack<T>::top(void) {
    return this->content.front();
}

template<typename T>
int Stack<T>::size(void) {
    return this->content.listSize();
}

template<typename T>
bool Stack<T>::empty(void) {
    return this->content.empty();
}

#endif