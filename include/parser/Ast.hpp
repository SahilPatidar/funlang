#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"
#include"../analyzer/ast_visitor.hpp"

using namespace lex;
namespace ast{

    const enum NodeCategory{
        NODE_BLOCK,

        NODE_NUM_LITERAL,
        toString_LITERAL,
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

        NODE_INT_TYPE,
        NODE_FLOAT_TYPE,
        NODE_STRING_TYPE,
        NODE_BOOL_TYPE,
        NODE_ARRAY_TYPE,
        NODE_PTR_TYPE,

        NODE_IF_STM,
        NODE_IN_STM,
        NODE_TYPE_STM,
        NODE_FOR_STM,
        NODE_CONST_STM,
        NODE_LET_STM,
        NODE_BRANCH_STM,
        NODE_STRUCT_STM,
        NODE_LET_STM,
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
        virtual ~Ast() = default;

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
        //NodeCategory nodeCategory() const { return PROGRAM; }    
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
        public:
        Identifier(tokt &_tok, std::string &_name)
            :tok(_tok), name(_name){}

        tokt token() const{ return tok; }
        std::string iden() const { return name; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_IDEN; }
    };


    class BlockStatement: public Ast {
        private:
        int lpos;
        std::vector<AstPtr> statms;
        int rpos;
        public:
        BlockStatement(int &_lpos, std::vector<AstPtr> &_state, int &_rpos)
            :lpos(_lpos), statms(_state), rpos(_rpos) {}

        int lParen() const;
        std::vector<AstPtr> statement();
        int rParen() const;
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_BLOCK; }
    };
    
    
    class EnumLitral: public Ast {
        private:
        tokt tok;
        std::vector<std::pair<AstPtr,AstPtr> >u_data;
        public:
        EnumLitral(tokt &_tok, AstPtr &_var,  std::vector<std::pair<AstPtr,
                    AstPtr> >&_u_data)
        :tok(_tok), u_data(_u_data) 
        {}

        tokt token() const{ return tok; }
        std::vector<std::pair<AstPtr,AstPtr> > value() const{return u_data;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_ENUM; }
    };


    class IntType: public Ast {
        private:
        tokt tok;
        public:
        IntType(tokt &_tok)
        : tok(_tok) 
        {}
       
        tokt token() const{ return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_INT_TYPE; }
    };

    class StringType: public Ast {
        private:
        tokt tok;
        public:
        StringType(tokt &_tok)
        : tok(_tok) 
        {}
        
        tokt token() const{ return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_STRING_TYPE; }
    };

    
    class FloatType: public Ast {
        private:
        tokt tok;
        public:
        FloatType(tokt &_tok)
        : tok(_tok) 
        {}
        
        tokt token() const{ return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FLOAT_TYPE; }
    };

    class BoolType: public Ast {
        private:
        tokt tok;
        public:
        BoolType(tokt &_tok)
        : tok(_tok) {}
        
        tokt token() const { return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_BOOL_TYPE; }
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


    class ConstState: public Ast {
        private:
        tokt tok;
        AstPtr name;
        AstPtr type;
        AstPtr val;
        public:
        ConstState(tokt &_tok, AstPtr &_var, AstPtr &_type, AstPtr &_val)
        : tok(_tok), name(_var), type(_type), val(_val) {}

        tokt token() const { return tok; }
        AstPtr vname() const{return name;}
        AstPtr vartype() const{return type;}
        AstPtr value() const{return val;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_CONST_STM; }
    };


    class IndexExpr: public Ast {
        private:
        tokt tok;
        AstPtr expr;
        int lpos;
        AstPtr index;
        int rpos;
        
        public:
        IndexExpr(tokt &_tok, AstPtr &_expr, int &_lpos, AstPtr &_index, int &_rpos)
        : tok(_tok), expr(_expr), lpos(_lpos), index(_index), rpos(_rpos)
        {}

        tokt token() const{ return tok; }
        AstPtr expression() const{return expr;}
        int l_position() const{return lpos;}
        AstPtr arry_index() const{return index;}
        int r_position() const{return rpos;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_INDEX_EXPR; }

    };


    class ArrayType: public Ast {
        private:
        tokt tok;
        AstPtr size;
        AstPtr type;
        public:
        ArrayType(tokt &_tok, AstPtr &_size, AstPtr &_type)
        : tok(_tok), size(_size), type(_type) {}

        tokt token() const{ return tok; }
        AstPtr arraysize() const{return size;}
        AstPtr arraytype() const{return type;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_ARRAY_TYPE; }
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


    // class ImportState: public Ast{
    // private:
    //     tokt tok;
    //     AstPtr path;

    // public:
    //     ImportState(tokt &_tok,AstPtr &_path)
    //     : tok(_tok), path(_path) {}

    //     tokt token() const;
    //     AstPtr import_path() const;
    //     void accept(AstVisitor& visitor) const;
    //      NodeCategory nodeCategory() const { return node; }
    // };

    

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


    class PostfixExper: public Ast {
        private:
        tokt tok;
        AstPtr var;
        Token_type op;
        
        public:
        PostfixExper(tokt &_tok, AstPtr &_var, Token_type &_op)
        : tok(_tok), var(_var), op(_op)
        {}

        Token_type oprator() const { return op; };
        tokt token() const { return tok; }
        AstPtr variable() const { return var; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_POSTFIX; }
    };


    class ForLoopState: public Ast{
        private:
        tokt tok;
        AstPtr h1;
        AstPtr h2;
        AstPtr h3;
        AstPtr body;
        
       
        public:
        ForLoopState(tokt &_tok, AstPtr &_h1, AstPtr &_h2,
                     AstPtr &_h3, AstPtr &_body )
            :tok(_tok), h1(_h1),  h2(_h2),
                 h3(_h3), body(_body)  {}

        AstPtr variable() const { return h1; }
        AstPtr condition() const { return h2; }
        AstPtr expression() const { return h3; }
        AstPtr loopBody() const { return body; }
        tokt token() const {return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FOR_STM; }

    };


    class InState: public Ast{
        private:
        tokt tok;
        AstPtr left;
        AstPtr right;
        AstPtr body;
       
        public:
        InState( tokt &_tok, AstPtr &_left, AstPtr &_right,
                     AstPtr &_body)
            :tok(_tok), left(_left),  right(_right),
                         body(_body)  {}

        AstPtr left_expr() const { return left; }
        AstPtr right_expr() const { return right; }
        AstPtr in_body() const { return body; }
        tokt token() const {return tok; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_IN_STM; }

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


     class PointerType: public Ast {
        private:
        tokt tok;
        Token_type op;
        AstPtr base;
       
        public:
        PointerType(tokt &tok,Token_type &_op, AstPtr &_type)
        : tok(tok), op(_op), base(_type) {}

        tokt token() const { return tok; }
        AstPtr type() const { return base; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_PTR_TYPE; }
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
        std::vector<AstPtr> elemt;
        
        public:
        StructState(tokt &_tok, std::vector<AstPtr> &_mem)
        : tok(_tok), elemt(_mem) {}

        tokt token() const { return tok; }
        std::vector<AstPtr> element() const { return elemt; }
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_STRUCT_STM; }
    };


    class ListExpr: public Ast {
        private:
        tokt tok;
        int lpos;
        std::vector<AstPtr>list;
        int rpos;
        public:
        ListExpr(tokt &_tok, int &_lpos, std::vector<AstPtr> &_list, int &_rpos)
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
        Token_type op;
        AstPtr right;
        
        public:
        AssignmentExpr(tokt &_tok, AstPtr &_left, Token_type &_assop, AstPtr &_right)
        : tok(_tok), left(_left), op(_assop), right(_right) {}
       
        tokt token() const{ return tok; }
        AstPtr lvalue() const{return left;}
        Token_type oprator() const{return op;}
        AstPtr rvalue() const{return right;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_ASSN_EXPR; }
    };



    class NewState:public Ast{
    private:
        tokt tok;
        AstPtr type;


    public:
        NewState(tokt &_tok, AstPtr &_type)
        :tok(_tok), type(_type) {}
        tokt token() const { return tok; }
        AstPtr typePtr() const{ return type; }
        std::string toString() const {return "";}
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_NEW_STM; }

    };


    class FreeState:public Ast{

    private:
        tokt tok;
        int lpos;
        AstPtr ptr;
        int rpos;

    public:
        FreeState(tokt &_tok, AstPtr &_ptr)
        :tok(_tok), ptr(_ptr) {}
        tokt token() const { return tok; }
        AstPtr typePtr() const{ return ptr; }
        std::string toString() const{return "";}
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_FREE_STM; }

    };


    class LetState: public Ast {
        private:
        tokt tok;
        std::vector<AstPtr> name;
        AstPtr type;
        public:
        LetState(tokt &_tok, std::vector<AstPtr> &_var, AstPtr &_type)
        : tok(_tok), name(_var), type(_type) {}

        tokt token() const{ return tok; }
        std::vector<AstPtr> varname() const{return name;}
        AstPtr vartype() const{return type;}
        std::string toString() const;
        void accept(AstVisitor& visitor) const;
        NodeCategory nodeCategory() const { return NODE_LET_STM; }
    };


    class Parameter: public Ast{
        private:
        tokt tok;
        AstPtr iden;
        AstPtr type;
        public:
        Parameter(tokt &_tok, AstPtr &_iden, AstPtr &_type)
        : tok(_tok), iden(_iden), type(_type) {}
        
        tokt token() const { return tok; }
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
        AstPtr ret_val;

        public:
        ReturnState(tokt &_tok, AstPtr &_val)
        : tok(_tok), ret_val(_val) {}

        tokt token() const { return tok; }
        AstPtr value() { return ret_val; }
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
