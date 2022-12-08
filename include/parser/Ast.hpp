#ifndef AST_H
#define AST_H

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"

using namespace lex;
namespace ast{
    
    class Ast{
        public:
        virtual ~Ast() = default;
    };
   
    using AstPtr = std::shared_ptr<Ast>;

    class Program: public Ast {
        private:
        tokt tok;
        std::vector<AstPtr> statement;
        public:
        Program(tokt &_tok, std::vector<AstPtr>&_state) 
        :tok(_tok), statement(_state) {}

        tokt token() const;
        std::vector<AstPtr> statements() const;
        void accept() const;
    };

    class IntergerLitral: public Ast {
        private:
        tokt tok;
        std::string Int;
        public:
        IntergerLitral(std::string &_int, tokt &_tok)
        : Int(_int), tok(_tok) {}

        std::string value() const;
        tokt token() const;
        void accept() const;
    };

    class BoolLitral: public Ast {
        private:
        std::string val;
        tokt tok;
        public:
        BoolLitral(std::string &_val, tokt &_tok)
        : val(_val), tok(_tok) {}

        std::string value() const;
        tokt token() const;
        void accept() const;
    };

    class StringLitral: public Ast {
        private:
        std::string str;
        tokt tok;
        bool chr;
        public:
        StringLitral(tokt &_tok, std::string &_str, bool _chr)
        : tok(_tok), str(_str), chr(_chr) {}

        std::string value() const;
        tokt token() const;
        bool ischar() const;
        void accept() const;
    };

    class NoLiteral: public AstPtr {
        public:
        NoLiteral() = default;
        tokt token() const;
        void accept() const;
    };

    class NullLitral: public AstPtr {
        private:
        tokt tok;
        public:
        NullLitral(tokt &_tok)
        : tok(_tok) {}

        tokt token() const;
        void accept() const;
    };

    class FloatLitral: public Ast {
        private:
        std::string flt;
        tokt tok;
        public:
        FloatLitral(std::string &_flt, tokt &_tok)
            : flt(_flt), tok(_tok) {}

        std::string value() const;
        tokt token() const;
        void accept() const;
    };

    class Identifier: public Ast {
        private:
        tokt tok;
        std::string id;
        public:
        Identifier(std::string &id, tokt &_tok)
            :id(id), tok(_tok) {}

        std::string value() const;
        tokt token() const;
        void accept() const;
    };


    class BlockStatement: public Ast {
        private:
        int lpos;
        std::vector<AstPtr> statm;
        int rpos;
        public:
        BlockStatement(int &_lpos, int &_rpos, std::vector<AstPtr> &_state)
            :lpos(_lpos), rpos(_rpos), statm(_state) {}

        int lParen() const;
        std::vector<AstPtr> statement() const;
        int rParen() const;
        void accept() const;
    };
    
    
    class EnumLitral: public Ast {
        private:
        tokt tok;
        AstPtr var;
        std::vector<std::pair<AstPtr,AstPtr>>u_data;
        public:
        EnumLitral( AstPtr &_var,  std::vector<std::pair<AstPtr,
                    AstPtr>>&_u_data, tokt &_tok)
            :var(_var), u_data(_u_data), tok(_tok) {}

        std::vector<std::pair<AstPtr,AstPtr>> value() const;
        AstPtr varname() const;
        tokt token() const;
        void accept() const;
    };

    class IntType: public Ast {
        private:
        tokt tok;
        public:
        IntType(tokt &_tok)
        : tok(_tok) {}
        tokt token() const;
        void accept() const;
    };

    class StringType: public Ast {
        private:
        tokt tok;
        public:
        StringType(tokt &_tok)
        : tok(_tok) {}
        tokt token() const;
        void accept() const;
    };

    
    class FloatType: public Ast {
        private:
        tokt tok;
        public:
        FloatType(tokt &_tok)
        : tok(_tok) {}
        tokt token() const;
        void accept() const;
    };

    class BoolType: public Ast {
        private:
        tokt tok;
        public:
        BoolType(tokt &_tok)
        : tok(_tok) {}
        tokt token() const;
        void accept() const;
    };

    class TypeState: public Ast {
        private:
        tokt tok;
        AstPtr dest;
        AstPtr src;
        public:
        TypeState(tokt &_tok, AstPtr &_dest, AstPtr &_src)
        : tok(_tok), dest(_dest), src(_src) {}

        tokt token() const;
        AstPtr destination() const;
        AstPtr source() const;
        void accept() const;
    };

    class ConstExpr: public Ast {
        private:
        tokt tok;
        AstPtr varname;
        AstPtr type;
        AstPtr val;
        public:
        ConstExpr(tokt &_tok, AstPtr &_var, AstPtr &_type, AstPtr &_val)
        : tok(_tok), varname(_var), type(_type), val(_val) {}

        tokt token() const;
        AstPtr vname() const;
        AstPtr vartype() const;
        AstPtr value() const;
        void accept() const;
    };

    class ArrayType: public Ast {
        private:
        tokt tok;
        AstPtr size;
        AstPtr type;
        public:
        ArrayType(tokt &_tok, AstPtr &_size, AstPtr &_type)
        : tok(_tok), size(_size), type(type) {}

        tokt token() const;
        AstPtr arraysize() const;
        AstPtr arraytype() const;
        void accept() const;
    };

    class ComposeExpr: public Ast{
        private:
        tokt tok;
        AstPtr expr;
        AstPtr field;
        public:
        ComposeExpr(tokt &_tok, AstPtr &_expr, AstPtr &_field) 
        : tok(_tok), expr(_expr), field(_field) {}

        tokt token() const;
        AstPtr exr() const;
        AstPtr field() const;
        void accept() const;
    };


    class BineryOp: public Ast {
        private:
        tokt tok;
        AstPtr left;
        tokt op;
        AstPtr right;
        public:
        BineryOp(tokt &_tok, AstPtr &_left, tokt &_op, AstPtr &_right)
        :tok(_tok), left(_left), op(_op), right(_right) {}

        tokt token() const;
        AstPtr rightOpr() const;
        tokt oprator() const;
        AstPtr leftOpr() const;
        void accept() const;
    };

    // class ImportState: public {
    //     private:

    //     public:
    // };

    class UnaryOp: public Ast {
        private:
        tokt tok;
        AstPtr var;
        public:
        UnaryOp(tokt &_tok, AstPtr &_var)
        : tok(_tok), var(_var) {}

        tokt token() const;
        AstPtr variable() const;
        void accept() const;
    };


    class ForLoopState: public Ast{
        private:
        AstPtr h1;
        AstPtr h2;
        AstPtr h3;
        AstPtr loopbody;
        tokt tok;
        public:
        ForLoopState(AstPtr &_h1, AstPtr &_h2,
                     AstPtr &_h3, AstPtr &_loopbody, tokt &_tok)
            :h1(_h1),  h2(_h2), h3(_h3),
                         loopbody(_loopbody), tok(_tok) {}

        AstPtr variable() const;
        AstPtr loopCondition() const;
        AstPtr loopExpression() const;
        AstPtr loopBody() const;
        tokt token() const;
        void accept() const;

    };


    class IfStatement: public Ast{
        private:
        AstPtr condition;
        AstPtr ifbody;
        AstPtr elsebody;
        tokt tok;
        public:
        IfStatement(AstPtr &_condition , AstPtr &_ifbody,
                             AstPtr &_elsebody, tokt &_tok)
        : condition(_condition), ifbody(_ifbody), 
                        elsebody(_elsebody), tok(_tok) {}
        
        AstPtr condition() const;
        AstPtr ifbody() const;
        AstPtr elsebody() const;
        tokt token() const;
        void accept() const;
    };

     class PointerExpr: public Ast {
        private:
        tokt tok;
        AstPtr typePtr;
        public:
        PointerExpr(tokt &tok, AstPtr &_type)
        : tok(tok), typePtr(_type) {}

        tokt token() const;
        AstPtr type() const;
        void accept() const;
    };

    class RefExpr: public Ast {
        private:
        tokt tok;
        AstPtr refType;
        public:
        RefExpr(tokt &_tok, AstPtr &ref)
        : tok(_tok), refType(ref) {}

        tokt token() const;
        AstPtr reftype() const;
        void accept() const;
    };



    class BranchState: public Ast {
        private:
        tokt tok;
        public:
        BranchState(tokt &_tok)
        : tok(_tok) {}

        tokt token() const;
        void accept() const;
    };


     class MemberExpr: public Ast {
        private:
        tokt tok;
        AstPtr right;
        Token_type mem_op;
        AstPtr left;
        public:
        MemberExpr(tokt &_tok, AstPtr &_left, Token_type &_mem_op, AstPtr &_right) 
        : tok(_tok), mem_op(_mem_op), left(_left) ,right(_right) {}

        tokt token() const;
        AstPtr rightid() const;
        Token_type mem_operator() const;
        AstPtr leftid() const;
        void accept() const;
    };

    class StructState: public Ast {
        private:
        tokt tok;
        AstPtr elemt;
        public:
        StructState(tokt &_tok, AstPtr &_mem)
        : tok(_tok), elemt(_mem) {}

        tokt token() const;
        AstPtr element() const;
        void accept() const;
    };

    class FeildList:public Ast {
        private:
        int lpos;
        std::vector<AstPtr>list;
        int rpos;
        public:
        FeildList(int &_lpos, std::vector<AstPtr> &_list, int &_rpos)
        :lpos(_lpos), list(_list), rpos(_rpos) {}

        int lposition() const;
        std::vector<AstPtr> listof() const;
        int rposition() const;
        void accept() const;
    };

    class AssignmentState: public Ast {
        private:
        tokt tok;
        AstPtr left;
        tokt op;
        AstPtr right;
        public:
        AssignmentState(tokt &_tok, AstPtr &_left, tokt &_assop, AstPtr &_right)
        : tok(_tok), left(_left), op(_assop), right(_right) {}
        tokt token() const;
        AstPtr leftVar() const;
        tokt opreator() const;
        AstPtr rightVal() const;
        void accept() const;
    };

    class VariableState: public Ast {
        private:
        tokt tok;
        AstPtr name;
        AstPtr type;
        public:
        VariableState(tokt &_tok, AstPtr &_var, AstPtr &_type)
        : tok(_tok), name(_var), type(_type) {}

        tokt token() const;
        AstPtr varname() const;
        AstPtr vartype() const;
        void accept() const;
    };


    class Param: public Ast{
        private:
        tokt tok;
        AstPtr iden;
        AstPtr type;
        public:
        Param(tokt &_tok, AstPtr &_iden, AstPtr &_type)
        : tok(_tok), iden(_iden), type(_type) {}
        
        tokt token() const;
        AstPtr Piden() const;
        AstPtr Ptype() const;
        void accept() const;
    };

    class FunctionDef: public Ast {
        private:
        tokt tok;
        AstPtr name;
        AstPtr parameter;
        AstPtr returntype;
        AstPtr funcbody;
        public:
        FunctionDef(tokt &_tok, AstPtr &_name, AstPtr &_parameter,
                                AstPtr  _retype, AstPtr &_uncbody)
         : tok(_tok), name(_name), parameter(_parameter),
                         returntype(_retype), funcbody(funcbody) {}

        tokt token() const;
        AstPtr funcname() const;
        AstPtr paramVal() const;
        AstPtr retType() const;
        AstPtr functionBody() const;
        void accept() const;
    };

    class ReturnState: public Ast {
        private:
        tokt tok;
        AstPtr val;
        public:
        ReturnState(tokt &_tok, AstPtr &_val)
        : tok(_tok), val(_val) {}

        tokt token();
        AstPtr value();
        void accept() const;
    };

    class FunctionCall: public Ast {
        private:
        tokt tok;
        AstPtr name;
        AstPtr args;
        public:
        FunctionCall(tokt &_tok, AstPtr &_name, AstPtr &_args)
        : tok(_tok), name(_name), args(_args) {}

        tokt token() const;
        AstPtr funcname() const;
        AstPtr arg() const;
        void accept() const;
    };

}
#endif