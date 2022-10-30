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

    };

    class StringLitral: public Ast {
        
    };

    class FloatLitral: public Ast {
        
    };

    class Expression: public Ast {
        private:
    };
    
    class BlockStatement: public Ast {

    };
    
    class ForLoopState: public Ast{

    };

    class WhileLoopState: public Ast{

    };

    class IfStatement: public Ast{
        private:
        AstPtr condition;
        AstPtr ifbody;
        AstPtr elsebody;
        AstPtr elifbody;
        public:
        IfStatement(AstPtr Ifbody, AstPtr Elsebody, AstPtr Elifbody)
            : ifbody(Ifbody),elsebody(Elsebody),elifbody(Elifbody) {}
        
        lex::Token_type token() const;

        void accept() const;
    };

}
#endif