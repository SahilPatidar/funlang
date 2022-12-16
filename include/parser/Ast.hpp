#ifndef AST_H
#define AST_H

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"

using namespace lex;
namespace ast{


    class Ast {
    
    protected:
        tok_t token_list;
    public:
        virtual ~Ast() = default;
    };
   
    using AstPtr = std::shared_ptr<Ast>;

    class Program: public Ast {
        private:
        uint tok;
        std::vector<AstPtr> statement;
        public:
        Program(uint &_tok, std::vector<AstPtr>&_state) 
        :tok(_tok), statement(_state) {}

        tokt token() const;
        std::vector<AstPtr> statements() const;
        void accept() const;
    };

  
    class NumericLitral: public Ast {
        private:
        uint tok;
      
      //  std::string Int;
        public:
        NumericLitral(uint &_tok)
        : tok(_tok) {}

        std::string value() const;
        uint token() const;
        void accept() const;
    };

    class BoolLitral: public Ast {
        private:
      //  std::string val;
        uint tok;
        public:
        BoolLitral(uint &_tok)
        : tok(_tok) {}

        std::string value() const;
        uint token() const;
        void accept() const;
    };

    class StringLitral: public Ast {
        private:
        uint tok;
        bool chr;
        public:
        StringLitral(uint &_tok, bool _chr)
        : tok(_tok), chr(_chr) {}

        std::string value() const;
        uint token() const;
        bool ischar() const;
        void accept() const;
    };


    class NullLitral: public Ast {
        private:
        uint tok;
        public:
        NullLitral(uint &_tok)
        : tok(_tok) {}

        uint token() const;
        void accept() const;
    };

    class FloatLitral: public Ast {
        private:
        uint tok;
        public:
        FloatLitral(uint &_tok)
            :tok(_tok) {}

        std::string value() const;
        uint token() const;
        void accept() const;
    };

    class Identifier: public Ast {
        private:
        uint tok;
        std::string id;
        public:
        Identifier(std::string &id, uint &_tok)
            :id(id), tok(_tok) {}

        std::string iden() const { return id; }
        tokt token() const { return token_list[tok]; }
        void accept() const;
    };


    class BlockStatement: public Ast {
        private:
        int lpos;
        std::vector<AstPtr> statms;
        int rpos;
        public:
        BlockStatement(int &_lpos, int &_rpos, std::vector<AstPtr> &_state)
            :lpos(_lpos), rpos(_rpos), statms(_state) {}

        int lParen() const { return lpos; }
        std::vector<AstPtr> statement() const { return statms; }
        int rParen() const { return rpos; }
        void accept() const;
    };
    
    
    class EnumLitral: public Ast {
        private:
        uint tok;
        AstPtr var;
        std::vector<std::pair<AstPtr,AstPtr>>u_data;
        public:
        EnumLitral( AstPtr &_var,  std::vector<std::pair<AstPtr,
                    AstPtr>>&_u_data, uint &_tok)
            :var(_var), u_data(_u_data), tok(_tok) 
            {}

        std::vector<std::pair<AstPtr,AstPtr>> value() const;
        AstPtr varname() const;
        tokt token() const { return token_list[tok]; }
        void accept() const;
    };


    class IntType: public Ast {
        private:
        uint tok;
        public:
        IntType(uint &_tok)
        : tok(_tok) 
        {}
       
        tokt token() const { return token_list[tok]; }
        void accept() const;
    };

    class StringType: public Ast {
        private:
        uint tok;
        public:
        StringType(uint &_tok)
        : tok(_tok) 
        {}
        
        tokt token() const { return token_list[tok]; }
        void accept() const;
    };

    
    class FloatType: public Ast {
        private:
        uint tok;
        public:
        FloatType(uint &_tok)
        : tok(_tok) 
        {}
        
        tokt token() const { return token_list[tok]; }
        void accept() const;
    };

    class BoolType: public Ast {
        private:
        uint tok;
        public:
        BoolType(uint &_tok)
        : tok(_tok) {}
        
        tokt token() const { return token_list[tok]; }
        void accept() const;
    };


    class TypeState: public Ast {
        private:
        uint tok;
        AstPtr dest;
        AstPtr src;
        public:
        TypeState(uint &_tok, AstPtr &_dest, AstPtr &_src)
        : tok(_tok), dest(_dest), src(_src) {}

        tokt token() const { return token_list[tok]; }
        AstPtr destination() const { return dest; }
        AstPtr source() const { return src; }
        void accept() const;
    };


    class ConstExpr: public Ast {
        private:
        uint tok;
        AstPtr name;
        AstPtr type;
        AstPtr val;
        public:
        ConstExpr(uint &_tok, AstPtr &_var, AstPtr &_type, AstPtr &_val)
        : tok(_tok), name(_var), type(_type), val(_val) {}

        tokt token() const { return token_list[tok]; }
        AstPtr vname() const { return name; }
        AstPtr vartype() const { return type; }
        AstPtr value() const { return val; }
        void accept() const;
    };


    class IndexExpr: public Ast {
        private:
        uint tok;
        AstPtr expr;
        int lpos;
        AstPtr index;
        int rpos;
        
        public:
        IndexExpr(uint &_tok, AstPtr &_expr, int &_lpos, AstPtr &_index, int &_rpos)
        : tok(_tok), expr(_expr),  index(_index), lpos(_lpos)
        {}

        tokt token() const { return token_list[tok]; }
        AstPtr expression() const { return expr; }
        int l_position() const { return lpos; }
        AstPtr index() const { return expr; }
        int r_position() const { return rpos; }
        void accept() const;

    };


    class ArrayType: public Ast {
        private:
        uint tok;
        AstPtr size;
        AstPtr type;
        public:
        ArrayType(uint &_tok, AstPtr &_size, AstPtr &_type)
        : tok(_tok), size(_size), type(type) {}

        tokt token() const { return token_list[tok]; }
        AstPtr arraysize() const { return size; }
        AstPtr arraytype() const { return type; }
        void accept() const;
    };


    class ComposeExpr: public Ast{
        private:
        uint tok;
        AstPtr expr;
        AstPtr body;
        public:
        ComposeExpr(uint &_tok, AstPtr &_expr, AstPtr &_field) 
        : tok(_tok), expr(_expr), body(_field) {}

        tokt token() const { return token_list[tok]; }
        AstPtr exr() const { return expr; }
        AstPtr field() const { return body; }
        void accept() const;
    };


    class BineryExper: public Ast {
        private:
        uint tok;
        AstPtr left;
        Token_type op;
        AstPtr right;
        public:
        BineryExper(uint &_tok, AstPtr &_left, Token_type &_op, AstPtr &_right)
        :tok(_tok), left(_left), op(_op), right(_right) {}

        tokt token() const { return token_list[tok]; }
        AstPtr rightOpr() const { return right; }
        Token_type oprator() const { return op; }
        AstPtr leftOpr() const { return left; }
        void accept() const;
    };

    class ImportState: public Ast{
        private:


        public:

    };

    

    class UnaryExper: public Ast {
        private:
        uint tok;
        AstPtr var;
        Token_type op;
        
        public:
        UnaryExper(uint &_tok, AstPtr &_var, Token_type &_op)
        : tok(_tok), var(_var), op(_op)
        {}

        Token_type op() const { return op; };
        tokt token() const { return token_list[tok]; }
        AstPtr variable() const { return var; }
        void accept() const;
    };


    class ForLoopState: public Ast{
        private:
        AstPtr h1;
        AstPtr h2;
        AstPtr h3;
        AstPtr loopbody;
        uint tok;
       
        public:
        ForLoopState(AstPtr &_h1, AstPtr &_h2,
                     AstPtr &_h3, AstPtr &_loopbody, uint &_tok)
            :h1(_h1),  h2(_h2), h3(_h3),
                         loopbody(_loopbody), tok(_tok) {}

        AstPtr variable() const { return h1; }
        AstPtr loopCondition() const { return h2; }
        AstPtr loopExpression() const { return h3; }
        AstPtr loopBody() const { return loopbody; }
        tokt token() const {return token_list[tok]; }
        void accept() const;

    };


    class IfStatement: public Ast{
        private:
        AstPtr cond;
        AstPtr ifbody;
        AstPtr elbody;
        uint tok;
        
        public:
        IfStatement(AstPtr &_cond , AstPtr &_ifbody,
                             AstPtr &_elbody, uint &_tok)
        : cond(_cond), ifbody(_ifbody), 
                        elbody(_elbody), tok(_tok) {}
        
        AstPtr condition() const { return cond; }
        AstPtr ifbody() const { return ifbody; }
        AstPtr elsebody() const { return  elbody; }
        tokt token() const { return token_list[tok]; }
        void accept() const;
    };


     class PointerType: public Ast {
        private:
        uint tok;
        Token_type op;
        AstPtr base;
       
        public:
        PointerType(uint &tok,Token_type &_op, AstPtr &_type)
        : tok(tok), op(_op), base(_type) {}

        tokt token() const { return token_list[tok]; }
        AstPtr type() const { return base; }
        void accept() const;
    };


    class BranchState: public Ast {
        private:
        uint tok;
        public:
        BranchState(uint &_tok)
        : tok(_tok) {}

        tokt token() const { return token_list[tok]; }
        void accept() const;
    };


     class MemberExpr: public Ast {
        private:
        uint tok;
        AstPtr right;
        Token_type mem_op;
        AstPtr left;
        
        public:
        MemberExpr(uint &_tok, AstPtr &_left, Token_type &_mem_op, AstPtr &_right) 
        : tok(_tok), mem_op(_mem_op), left(_left) ,right(_right) {}

        tokt token() const;
        AstPtr rightid() const;
        Token_type mem_operator() const;
        AstPtr leftid() const;
        void accept() const;
    };



    class StructState: public Ast {
        private:
        uint tok;
        std::vector<AstPtr> elemt;
        
        public:
        StructState(uint &_tok, std::vector<AstPtr> &_mem)
        : tok(_tok), elemt(_mem) {}

        tokt token() const { return token_list[tok]; }
        std::vector<AstPtr> element() const { return elemt; }
        void accept() const;
    };


    class ExpressionList:public Ast {
        private:
        int lpos;
        std::vector<AstPtr>list;
        int rpos;
       
        public:
        ExpressionList(int &_lpos, std::vector<AstPtr> &_list, int &_rpos)
        :lpos(_lpos), list(_list), rpos(_rpos) {}

        int lposition() const;
        std::vector<AstPtr> listof() const;
        int rposition() const;
        void accept() const;
    };



    class AssignmentState: public Ast {
        private:
        uint tok;
        AstPtr left;
        Token_type op;
        AstPtr right;
        
        public:
        AssignmentState(uint &_tok, AstPtr &_left, Token_type &_assop, AstPtr &_right)
        : tok(_tok), left(_left), op(_assop), right(_right) {}
       
        tokt token() const;
        AstPtr leftVar() const;
        Token_type opreator() const;
        AstPtr rightVal() const;
        void accept() const;
    };



    class NewState:public Ast{
    private:
        uint tok;
        AstPtr type;


    public:
        NewState(uint &_tok, AstPtr &_type)
        :tok(_tok), type(_type) {}
        tokt token() const { return token_list[tok]; }
        AstPtr typePtr() const{ return type; }
        void accept() const;

    };


    class FreeState:public Ast{

    private:
        uint tok;
        int lpos;
        AstPtr ptr;
        int rpos;

    public:
        FreeState(uint &_tok, AstPtr &_ptr)
        :tok(_tok), ptr(_ptr) {}
        tokt token() const { return token_list[tok]; }
        AstPtr typePtr() const{ return ptr; }
        void accept() const;

    };


    class VariableState: public Ast {
        private:
        uint tok;
        std::vector<AstPtr> name;
        AstPtr type;
        public:
        VariableState(uint &_tok, std::vector<AstPtr> &_var, AstPtr &_type)
        : tok(_tok), name(_var), type(_type) {}

        tokt token() const;
        std::vector<AstPtr> varname() const;
        AstPtr vartype() const;
        void accept() const;
    };


    class Param: public Ast{
        private:
        int tok;
        AstPtr iden;
        AstPtr type;
        public:
        Param(int &_tok, AstPtr &_iden, AstPtr &_type)
        : tok(_tok), iden(_iden), type(_type) {}
        
        tokt token() const { return token_list[tok]; }
        AstPtr Piden() const;
        AstPtr Ptype() const;
        void accept() const;
    };


    class FunctionDef: public Ast {
        private:
        uint tok;
        AstPtr name;
        std::vector<AstPtr> param;
        AstPtr retype;
        AstPtr funcbody;

        public:
        FunctionDef(uint &_tok, AstPtr &_name, std::vector<AstPtr> &_parameter,
                                AstPtr  _retype, AstPtr &_uncbody)
         : tok(_tok), name(_name), param(_parameter),
                         retype(_retype), funcbody(funcbody) {}

        tokt token() const { return token_list[tok]; }
        AstPtr func_name() const { return name; }
        std::vector<AstPtr> parameter() const { return param; }
        AstPtr ret_type() const { return retype; }
        AstPtr func_Body() const { return funcbody; }
        void accept() const;
    };

    class ReturnState: public Ast {
        private:
        uint tok;
        AstPtr val;

        public:
        ReturnState(uint &_tok, AstPtr &_val)
        : tok(_tok), val(_val) {}

        tokt token() { token_list[tok]; }
        AstPtr value() { return val; }
        void accept() const;
    };

    class FunctionCall: public Ast {
        private:
        uint tok;
        AstPtr name;
        std::vector<AstPtr> args;

        public:
        FunctionCall(uint &_tok, AstPtr &_name, std::vector<AstPtr> &_args)
        : tok(_tok), name(_name), args(_args) {}


        tokt token() const { token_list[tok]; }
        AstPtr funcname() const { return name; }
        std::vector<AstPtr> arg() const { return args; }
        void accept() const;
    };

}
#endif