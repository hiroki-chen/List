#ifndef _ERRORLOG_HPP_
#define _ERRORLOG_HPP_

#include <iostream>
#include <exception>

class ListOutOfIndexException : public std::exception {
    const char* info;
public:
    ListOutOfIndexException() : info("You cannot access a list in such way; out of bound!!") {}
    const char* what() const noexcept override { return info; }
};

class IteratorOutOfIndexException : public std::exception {
    const char* info;

public:
    IteratorOutOfIndexException() : info("Iterator is out ouf bound!!") {}
    const char* what() const noexcept override { return info; }
};

class IteratorMisMatchException : public std::exception {
    const char* info;

public:
    IteratorMisMatchException() : info("Iterator does not point to the current list you want to manipulate!") {}
    const char* what() const noexcept override { return info; }
};

class ConstIteratorCannotBeOperatedException : public std::exception {
    const char* info;

public:
    ConstIteratorCannotBeOperatedException() : info("You cannot modify a const iterator.") {}
    const char* what() const noexcept override { return info; }
};

#endif