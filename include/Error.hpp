#ifndef ERROR_H
#define ERROR_H
#include<string>

enum Errors {
    ERR_OK,
    ERR_LEX,
    ERR_IO,
    ERR_LEX,
    ERR_PARSE,
    ERR_CODEGEN,
    ERR_EXEC,
    ERR_FAIL
};

namespace error{
    std::string &str();
    ssize_t &code;
    ssize_t &value;
    void set_err_value(ssize_t &code, ssize_t &value, std::string str);
}
#endif