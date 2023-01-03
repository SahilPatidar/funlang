#pragma once
#include<map>

template<typename T>
class Table{
    private:
    std::map<std::string,T>table;
    public:
    bool insert(std::string val, T type);
    T get(std::string);
};


