
#include"../../include/parser/Ast.hpp"

namespace ast {

    tokt Program::token() const {
        return tok;
    }

    std::vector<AstPtr> Program::statements() const{
        return statement;
    }


    tokt BlockStatement::token() const {
        return tok;
    }

    std::vector<AstPtr> BlockStatement::statements() const{
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

    tokt BlockStatement::token() const {
        return tok;
    }

    std::vector<AstPtr> BlockStatement::statements() const {
        return statement;
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
    
    tokt WhileLoopState::token() const {
        return tok;
    }

    AstPtr WhileLoopState::expression() const {
        return expr;
    }

    AstPtr WhileLoopState::loopBody() const {
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

