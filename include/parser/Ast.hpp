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
        AstPtr statm;
        int rpos;
        public:
        BlockStatement(int &_lpos, int &_rpos ,AstPtr &_state)
            :lpos(_lpos), rpos(_rpos), statm(_state) {}

        int lParen() const;
        AstPtr statement() const;
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

    

    class ParenExpr: public Ast {
        private:
        int lpos;
        AstPtr expr;
        int rpos;
        ParenExpr(int &_lpos, AstPtr &_expr, int &_rpos)
        : lpos(_lpos), expr(_expr), rpos(_rpos) {}

        int LPos() const;
        AstPtr expression() const;
        int RPos() const;
        void accept() const;  
    };

    // class CompositeExpr: public Ast {
    //     private:
    //     AstPtr type;
    //     AstPtr expr;
    //     int 


    // };

    

    class BineryOp: public Ast {
        private:
        tokt tok;
        AstPtr right;
        tokt op;
        AstPtr left;
        public:
        BineryOp(tokt &_tok, AstPtr &_right, tokt &_op, AstPtr &_left)
        :tok(_tok), right(_right), op(_op), left(_left) {}

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

    class UneryOp: public Ast {
        private:
        tokt tok;
        AstPtr var;
        public:
        UneryOp(tokt &_tok, AstPtr &_var)
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

    

    class ArrowExpr: public Ast {
        private:
        tokt tok;
        AstPtr right;
        AstPtr left;
        public:
        ArrowExpr(tokt &_tok, AstPtr &_right, AstPtr &_left) 
        : tok(_tok), right(_right), left(_left) {}

        tokt token() const;
        AstPtr rightid() const;
        AstPtr leftid() const;
        void accept() const;
    };

     class DotExpr: public Ast {
        private:
        tokt tok;
        AstPtr right;
        AstPtr left;
        public:
        DotExpr(tokt &_tok, AstPtr &_right, AstPtr &_left) 
        : tok(_tok), right(_right), left(_left) {}

        tokt token() const;
        AstPtr rightid() const;
        AstPtr leftid() const;
        void accept() const;
    };

    class FeildList:public Ast {
        private:
        tokt tok;
        std::vector<AstPtr>list;
        public:
        FeildList(tokt &_tok, std::vector<AstPtr> &_list)
        : tok(_tok), list(_list) {}

        tokt token() const;
        std::vector<AstPtr> listof() const;
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