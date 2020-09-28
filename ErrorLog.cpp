#include "ErrorLog.hpp"

void ErrorLog::operator << (std::string& errorInfo) {
    std::string type = errorInfo.substr(0, 7);

    if (type.compare(error_1)) { this->type = OUT_OF_INDEX; }
    if (type.compare(error_2)) { this->type = VALUE_NOT_EXIST; }
    if (type.compare(error_3)) { this->type = ACCESS_NULLPTR; }
    if (type.compare(error_4)) { this->type = UNEXPECTED_ERROR; }
}

std::ostream& operator << (std::ostream& os, ErrorLog& e) {
    return os << e.errorInfo;
}