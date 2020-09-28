#ifndef _ERRORLOG_HPP_
#define _ERRORLOG_HPP_

#include <iostream>

const std::string error_1 = "Error_1";
const std::string error_2 = "Error_2";
const std::string error_3 = "Error_3";
const std::string error_4 = "Error_4";

enum errorType {
    OUT_OF_INDEX,
    VALUE_NOT_EXIST,
    ACCESS_NULLPTR,
    UNEXPECTED_ERROR
};

class ErrorLog {
errorType type;
std::string errorInfo;

public:
    friend std::ostream& operator << (std::ostream& os, ErrorLog& e);
    void operator << (std::string& errorInfo);
};

#endif