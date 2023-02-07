#pragma once
#include<memory>
#include<map>
#include"../lex/lex.hpp"

namespace ast{


const enum KindType {
    TYPE_INT,
    TYPE_DECIMAL,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_POINTER,
    TYPE_STRUCT,
    TYPE_ARRAY,
    TYPE_CONST,
    TYPE_FUNCTION,
};


class Type{
public:
 virtual ~Type() = default;
 virtual bool OperatorMatch(lex::Token_type op, const TypePtr type) const;
 virtual bool UnaryOpMatch(lex::Token_type op);
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
    bool OperatorMatch(lex::Token_type op, const TypePtr type);
    bool UnaryOpMatch(lex::Token_type op);
    KindType type() const { return TYPE_INT; }


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
    bool OperatorMatch(lex::Token_type op, const TypePtr type);
    bool UnaryOpMatch(lex::Token_type op);
    KindType type() const { return TYPE_DECIMAL; }

};

class Bool: public Type {
private:

public:
    KindType type() const { return TYPE_BOOLEAN; }
    bool UnaryOpMatch(lex::Token_type op);

};

// class ConstType: public Type {
// private:
//     TypePtr type;

// public:
//     ConstType(TypePtr&_type)
//     :type(_type) {}

//     TypePtr consType() const {return type;}
//     bool OperatorMatch(lex::Token_type op, const TypePtr type);
//     bool UnaryOpMatch(lex::Token_type op);
//     KindType type() const { return TYPE_CONST; }


// };

class FuncType: public Type {
private:
    std::vector<TypePtr>param;
    TypePtr retype;
public:
    FuncType(std::vector<TypePtr>&_param, TypePtr &_ret)
    :param(_param), retype(_ret) {}

    std::vector<TypePtr>paramType() const { return param; }
    TypePtr retType() const { return retype; }
    bool OperatorMatch(lex::Token_type op, const TypePtr type);
    bool UnaryOpMatch(lex::Token_type op);
    KindType type() const { return TYPE_FUNCTION; }

};

class StructType: public Type{
private:
    std::map<std::string,TypePtr>mem;
public:
    StructType(std::map<std::string,TypePtr> &_mem) 
    :mem(_mem) {}

    //std::string eleName() const {return name;}
    std::map<std::string,TypePtr>member() const {return mem;}
    bool contain(std::string name) {
        if(mem.find(name) != mem.end()){
            return true;
        }else{
            return false;
        }
    }
    bool matchType(std::string name, TypePtr ty) {
        if(mem[name]->type() == ty->type()){
            return true;
        }else{
            return false;
        }
    }

    bool OperatorMatch(lex::Token_type op, const TypePtr type);
    bool UnaryOpMatch(lex::Token_type op);
    KindType type() const { return TYPE_STRUCT; }


};

class Array: public Type{
private:

public:

    bool OperatorMatch(lex::Token_type op, const TypePtr type);
    bool UnaryOpMatch(lex::Token_type op);
    KindType type() const { return TYPE_ARRAY; }

};

class Pointer: public Type{
private:
    int ptr_size;
    TypePtr base;
public:
    Pointer(int &_ptr_size, TypePtr &_base)
    :ptr_size(_ptr_size), base(_base) {}

    int ptrSize() const {return ptr_size;}
    TypePtr baseType() const {return base;}
    KindType type() const { return TYPE_POINTER; }
    bool UnaryOpMatch(lex::Token_type op);
    // KindType base_type() const { reTYPE_turn base->type(); }
    bool OperatorMatch(lex::Token_type op, const TypePtr type);


};


class TypeGenerator{
    public:
    static TypePtr Integer();
    static TypePtr Boolean();
    static TypePtr Decimal();
    static TypePtr String();
    static TypePtr StructTyGen(std::map<std::string, TypePtr>&_ele);
    static TypePtr FuncTypeGenerate(std::vector<TypePtr>&p_type, TypePtr r_type);
    static TypePtr Generate(KindType type);
};

}