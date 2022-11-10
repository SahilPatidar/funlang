
#include"../../include/parser/Ast.hpp"

namespace ast {

    Token Program::token() const {
        return tok;
    }

    std::vector<AstPtr> Program::statements() const{
        return statement;
    }


    Token BlockStatement::token() const {
        return tok;
    }

    std::vector<AstPtr> BlockStatement::statements() const{
        return statement;
    }

    Token IntergerLitral::token() const {
        return tok;
    }
    
    std::string IntergerLitral::value() const {
        return Int;
    }

    Token StringLitral::token() const {
        return tok;
    }

    std::string StringLitral::value() const {
        return str;
    }

    bool StringLitral::ischar() const {
        return chr;
    }

    Token BoolLitral::token() const {
        return tok;
    }
    
    std::string BoolLitral::value() const {
        return val;
    }

    Token FloatLitral::token() const {
        return tok;
    }

    std::string FloatLitral::value() const {
        return flt;
    }

    Token Identifier::token() const {
        return tok;
    }

    std::string Identifier::value() const {
        return id;
    }

    Token BlockStatement::token() const {
        return tok;
    }

    std::vector<AstPtr> BlockStatement::statements() const {
        return statement;
    }

    Token EnumLitral::token() const {
        return tok;
    }

    Token BineryOp::token() const {
        return tok;
    }

    AstPtr BineryOp::leftOpr() const {
        return left;
    }

    Token BineryOp::oprator() const {
        return op;
    }

    AstPtr BineryOp::rightOpr() const {
        return right;
    }

    Token ForLoopState::token() const {
        return tok;
    }

    std::vector<AstPtr> ForLoopState::variable() const {
        return var;
    }

    AstPtr ForLoopState::loopCondition() const {
        return condition;
    }

    AstPtr ForLoopState::loopExpression() const {
        return expression;
    }

    AstPtr ForLoopState::loopBody() const {
        return loopbody;
    }
    
    Token WhileLoopState::token() const {
        return tok;
    }

    AstPtr WhileLoopState::expression() const {
        return expr;
    }

    AstPtr WhileLoopState::loopBody() const {
        return loopbody;
    }

    Token IntType::token() const {
        return tok;
    }

    Token StringType::token() const {
        return tok;
    }

    Token BoolType::token() const {
        return tok;
    }

    Token FloatType::token() const {
        return tok;
    }

    Token ConstExpr::token() const {
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

