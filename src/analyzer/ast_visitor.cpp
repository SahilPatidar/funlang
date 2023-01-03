#include<iostream>
#include"../../include/parser/Ast.hpp"
#include"../../include/analyzer/ast_visitor.hpp"
namespace ast{

void Program::accept(AstVisitor &visitor) const {
    if(!visitor.visit(*this)){
        //for()
    }
}

void BlockStatement::accept(AstVisitor &visitor) const {
    if(!visitor.visit(*this)){
        //for()
    }
}

void ForLoopState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void FunctionDef::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void ConstState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void BranchState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void StructState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void InState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void ReturnState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void IfStatement::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void LetState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void FreeState::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}




void BoolLiteral::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void NumericLiteral::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void NullLiteral::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void StringLiteral::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void FloatLiteral::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}


void BineryExper::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void AssignmentExpr::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void PostfixExper::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void PrefixExper::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void PointerType::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void ListExpr::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void FunctionCall::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void MemberExpr::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}
  
void IndexExpr::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void Parameter::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}
  


void ArrayType::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void IntType::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void BoolType::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void FloatType::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}

void StringType::accept(AstVisitor &visitor) const {
    visitor.visit(*this);
}


}