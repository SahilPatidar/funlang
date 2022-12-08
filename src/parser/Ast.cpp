
#include"../../include/parser/Ast.hpp"

namespace ast {

    tokt Program::token() const {
        return tok;
    }

    std::vector<AstPtr> Program::statements() const{
        return statement;
    }

    tokt IntergerLitral::token() const {
        return tok;
    }
    
    std::string IntergerLitral::value() const {
        return Int;
    }

    tokt StringLitral::token() const {
        return tok;
    }

    std::string StringLitral::value() const {
        return str;
    }

    bool StringLitral::ischar() const {
        return chr;
    }

    tokt BoolLitral::token() const {
        return tok;
    }
    
    std::string BoolLitral::value() const {
        return val;
    }

    tokt FloatLitral::token() const {
        return tok;
    }

    std::string FloatLitral::value() const {
        return flt;
    }

    tokt Identifier::token() const {
        return tok;
    }

    std::string Identifier::value() const {
        return id;
    }

    int BlockStatement::lParen() const {
        return lpos;
    }

    int BlockStatement::rParen() const {
        return rpos;
    }

    std::vector<AstPtr> BlockStatement::statement() const {
        return statm;
    }

    tokt EnumLitral::token() const {
        return tok;
    }

    tokt BineryOp::token() const {
        return tok;
    }

    AstPtr BineryOp::leftOpr() const {
        return left;
    }

    tokt BineryOp::oprator() const {
        return op;
    }

    AstPtr BineryOp::rightOpr() const {
        return right;
    }

    tokt ForLoopState::token() const {
        return tok;
    }

    AstPtr ForLoopState::variable() const {
        return h1;
    }

    AstPtr ForLoopState::loopCondition() const {
        return h2;
    }

    AstPtr ForLoopState::loopExpression() const {
        return h3;
    }

    AstPtr ForLoopState::loopBody() const {
        return loopbody;
    }

    tokt IntType::token() const {
        return tok;
    }

    tokt StringType::token() const {
        return tok;
    }

    tokt BoolType::token() const {
        return tok;
    }

    tokt FloatType::token() const {
        return tok;
    }

    tokt ConstExpr::token() const {
        return tok;
    }

    AstPtr ConstExpr::vname() const {
        return varname;
    }

    AstPtr ConstExpr::vartype() const {
        return type;
    }

    AstPtr ConstExpr::value() const {
        return val;
    }
    
}

