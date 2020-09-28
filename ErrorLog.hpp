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

#endif