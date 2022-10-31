#ifndef AST_H
#define AST_H

#include<iostream>
#include<vector>
#include<memory>
#include"../lex/lex.hpp"

namespace ast{
    
    class Ast{
        public:
        virtual ~Ast() = default;
    };
   
    using AstPtr = std::shared_ptr<Ast>;

    class IntergerLitral: public Ast {
        private:
        lex::Token_type _token;
        std::string _int;
        public:
        IntergerLitral(std::string &Int)
        :_int(Int) {}

        std::string value() const;
        lex::Token_type token() const;
        void accept() const;
    };

    class StringLitral: public Ast {
        private:
        std::string _str;
        lex::Token_type _token;
        bool _char;
        public:
        StringLitral(std::string &str, bool chr)
        :_str(str), _char(chr) {}

        std::string value() const;
        lex::Token_type token() const;
        void accept() const;
    };

    class FloatLitral: public Ast {
        private:
        std::string _float;
        lex::Token_type _token;
        public:
        FloatLitral(std::string &flt, lex::Token_type &tok)
            :_float(flt), _token(tok) {}

        std::string value() const;
        lex::Token_type token() const;
        void accept() const;
    };

    class Identifier: public Ast {
        private:
        lex::Token_type _token;
        std::string _id;
        public:
        Identifier(std::string &id, lex::Token_type &tok)
            :_id(id), _token(tok) {}

        std::string value() const;
        lex::Token_type token() const;
        void accept() const;
    };


    
    class BlockStatement: public Ast {

    };
    
    


    class EnumState: public Ast {
        private:
        lex::Token_type _token;
        std::vector<AstPtr> _u_data;
        public:
        EnumState(std::vector<AstPtr>&u_data, lex::Token_type &tok)
            :_u_data(u_data), _token(tok) {}

        std::vector<AstPtr> value() const;
        lex::Token_type token() const;
        void accept() const;
    };

    class ForLoopState: public Ast{
        private:
        std::vector<AstPtr> _variable;
        AstPtr _condition;
        AstPtr _expression;
        AstPtr _loopbody;
        lex::Token_type _token;
        public:
        ForLoopState(std::vector<AstPtr>&variable, AstPtr &expression, AstPtr &loopbody, lex::Token_type &tok)
            :_variable(variable),  _expression(expression), _loopbody(loopbody), _token(tok) {}

        lex::Token_type token() const;
        void accept() const;

    };

    class WhileLoopState: public Ast{
        private:
        AstPtr _expression;
        AstPtr _loopbody;
        lex::Token_type _token;
        public:
        WhileLoopState(AstPtr &expression, AstPtr &loopbody, lex::Token_type &tok)
            : _expression(expression), _loopbody(loopbody), _token(tok) {}

        lex::Token_type token() const;
        void accept();
    };

    class IfStatement: public Ast{
        private:
        AstPtr _condition;
        AstPtr _ifbody;
        AstPtr _elsebody;
        AstPtr _elifbody;
        lex::Token_type _token;
        public:
        IfStatement(AstPtr &condition , AstPtr &ifbody, AstPtr &elsebody, AstPtr &elifbody, lex::Token_type &tok)
            :_condition(condition), _ifbody(ifbody),_elsebody(elsebody),_elifbody(elifbody), _token(tok) {}
        

        lex::Token_type token() const;
        void accept();
    };

}
#endif