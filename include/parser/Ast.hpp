#pragma once

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"

using namespace lex;
namespace ast{


    class Ast {
    protected:
        tok_t t;
    public:
        virtual ~Ast() = default;

        virtual std::string node_str() const = 0;
       // virtual void accept() const = 0;
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
        std::string node_str() const;
        //void accept() const;
    };

  
    class NumericLitral: public Ast {
        private:
        tokt tok;
      
      //  std::string Int;
        public:
        NumericLitral(tokt &_tok)
        : tok(_tok) {}

        tokt token() const { return tok; };
        std::string node_str() const;
        //void accept() const;
    };

    class BoolLitral: public Ast {
        private:
      //  std::string val;
        tokt tok;
        public:
        BoolLitral(tokt &_tok)
        : tok(_tok) {}

        //std::string value() const;
        tokt token() const { return tok; }
        std::string node_str() const;
        //void accept() const;
    };

    class StringLitral: public Ast {
        private:
        tokt tok;
        bool chr;
        public:
        StringLitral(tokt &_tok, bool _chr)
        : tok(_tok), chr(_chr) {}

        tokt token() const{ return tok; }
        //std::string value() const{ return tok.data; }
        bool ischar() const{ return chr; }
        std::string node_str() const;
        //void accept() const;
    };


    class NullLitral: public Ast {
        private:
        tokt tok;
        public:
        NullLitral(tokt &_tok)
        : tok(_tok) {}

        tokt token() const{ return tok; }
        std::string node_str() const;
        //void accept() const;
    };

    class FloatLitral: public Ast {
        private:
        tokt tok;
        public:
        FloatLitral(tokt &_tok)
        :tok(_tok) {}

        tokt token() const{ return tok; }
        //std::string value() const { return tok.data; }
        std::string node_str() const;
        //void accept() const;
    };

    class Identifier: public Ast {
        private:
        tokt tok;
        public:
        Identifier(tokt &_tok)
            :tok(_tok) {}

        tokt token() const{ return tok; }
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
    };


    class IntType: public Ast {
        private:
        tokt tok;
        public:
        IntType(tokt &_tok)
        : tok(_tok) 
        {}
       
        tokt token() const{ return tok; }
        std::string node_str() const;
        //void accept() const;
    };

    class StringType: public Ast {
        private:
        tokt tok;
        public:
        StringType(tokt &_tok)
        : tok(_tok) 
        {}
        
        tokt token() const{ return tok; }
        std::string node_str() const;
        //void accept() const;
    };

    
    class FloatType: public Ast {
        private:
        tokt tok;
        public:
        FloatType(tokt &_tok)
        : tok(_tok) 
        {}
        
        tokt token() const{ return tok; }
        std::string node_str() const;
        //void accept() const;
    };

    class BoolType: public Ast {
        private:
        tokt tok;
        public:
        BoolType(tokt &_tok)
        : tok(_tok) {}
        
        tokt token() const { return tok; }
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;

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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
    //     //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;

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
        std::string node_str() const;
        //void accept() const;

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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
    };


    class BranchState: public Ast {
        private:
        tokt tok;
        public:
        BranchState(tokt &_tok)
        : tok(_tok) {}

        tokt token() const { return tok; }
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
    };



    class AssignmentState: public Ast {
        private:
        tokt tok;
        AstPtr left;
        Token_type op;
        AstPtr right;
        
        public:
        AssignmentState(tokt &_tok, AstPtr &_left, Token_type &_assop, AstPtr &_right)
        : tok(_tok), left(_left), op(_assop), right(_right) {}
       
        tokt token() const{ return tok; }
        AstPtr leftVar() const{return left;}
        Token_type opreator() const{return op;}
        AstPtr rightVal() const{return right;}
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const {return "";}
        //void accept() const;

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
        std::string node_str() const{return "";}
        //void accept() const;

    };


    class VariableState: public Ast {
        private:
        tokt tok;
        std::vector<AstPtr> name;
        AstPtr type;
        public:
        VariableState(tokt &_tok, std::vector<AstPtr> &_var, AstPtr &_type)
        : tok(_tok), name(_var), type(_type) {}

        tokt token() const{ return tok; }
        std::vector<AstPtr> varname() const{return name;}
        AstPtr vartype() const{return type;}
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
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
        std::string node_str() const;
        //void accept() const;
    };

}
