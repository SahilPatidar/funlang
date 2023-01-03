#pragma once
#include<memory>
#include<map>
#include"../lex/lex.hpp"

namespace ast{


const enum KindType {
    INTEGER,
    DECIMAL,
    STRING,
    BOOLEAN,
    POINTER,
    STRUCT,
    ARRAY,
    CONST,
    FUNCTION,
};


class Type{
public:
 virtual ~Type() = default;
 virtual bool OperatorMatch(Token_type op, const TypePtr type) const;
 virtual KindType type() const = 0;
};

using TypePtr = std::shared_ptr<Type>;

class Int: public Type{
private:
    int size;
public:
    Int(int size)
    :size(size) {}
    int size() const {return size;}
    bool OperatorMatch(Token_type op, const TypePtr type);
    KindType type() const { return INTEGER; }


};

class String: public Type{
public:
    String();
};

class Float: public Type {
private:
    int size;
public:
    Float(int size)
    :size(size) {}
    int size() const {return size;}
    bool OperatorMatch(Token_type op, const TypePtr type);
    KindType type() const { return DECIMAL; }

};

class Bool: public Type {
private:

public:
    KindType type() const { return BOOLEAN; }

};

class ConstType: public Type {
private:
    TypePtr type;

public:
    ConstType(TypePtr&_type)
    :type(_type) {}

    TypePtr consType() const {return type;}
    bool OperatorMatch(Token_type op, const TypePtr type);
    KindType type() const { return CONST; }


};

class FuncType: public Type {
private:
    std::vector<TypePtr>param;
    TypePtr retype;
public:
    FuncType(std::vector<TypePtr>&_param, TypePtr &_ret)
    :param(_param), retype(_ret) {}

    std::vector<TypePtr>paramType() const { return param; }
    TypePtr retType() const { return retype; }
    bool OperatorMatch(Token_type op, const TypePtr type);
    KindType type() const { return FUNCTION; }

};

class StructType: public Type{
private:
    std::map<std::string,TypePtr>mem;
public:
    StructType(std::map<std::string,TypePtr> &_mem) 
    :mem(_mem) {}

    std::map<std::string,TypePtr>member() const {return mem;}
    bool OperatorMatch(Token_type op, const TypePtr type);
    KindType type() const { return STRUCT; }


};

class ArrayType: public Type{
private:

public:

    bool OperatorMatch(Token_type op, const TypePtr type);
    KindType type() const { return ARRAY; }

};

class PointerType: public Type{
private:
    int ptr_size;
    TypePtr base;
public:
    PointerType(int &_ptr_size, TypePtr &_base)
    :ptr_size(_ptr_size), base(_base) {}

    int ptrSize() const {return ptr_size;}
    TypePtr baseType() const {return base;}
    KindType type() const { return POINTER; }
    // KindType base_type() const { return base->type(); }
    bool OperatorMatch(Token_type op, const TypePtr type);


};


class TypeGenerator{
    public:
    static TypePtr Integer();
    static TypePtr Boolean();
    static TypePtr Decimal();
    static TypePtr String();
    static TypePtr FuncTypeGenerate(std::vector<TypePtr>&p_type, TypePtr r_type);
    static TypePtr Generate(KindType type);
};

}