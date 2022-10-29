#ifndef AST_H
#define AST_H

#include<iostream>
#include<memory>

namespace ast{
    class Ast{
        public:
        virtual ~Ast() = default;
    };

    using AstPtr = std::shared_ptr<Ast>;

    class IfStatement: public Ast{
        private:
        AstPtr condition;
        AstPtr ifbody;
        AstPtr elsebody;
        AstPtr elifbody;
        public:
        IfStatement(AstPtr Ifbody, AstPtr Elsebody, AstPtr Elifbody)
            : ifbody(Ifbody),elsebody(Elsebody),elifbody(Elifbody) {}
        
        void accept() const;
    };

}
#endif