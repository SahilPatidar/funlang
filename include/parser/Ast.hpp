#ifndef AST_H
#define AST_H

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"

using Token = lex::Token_type;
namespace ast{
    
    class Ast{
        public:
        virtual ~Ast() = default;
    };
   
    using AstPtr = std::shared_ptr<Ast>;

    class Program: public Ast {
        private:
        Token tok;
        std::vector<AstPtr> statement;
        public:
        Program(Token &_tok, std::vector<AstPtr>&_state) 
        :tok(_tok), statement(_state) {}

        Token token() const;
        std::vector<AstPtr> statements() const;
        void accept() const;
    };

    class IntergerLitral: public Ast {
        private:
        Token tok;
        std::string Int;
        public:
        IntergerLitral(std::string &_int, Token &_tok)
        : Int(_int), tok(_tok) {}

        std::string value() const;
        Token token() const;
        void accept() const;
    };

    class BoolLitral: public Ast {
        private:
        std::string val;
        Token tok;
        public:
        BoolLitral(std::string &_val, Token &_tok)
        : val(_val), tok(_tok) {}

        std::string value() const;
        Token token() const;
        void accept() const;
    };

    class StringLitral: public Ast {
        private:
        std::string str;
        Token tok;
        bool chr;
        public:
        StringLitral(Token &_tok, std::string &_str, bool _chr)
        : tok(_tok), str(_str), chr(_chr) {}

        std::string value() const;
        Token token() const;
        bool ischar() const;
        void accept() const;
    };

    class NoLiteral: public AstPtr {
        public:
        NoLiteral() = default;
        Token token() const;
        void accept() const;
    };

    class NullLitral: public AstPtr {
        private:
        Token tok;
        public:
        NullLitral(Token &_tok)
        : tok(_tok) {}

        Token token() const;
        void accept() const;
    };

    class FloatLitral: public Ast {
        private:
        std::string flt;
        Token tok;
        public:
        FloatLitral(std::string &_flt, Token &_tok)
            : flt(_flt), tok(_tok) {}

        std::string value() const;
        Token token() const;
        void accept() const;
    };

    class Identifier: public Ast {
        private:
        Token tok;
        std::string id;
        public:
        Identifier(std::string &id, Token &_tok)
            :id(id), tok(_tok) {}

        std::string value() const;
        Token token() const;
        void accept() const;
    };


    class BlockStatement: public Ast {
        private:
        Token tok;
        std::vector<AstPtr> statement;
        public:
        BlockStatement(Token &_tok, std::vector<AstPtr> &_state)
            :tok(_tok), statement(_state) {}

        std::vector<AstPtr> statements() const;
        Token token() const;
        void accept() const;
    };
    
    
    class EnumLitral: public Ast {
        private:
        Token tok;
        AstPtr var;
        std::vector<std::pair<AstPtr,AstPtr>>u_data;
        public:
        EnumLitral( AstPtr &_var,  std::vector<std::pair<AstPtr,
                    AstPtr>>&_u_data, Token &_tok)
            :var(_var), u_data(_u_data), tok(_tok) {}

        std::vector<std::pair<AstPtr,AstPtr>> value() const;
        AstPtr varname() const;
        Token token() const;
        void accept() const;
    };

    class IntType: public Ast {
        private:
        Token tok;
        public:
        IntType(Token &_tok)
        : tok(_tok) {}
        Token token() const;
        void accept() const;
    };

    class StringType: public Ast {
        private:
        Token tok;
        public:
        StringType(Token &_tok)
        : tok(_tok) {}
        Token token() const;
        void accept() const;
    };

    
    class FloatType: public Ast {
        private:
        Token tok;
        public:
        FloatType(Token &_tok)
        : tok(_tok) {}
        Token token() const;
        void accept() const;
    };

    class BoolType: public Ast {
        private:
        Token tok;
        public:
        BoolType(Token &_tok)
        : tok(_tok) {}
        Token token() const;
        void accept() const;
    };

    class ConstExpr: public Ast {
        private:
        Token tok;
        AstPtr varname;
        AstPtr type;
        AstPtr val;
        public:
        ConstExpr(Token &_tok, AstPtr &_var, AstPtr &_type, AstPtr &_val)
        : tok(_tok), varname(_var), type(_type), val(_val) {}

        Token token() const;
        AstPtr vname() const;
        AstPtr vartype() const;
        AstPtr value() const;
        void accept() const;
    };

    class ArrayTypeExpr: public Ast {
        private:
        Token tok;
        AstPtr size;
        AstPtr type;
        public:
        ArrayTypeExpr(Token &_tok, AstPtr &_size, AstPtr &_type)
        : tok(_tok), size(_size), type(type) {}

        Token token() const;
        AstPtr arraysize() const;
        AstPtr arraytype() const;
        void accept() const;
    };

    class ArrayLitral: public Ast {
        private:
        Token tok;
        std::vector<AstPtr> val;
        public:
        ArrayLitral(Token &_tok, std::vector<AstPtr>&_val)
        : tok(_tok), val(_val) {}

        Token token() const;
        std::vector<AstPtr> values() const;
        void accept() const;
    };

    class ArrayExpr: public Ast {
        private:
        Token tok;
        AstPtr arr;
        std::vector<AstPtr> index;
        public:
        ArrayExpr(Token &_tok, AstPtr &_arr, std::vector<AstPtr> &_index)
        : tok(_tok), arr(_arr), index(_index) {}

        Token token() const;
        AstPtr array() const;
        std::vector<AstPtr> arrayindex() const;
        void accept() const;
    };

    class BineryOp: public Ast {
        private:
        Token tok;
        AstPtr right;
        Token op;
        AstPtr left;
        public:
        BineryOp(Token &_tok, AstPtr &_right, Token &_op, AstPtr &_left)
        :tok(_tok), right(_right), op(_op), left(_left) {}

        Token token() const;
        AstPtr rightOpr() const;
        Token oprator() const;
        AstPtr leftOpr() const;
        void accept() const;
    };

    // class ImportState: public {
    //     private:

    //     public:
    // };

    class ForLoopState: public Ast{
        private:
        std::vector<AstPtr> var;
        AstPtr condition;
        AstPtr expression;
        AstPtr loopbody;
        Token tok;
        public:
        ForLoopState(std::vector<AstPtr>&_var, AstPtr &_condition,
                     AstPtr &_expression, AstPtr &_loopbody, Token &_tok)
            :var(_var),  expression(_expression), condition(_condition),
                         loopbody(_loopbody), tok(_tok) {}

        std::vector<AstPtr> variable() const;
        AstPtr loopCondition() const;
        AstPtr loopExpression() const;
        AstPtr loopBody() const;
        Token token() const;
        void accept() const;

    };

    class WhileLoopState: public Ast{
        private:
        AstPtr expr;
        AstPtr loopbody;
        Token tok;
        public:
        WhileLoopState(AstPtr &_expr, AstPtr &_loopbody, Token &_tok)
            : expr(_expr), loopbody(_loopbody), tok(_tok) {}

        AstPtr expression() const;
        AstPtr loopBody() const;        
        Token token() const;
        void accept() const;
    };

    class IfStatement: public Ast{
        private:
        AstPtr condition;
        AstPtr ifbody;
        AstPtr elsebody;
        AstPtr elifbody;
        Token token;
        public:
        IfStatement(AstPtr &_condition , AstPtr &_ifbody, AstPtr &_elsebody,
                     AstPtr &_elifbody, Token &_tok)
        : condition(_condition), ifbody(_ifbody), elsebody(_elsebody), elifbody(_elifbody), token(_tok) {}
        
        AstPtr condition() const;
        AstPtr ifbody() const;
        AstPtr elsebody() const;
        AstPtr elifbody() const;
        Token token() const;
        void accept() const;
    };

     class PointerExpr: public Ast {
        private:
        Token token;
        AstPtr typePtr;
        public:
        PointerExpr(Token &tok, AstPtr &_type)
        : token(tok), typePtr(_type) {}

        Token tok() const;
        AstPtr type() const;
        void accept() const;
    };

    class RefExpr: public Ast {
        private:
        Token token;
        AstPtr refType;
        public:
        RefExpr(Token &tok, AstPtr &ref)
        : token(tok), refType(ref) {}

        Token tok() const;
        AstPtr reftype() const;
        void accept() const;
    };

    class BreakState: public Ast {
        private:
        Token tok;
        public:
        BreakState(Token &_tok)
        : tok(_tok) {}

        Token token() const;
        void accept() const;
    };

    class ContinueState: public Ast {
        private:
        Token tok;
        public:
        ContinueState(Token &_tok)
        : tok(_tok) {}

        Token token() const;
        void accept() const;
    };

    class ArrowExpr: public Ast {
        private:
        Token tok;
        AstPtr right;
        AstPtr left;
        public:
        ArrowExpr(Token &_tok, AstPtr &_right, AstPtr &_left) 
        : tok(_tok), right(_right), left(_left) {}

        Token token() const;
        AstPtr rightid() const;
        AstPtr leftid() const;
        void accept() const;
    };

     class DotExpr: public Ast {
        private:
        Token tok;
        AstPtr right;
        AstPtr left;
        public:
        DotExpr(Token &_tok, AstPtr &_right, AstPtr &_left) 
        : tok(_tok), right(_right), left(_left) {}

        Token token() const;
        AstPtr rightid() const;
        AstPtr leftid() const;
        void accept() const;
    };

    class VariableState: public Ast {
        private:
        Token tok;
        AstPtr name;
        AstPtr type;
        AstPtr val;
        public:
        VariableState(Token &_tok, AstPtr &_var, AstPtr &_type, AstPtr &_val)
        : tok(_tok), name(_var), type(_type), val(_val) {}

        Token token() const;
        AstPtr varname() const;
        AstPtr vartype() const;
        AstPtr value() const;
        void accept() const;
    };


    struct param {
        AstPtr var;
        AstPtr type;
        param(AstPtr &_var, AstPtr &_type)
        : var(_var), type(_type)  {}
    };

    class FunctionDef: public Ast {
        private:
        Token token;
        std::vector<param>parameter;
        AstPtr returntype;
        AstPtr funcbody;
        public:
        FunctionDef(Token &_tok, std::vector<param>&_parameter,
                                 AstPtr _retype, AstPtr &_uncbody)
        : token(_tok), parameter(_parameter),
                         returntype(_retype), funcbody(funcbody) {}

        Token token() const;
        std::vector<param> paramVal() const;
        AstPtr retType() const;
        AstPtr functionBody() const;
        void accept() const;
    };

    class FunctionCall: public Ast {
        private:
        Token token;
        AstPtr name;
        std::vector<AstPtr> args;
        public:
        FunctionCall(Token &_tok, std::vector<AstPtr>&_args)
        : token(_tok), args(_args) {}

        Token tok() const;
        std::vector<AstPtr> arg() const;
        void accept() const;
    };

}
#endif