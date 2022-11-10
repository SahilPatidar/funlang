
#include"../../include/parser/Ast.hpp"

namespace ast {

    tok_t Program::token() const {
        return tok;
    }

    std::vector<AstPtr> Program::statements() const{
        return statement;
    }


    tok_t BlockStatement::token() const {
        return tok;
    }

    std::vector<AstPtr> BlockStatement::statements() const{
        return statement;
    }

    tok_t IntergerLitral::token() const {
        return tok;
    }
    
    std::string IntergerLitral::value() const {
        return Int;
    }

    tok_t StringLitral::token() const {
        return tok;
    }

    std::string StringLitral::value() const {
        return str;
    }

    bool StringLitral::ischar() const {
        return chr;
    }

    tok_t BoolLitral::token() const {
        return tok;
    }
    
    std::string BoolLitral::value() const {
        return val;
    }

    tok_t FloatLitral::token() const {
        return tok;
    }

    std::string FloatLitral::value() const {
        return flt;
    }

    tok_t Identifier::token() const {
        return tok;
    }

    std::string Identifier::value() const {
        return id;
    }

    tok_t BlockStatement::token() const {
        return tok;
    }

    std::vector<AstPtr> BlockStatement::statements() const {
        return statement;
    }

    tok_t EnumLitral::token() const {
        return tok;
    }

    tok_t BineryOp::token() const {
        return tok;
    }

    AstPtr BineryOp::leftOpr() const {
        return left;
    }

    tok_t BineryOp::oprator() const {
        return op;
    }

    AstPtr BineryOp::rightOpr() const {
        return right;
    }

    tok_t ForLoopState::token() const {
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
    
    tok_t WhileLoopState::token() const {
        return tok;
    }

    AstPtr WhileLoopState::expression() const {
        return expr;
    }

    AstPtr WhileLoopState::loopBody() const {
        return loopbody;
    }

    tok_t IntType::token() const {
        return tok;
    }

    tok_t StringType::token() const {
        return tok;
    }

    tok_t BoolType::token() const {
        return tok;
    }

    tok_t FloatType::token() const {
        return tok;
    }

    tok_t ConstExpr::token() const {
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

