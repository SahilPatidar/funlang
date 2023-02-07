#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"
#include"../analyzer/ast_visitor.hpp"
#include"type.hpp"

using namespace lex;
namespace ast{

    enum NodeCategory{
        NODE_BLOCK,
        NODE_TUPLE,
        NODE_USE,
        NODE_NUM_LITERAL,
        NODE_BOOL_LITERAL,
        NODE_FLOAT_LITERAL,
        NODE_NULL_LITERAL,
        NODE_STRING_LITERAL,
        NODE_IDEN,
        NODE_ENUM,

        NODE_BINERY_EXPR,
        NODE_POSTFIX,
        NODE_PREFIX,
        NODE_MEM_EXPR,
        NODE_ASSN_EXPR,
        NODE_LIST_EXPR,
        NODE_INDEX_EXPR,
        NODE_EXTERN,

        NODE_INT_TYPE,
        NODE_FLOAT_TYPE,
        NODE_STRING_TYPE,
        NODE_BOOL_TYPE,
        NODE_ARRAY_TYPE,
        NODE_PTR_TYPE,
        NODE_REF_TYPE,
        NODE_FN_TYPE,

        NODE_IF_STM,
        NODE_WHILE_STM,
        NODE_IN_STM,
        NODE_TYPE_STM,
        NODE_FOR_STM,
        NODE_CONST_STM,
        NODE_LET_STM,
        NODE_BRANCH_STM,
        NODE_STRUCT_STM,
        NODE_NEW_STM,
        NODE_FREE_STM,
        NODE_RET_STM,
        
        NODE_PARAM,
        NODE_CALL,
        NODE_FUNC_DEF,

    };


    class Ast {
    public:
        virtual ~Ast() {} //= default;
        virtual std::string toString() const = 0;
        virtual NodeCategory nodeCategory() const = 0;
        virtual void accept(AstVisitor& visitor) const = 0;
    };
   
    using AstPtr = std::shared_ptr<Ast>;

    class Program: public Ast {
        private:
        tokt tok;
        std::vector<AstPtr> statms;
        public:
        Program(tokt &_tok, std::vector<AstPtr>&_state) 
        :tok(_tok), statms(_state) {}

        tokt token() const { return tok; }
        std::vector<AstPtr> statements() const { return statms; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;  
    };

  
    class NumericLiteral: public Ast {
        private:
        tokt tok;
      //  std::string Int;
        public:
        NumericLiteral(tokt &_tok)
        : tok(_tok) {}

        tokt token() const { return tok; };
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_NUM_LITERAL; }
    };

    class BoolLiteral: public Ast {
        private:
      //  std::string val;
        tokt tok;
        public:
        BoolLiteral(tokt &_tok)
        : tok(_tok) {}

        //std::string value() const;
        tokt token() const { return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_BOOL_LITERAL; }
    };

    class StringLiteral: public Ast {
        private:
        tokt tok;
        bool chr;

        public:
        StringLiteral(tokt &_tok, bool _chr)
        : tok(_tok), chr(_chr) {}

        tokt token() const{ return tok; }
        //std::string value() const{ return tok.data; }
        bool ischar() const{ return chr; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_STRING_LITERAL; }
    };


    class NullLiteral: public Ast {
        private:
        tokt tok;
        public:
        NullLiteral(tokt &_tok)
        : tok(_tok) {}

        tokt token() const{ return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_NULL_LITERAL; }
    };

    class FloatLiteral: public Ast {
        private:
        tokt tok;

        public:
        FloatLiteral(tokt &_tok)
        :tok(_tok) {}

        tokt token() const{ return tok; }
        //std::string value() const { return tok.data; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FLOAT_LITERAL; }
    };

    class Identifier: public Ast {
        private:
        tokt tok;
        std::string name;
        //TypePtr typeinfo;
        public:
        Identifier(tokt &_tok, std::string &_name)
            :tok(_tok), name(_name){}

        tokt token() const { return tok; }
        // TypePtr typeInfo() const { return typeinfo; }
        // void setTypeInfo(TypePtr &type) { typeinfo = type; }
        std::string iden() const { return name; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_IDEN; }
    };


    class BlockStatement: public Ast {
    private:
        std::vector<AstPtr> statms;
    public:
        BlockStatement(std::vector<AstPtr> &_state)
            :statms(_state) {}

        std::vector<AstPtr> statement() const {return statms;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_BLOCK; }
    };
    
    
    // class EnumLitral: public Ast {
    //     private:
    //     tokt tok;
    //     std::vector<std::pair<AstPtr,AstPtr> >u_data;
    //     public:
    //     EnumLitral(tokt &_tok, AstPtr &_var,  std::vector<std::pair<AstPtr,
    //                 AstPtr> >&_u_data)
    //     :tok(_tok), u_data(_u_data) 
    //     {}

    //     tokt token() const{ return tok; }
    //     std::vector<std::pair<AstPtr,AstPtr> > value() const{return u_data;}
    //     std::string toString() const;
        // void accept(AstVisitor& visitor) const;
        // NodeCategory nodeCategory() const { return NODE_ENUM; }
    // };


    class PreDefineType: public Ast{
        private:
        tokt tok;
        //TypePtr typeinfo;
        public:
        PreDefineType(tokt &_tok)
        : tok(_tok) 
        {}
        //TypePtr setTy(TypePtr ty){typeinfo=ty;}
        //TypePtr getTy()const{return typeinfo;}
        tokt token() const{ return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;

    };


    class Variadic: public Ast {
        private:
        tokt tok;
        AstPtr left;
        AstPtr right;
        public:
        Variadic(tokt &_tok, AstPtr &_left, AstPtr &_right)
        : tok(_tok), left(_left), right(_right)
        {}
        Variadic(tokt &_tok)
        : tok(_tok)
        {}
       
        tokt token() const{ return tok; }
        AstPtr leftExpr() const{ return left; }
        AstPtr rightExpr() const{ return right; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_INT_TYPE; }
    };


     class PointerExpr: public Ast {
        private:
        tokt tok;
        AstPtr base;
        bool istype;
        public:
        PointerExpr(tokt &tok, AstPtr &_type, bool &_istype)
        : tok(tok), base(_type), istype(_istype) {}

        tokt token() const { return tok; }
        AstPtr type() const { return base; }
        bool isType() const { return istype; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_PTR_TYPE; }
    };

     class RefExpr: public Ast {
        private:
        tokt tok;
        Token_type op;
        AstPtr base;
        bool istype;
        public:
        RefExpr(tokt &tok,Token_type &_op, AstPtr &_type, bool &_istype)
        : tok(tok), op(_op), base(_type), istype(_istype) {}

        tokt token() const { return tok; }
        AstPtr type() const { return base; }
        bool isType() const { return istype; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_REF_TYPE; }
    };

    class GroupedExpr:public Ast {
        AstPtr expr;
        public:
        GroupedExpr(AstPtr &_expr)
        :expr(_expr) {}

        AstPtr expression() const { return expr; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
    };

    class FunType: public Ast {
        private:
        tokt tok;
        std::vector<AstPtr> ty;
        AstPtr ret;
       
        public:
        FunType(tokt &tok, std::vector<AstPtr> &_ty, AstPtr &_ret)
        : tok(tok), ty(_ty), ret(_ret) {}

        tokt token() const { return tok; }
        std::vector<AstPtr> type() const { return ty; }
        AstPtr retval() const { return ret; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FN_TYPE; }
    };

    class TypeState: public Ast {
        private:
        tokt tok;
        AstPtr left;
        AstPtr right;

        public:
        TypeState(tokt &_tok, AstPtr &_l, AstPtr &_r)
        : tok(_tok), left(_l), right(_r) {}

        tokt token() const { return tok; }
        AstPtr left_opar() const{ return left; }
        AstPtr right_opar() const{return right;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_TYPE_STM; }
    };

    class AsState: public Ast {
        private:
        tokt tok;
        AstPtr left;
        AstPtr right;

        public:
        AsState(tokt &_tok, AstPtr &_l, AstPtr &_r)
        : tok(_tok), left(_l), right(_r) {}

        tokt token() const { return tok; }
        AstPtr left_opar() const{ return left; }
        AstPtr right_opar() const{return right;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_TYPE_STM; }
    };


    class IndexExpr: public Ast {
        private:
        AstPtr iden;
        std::vector<AstPtr> index;
        
        public:
        IndexExpr(AstPtr expr, std::vector<AstPtr> &_index)
        :iden(expr),index(_index)
        {}

        AstPtr identifier() const{return iden;}
        std::vector<AstPtr> arry_index() const{return index;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_INDEX_EXPR; }

    };


    class ArrayType: public Ast {
        private:
        tokt tok;
        std::vector<AstPtr> size;
        AstPtr type;
        public:
        ArrayType(tokt &_tok, std::vector<AstPtr> &_size, AstPtr &_type)
        : tok(_tok), size(_size), type(_type) {}

        tokt token() const{ return tok; }
        std::vector<AstPtr> arraysize() const{return size;}
        AstPtr arraytype() const{return type;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_ARRAY_TYPE; }
    };


    class Extern: public Ast {
        private:
        tokt tok;
        AstPtr lib;
        AstPtr block;
        public:
        Extern(tokt &_tok, AstPtr &_lib, AstPtr &_block)
        :tok(_tok), lib(_lib), block(_block) {}

        tokt token() const {return tok;}
        AstPtr externName() const {return lib;}
        AstPtr expression()const {return block;}
        std::string toString() const;
        //void accept(AstVisitor &vistitor) const;
        NodeCategory nodeCategory() const {return NODE_EXTERN;}
    };

    class Path: public Ast {
        private:
        tokt tok;
        AstPtr owner;
        AstPtr block;
        public:
        Path(tokt &_tok, AstPtr &_lib, AstPtr &_block)
        :tok(_tok), owner(_lib), block(_block) {}

        tokt token() const {return tok;}
        AstPtr lexpression() const {return owner;}
        AstPtr rexpression()const {return block;}
        std::string toString() const;
        //void accept(AstVisitor &vistitor) const;
        NodeCategory nodeCategory() const {return NODE_EXTERN;}
    };

    class BineryExper: public Ast {
    private:
        tokt tok;
        AstPtr left;
        Token_type op;
        AstPtr right;

    public:
        BineryExper(tokt &_tok, AstPtr &_left, Token_type &_op, AstPtr &_right)
        :tok(_tok), left(_left), op(_op), right(_right) {}

        tokt token() const{ return tok; }
        AstPtr leftOpr() const{return left;}
        Token_type oprator() const{return op;}
        AstPtr rightOpr() const{return right;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_BINERY_EXPR; }
    };


    class Use: public Ast{
    private:
        tokt tok;
        AstPtr name;
        AstPtr path;

    public:
        Use(tokt &_tok, AstPtr &_name, AstPtr &_path)
        : tok(_tok), path(_path) {}

        tokt token() const {return tok;}
        AstPtr nameof() const {return name;}
        AstPtr import_path() const {return path;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
         NodeCategory nodeCategory() const { return NODE_USE; }
    };


    class Tuple: public Ast{
    private:
        tokt tok;
        std::vector<AstPtr>tuple;
        bool istype;
        // bool isEmpty;
    public:
        Tuple(tokt &_tok, std::vector<AstPtr> &_tuple, bool &_isType)
        : tok(_tok), tuple(_tuple), istype(_isType) {}

        tokt token() const {return tok;}
        std::vector<AstPtr> tupleEle() const{return tuple;}
        bool isTupleType()const{return istype;}
        //bool isEmptyTuple()const{return isEmpty;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_TUPLE;}
    };


    class PrefixExper: public Ast {
        private:
        tokt tok;
        AstPtr var;
        Token_type op;
        
        public:
        PrefixExper(tokt &_tok, AstPtr &_var, Token_type &_op)
        : tok(_tok), var(_var), op(_op)
        {}

        tokt token() const{ return tok; }
        Token_type oprator() const{return op;}
        AstPtr variable() const{return var;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_PREFIX; }
    };



    class WhileLoop: public Ast{
    private:
        tokt tok;
        AstPtr expr;
        AstPtr body;

    public:
        WhileLoop(tokt &_tok, AstPtr &_expr, AstPtr &_body )
            :tok(_tok), expr(_expr), body(_body)  {}

        AstPtr expression() const { return expr; }
        AstPtr loopbody() const { return body; }
        tokt token() const {return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FOR_STM; }

    };


    class ForInLoop: public Ast{
    private:
        tokt tok;
        AstPtr left;
        AstPtr right;
        AstPtr body;
        
    public:
        ForInLoop(tokt &_tok, AstPtr &_left, AstPtr &_right, AstPtr &_body )
            :tok(_tok), left(_left), right(_right), body(_body)  {}

        AstPtr leftExpr() const { return left; }
        AstPtr rightExpr() const { return right; }
        AstPtr loopbody() const { return body; }
        tokt token() const {return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FOR_STM; }

    };

    class IfStatement: public Ast{
        private:
        tokt tok;
        AstPtr cond;
        AstPtr ifbody;
        AstPtr elbody;
        
        public:
        IfStatement(tokt &_tok, AstPtr &_cond , AstPtr &_ifbody,
                             AstPtr &_elbody)
        : tok(_tok), cond(_cond), ifbody(_ifbody), 
                        elbody(_elbody) {}
        
        tokt token() const { return tok; }
        AstPtr condition() const { return cond; }
        AstPtr if_body() const { return ifbody; }
        AstPtr else_body() const { return  elbody; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_IF_STM; }
    };


    class BranchState: public Ast {
        private:
        tokt tok;
        public:
        BranchState(tokt &_tok)
        : tok(_tok) {}

        tokt token() const { return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_BRANCH_STM; }
    };


     class MemberExpr: public Ast {
        private:
        tokt tok;
        AstPtr left;
        Token_type mem_op;
        AstPtr right;
        
        public:
        MemberExpr(tokt &_tok, AstPtr &_left, Token_type &_mem_op, AstPtr &_right) 
        : tok(_tok), left(_left), mem_op(_mem_op) ,right(_right) {}

        tokt token() const{ return tok; }
        AstPtr leftid() const{return left;}
        Token_type mem_operator() const{return mem_op;}
        AstPtr rightid() const{return right;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_MEM_EXPR; }
    };



    class StructState: public Ast {
        private:
        tokt tok;
        AstPtr iden;
        std::vector<AstPtr> elemt;
        bool isDecl;
        public:
        StructState(tokt &_tok, AstPtr &_iden, std::vector<AstPtr> &_mem, bool &_isDecl)
        : tok(_tok), iden(_iden), elemt(_mem), isDecl(_isDecl) {}

        tokt token() const { return tok; }
        AstPtr name() const { return iden; }
        std::vector<AstPtr> element() const { return elemt; }
        bool isDeclaration() const { return isDecl; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_STRUCT_STM; }
    };


    class ListExpr: public Ast {
        private:
        tokt tok;
        std::vector<AstPtr>list;
        public:
        ListExpr(tokt &_tok, std::vector<AstPtr> &_list)
        :tok(_tok), list(_list) {}

        tokt token() const { return tok; }
        std::vector<AstPtr> listof() const { return list; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_LIST_EXPR; }
    };



    class AssignmentExpr: public Ast {
        private:
        tokt tok;
        AstPtr left;
        AstPtr right;
        public:
        AssignmentExpr(tokt &_tok, AstPtr &_left, AstPtr &_right)
        : tok(_tok), left(_left), right(_right)
        {}
       
        tokt token() const{ return tok; }
        AstPtr lvalue() const{return left;}
        Token_type oprator() const{return tok.tok_type;}
        AstPtr rvalue() const{return right;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_ASSN_EXPR; }
    };


    class VarState: public Ast {
        private:
        tokt tok;
        AstPtr name;
        AstPtr type;
        //TypePtr typeinfo;
        AstPtr val;
        public:
        VarState(tokt &_tok, AstPtr &_var, AstPtr &_type, AstPtr &_val)
        : tok(_tok), name(_var), type(_type), val(_val) {}

        tokt token() const{ return tok; }
        AstPtr varName() const{return name;}
        AstPtr varType() const{return type;}
        AstPtr varVal() const{return val;}
        // TypePtr getType() const {return typeinfo;}
        // void setType(const TypePtr _typeinfo) {typeinfo = _typeinfo;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_LET_STM; }
    };


    class Parameter: public Ast{
        private:
        AstPtr iden;
        AstPtr type;
        public:
        Parameter( AstPtr &_iden, AstPtr &_type)
        : iden(_iden), type(_type) {}
        
        AstPtr identifier() const{ return iden; }
        AstPtr p_type() const{ return type; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_PARAM; }
    };


    class FunctionDef: public Ast {
        private:
        tokt tok;
        AstPtr name;
        std::vector<AstPtr> param;
        AstPtr retype;
        AstPtr body;

        public:
        FunctionDef(tokt &_tok, AstPtr &_name, std::vector<AstPtr> &_parameter,
                                AstPtr  _retype, AstPtr &_body)
         : tok(_tok), name(_name), param(_parameter),
                         retype(_retype), body(_body) {}

        tokt token() const { return tok; }
        AstPtr func_name() const { return name; }
        std::vector<AstPtr> parameter() const { return param; }
        AstPtr ret_type() const { return retype; }
        AstPtr func_body() const { return body; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FUNC_DEF; }
    };


    class ReturnState: public Ast {
        private:
        tokt tok;
        AstPtr val;

        public:
        ReturnState(tokt &_tok, AstPtr &_val)
        : tok(_tok), val(_val) {}

        tokt token() const { return tok; }
        AstPtr value() const { return val; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_RET_STM; }
    };


    class FunctionCall: public Ast {
        private:
        tokt tok;
        AstPtr name;
        std::vector<AstPtr> args;

        public:
        FunctionCall(tokt &_tok, AstPtr &_name, std::vector<AstPtr> &_args)
        : tok(_tok), name(_name), args(_args) {}


        tokt token() const { return tok; }
        AstPtr funcname() const { return name; }
        std::vector<AstPtr> arg() const { return args; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_CALL; }
    };

}
