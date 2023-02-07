#pragma once
#include<map>
#include<optional>
#include"../parser/type.hpp"

using namespace ast;


template<typename T>
class SymTable{
    private:
    std::map<std::string,T>extrnt;
    std::map<std::string,T>sym;
    std::shared_ptr<SymTable<T> >p_table;
    bool islocal = false;
    public:
    SymTable(std::shared_ptr<SymTable>table){

    }
    bool insert(std::string val, T type) {

        return true;
    }
    void setFlag(bool flag);

    bool contains(std::string key, bool inloc) {

        return false;
    }
    bool contains(std::string key) {

        return false;
    }

    T get(std::string key) {

    }

    bool pop() {
        local.clear();
    }
};







