#pragma once
#include<iostream>

template<typename T>
class ast_ptr{
    public:
    ast_ptr()
    : obj(new T()), ref(0) 
    {}
    
    ast_ptr(T&&other)
    : obj(other), ref(0) 
    {}

    T& operator=(T&other) {

    }
    private:
    T *obj;
    int *ref;
};
