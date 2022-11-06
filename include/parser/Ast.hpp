#ifndef AST_H
#define AST_H

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"

using tok_t = lex::Token_type;
namespace ast{
    
    class Ast{
        public:
        virtual ~Ast() = default;
    };
   
    using AstPtr = std::shared_ptr<Ast>;

    class IntergerLitral: public Ast {
        private:
        tok_t tok;
        std::string Int;
        public:
        IntergerLitral(std::string &_int, tok_t &_tok)
        : Int(_int), tok(_tok) {}

        std::string value() const;
        tok_t token() const;
        void accept() const;
    };

    class BoolLitral: public Ast {
        private:
        std::string val;
        tok_t tok;
        public:
        BoolLitral(std::string &_val, tok_t &_tok)
        : val(_val), tok(_tok) {}

        std::string value() const;
        tok_t token() const;
        void accept() const;
    };

    class StringLitral: public Ast {
        private:
        std::string _str;
        tok_t _token;
        bool _char;
        public:
        StringLitral(std::string &str, bool chr)
        :_str(str), _char(chr) {}

        std::string value() const;
        tok_t token() const;
        void accept() const;
    };

    class FloatLitral: public Ast {
        private:
        std::string flt;
        tok_t token;
        public:
        FloatLitral(std::string &_flt, tok_t &_tok)
            : flt(_flt), token(_tok) {}

        std::string value() const;
        tok_t token() const;
        void accept() const;
    };

    class Identifier: public Ast {
        private:
        tok_t token;
        std::string id;
        public:
        Identifier(std::string &id, tok_t &tok)
            :id(id), token(tok) {}

        std::string value() const;
        tok_t token() const;
        void accept() const;
    };


    class BlockStatement: public Ast {
        private:
        tok_t _token;
        std::vector<AstPtr> _val;
        public:
        BlockStatement(tok_t &tok, std::vector<AstPtr> &val)
            :_token(tok), _val(val) {}

        std::vector<AstPtr> value() const;
        tok_t token() const;
        void accept() const;
    };
    
    
    class EnumState: public Ast {
        private:
        tok_t token;
        AstPtr var;
        std::vector<std::pair<AstPtr,AstPtr>>u_data;
        public:
        EnumState( AstPtr &_var,  std::vector<std::pair<AstPtr,
                    AstPtr>>&_u_data, tok_t &_tok)
            :var(_var), u_data(_u_data), token(_tok) {}

        std::vector<std::pair<AstPtr,AstPtr>> value() const;
        AstPtr varname() const;
        tok_t token() const;
        void accept() const;
    };

    class IntType: public Ast {
        private:
        tok_t tok;
        public:
        IntType(tok_t &_tok)
        : tok(_tok) {}
        tok_t token() const;
        void accept() const;
    };

    class StringType: public Ast {
        private:
        tok_t tok;
        public:
        StringType(tok_t &_tok)
        : tok(_tok) {}
        tok_t token() const;
        void accept() const;
    };

    
    class FloatType: public Ast {
        private:
        tok_t tok;
        public:
        FloatType(tok_t &_tok)
        : tok(_tok) {}
        tok_t token() const;
        void accept() const;
    };

    class ArrayDec: public Ast {
        private:
        tok_t tok;
        AstPtr var;
        AstPtr type;
        public:
        ArrayDec(tok_t &_tok, AstPtr &_var, AstPtr &_type)
        : tok(_tok), var(_var), type(type) {}

        tok_t token() const;
        AstPtr arrayname() const;
        AstPtr arraytype() const;
        void accept() const;
    };

    class ArrayLitral: public Ast {
        private:
        tok_t tok;
        std::vector<AstPtr> val;
        public:
        ArrayLitral(tok_t &_tok, std::vector<AstPtr>&_val)
        : tok(_tok), val(_val) {}

        tok_t token() const;
        std::vector<AstPtr> values() const;
        void accept() const;
    };

    class BineryOp: public Ast {
        private:
        tok_t tok;
        AstPtr right;
        tok_t op;
        AstPtr left;
        public:
        BineryOp(tok_t &_tok, AstPtr &_right, tok_t &_op, AstPtr &_left)
        :tok(_tok), right(_right), op(_op), left(_left) {}

        tok_t token() const;
        AstPtr rightOp() const;
        tok_t oprator() const;
        AstPtr leftOp() const;
        void accept() const;
    };

    // class UneryOp: public Ast {
    //     private:
    //     tok_t tok;
    //     AstPtr var;

    // };

    class ForLoopState: public Ast{
        private:
        std::vector<AstPtr> variable;
        AstPtr condition;
        AstPtr expression;
        AstPtr loopbody;
        tok_t token;
        public:
        ForLoopState(std::vector<AstPtr>&_variable,
                     AstPtr &_expression, AstPtr &_loopbody, tok_t &_tok)
            :variable(_variable),  expression(_expression),
                         loopbody(_loopbody), token(_tok) {}

        std::vector<AstPtr> variable() const;
        AstPtr condition() const;
        AstPtr expression() const;
        AstPtr loopbody() const;
        tok_t token() const;
        void accept() const;

    };

    class WhileLoopState: public Ast{
        private:
        AstPtr expression;
        AstPtr loopbody;
        tok_t token;
        public:
        WhileLoopState(AstPtr &_expression, AstPtr &_loopbody, tok_t &_tok)
            : expression(_expression), loopbody(_loopbody), token(_tok) {}

        AstPtr expression() const;
        AstPtr loopbody() const;        
        tok_t token() const;
        void accept() const;
    };

    class IfStatement: public Ast{
        private:
        AstPtr condition;
        AstPtr ifbody;
        AstPtr elsebody;
        AstPtr elifbody;
        tok_t token;
        public:
        IfStatement(AstPtr &_condition , AstPtr &_ifbody, AstPtr &_elsebody,
                     AstPtr &_elifbody, tok_t &_tok)
        : condition(_condition), ifbody(_ifbody), elsebody(_elsebody), elifbody(_elifbody), token(_tok) {}
        
        AstPtr condition() const;
        AstPtr ifbody() const;
        AstPtr elsebody() const;
        AstPtr elifbody() const;
        tok_t token() const;
        void accept() const;
    };

     class PointerType: public Ast {
        private:
        tok_t token;
        AstPtr typePtr;
        public:
        PointerType(tok_t &tok, AstPtr &_type)
        : token(tok), typePtr(_type) {}

        tok_t tok() const;
        AstPtr type() const;
        void accept() const;
    };

    class RefType: public Ast {
        private:
        tok_t token;
        AstPtr refType;
        public:
        RefType(tok_t &tok, AstPtr &ref)
        : token(tok), refType(ref) {}

        tok_t tok() const;
        AstPtr reftype() const;
        void accept() const;
    };

    class VariableState: public Ast {
        private:
        tok_t tok;
        AstPtr name;
        AstPtr type;
        AstPtr val;
        public:
        VariableState(tok_t &_tok, AstPtr &_var, AstPtr &_type, AstPtr &_val)
        : tok(_tok), name(_var), type(_type), val(_val) {}

        tok_t token() const;
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
        tok_t token;
        std::vector<param>parameter;
        AstPtr returntype;
        AstPtr funcbody;
        public:
        FunctionDef(tok_t &_tok, std::vector<param>&_parameter, AstPtr _retype, AstPtr &_uncbody)
        : token(_tok), parameter(_parameter), returntype(_retype), funcbody(funcbody) {}

        tok_t token() const;
        std::vector<param> paramVal() const;
        AstPtr retType() const;
        AstPtr functionBody() const;
        void accept() const;
    };

    class FunctionCall: public Ast {
        private:
        tok_t token;
        AstPtr name;
        std::vector<AstPtr> args;
        public:
        FunctionCall(tok_t &_tok, std::vector<AstPtr>&_args)
        : token(_tok), args(_args) {}

        tok_t tok() const;
        std::vector<AstPtr> arg() const;
        void accept() const;
    };

}
#endif