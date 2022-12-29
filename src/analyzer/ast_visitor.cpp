#include<iostream>
#include"../../include/parser/Ast.hpp"
#include"../../include/analyzer/ast_visitor.hpp"
namespace ast{

void Program::accept(AstVisitor &visitor) const {
    if(!visitor.valid(*this)){
        //for()
    }
}

void BlockStatement::accept(AstVisitor &visitor) const {
    if(!visitor.valid(*this)){
        //for()
    }
}

void ForLoopState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void FunctionDef::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void ConstState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void BranchState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void StructState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void InState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void ReturnState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void IfStatement::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void LetState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void FreeState::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}




void BoolLitral::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void NumericLitral::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void NullLitral::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void StringLitral::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void FloatLitral::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}


void BineryExper::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void AssignmentExpr::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void PostfixExper::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void PrefixExper::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void PointerType::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void ListExpr::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void FunctionCall::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void MemberExpr::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}
  
void IndexExpr::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void Parameter::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}
  


void ArrayType::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void IntType::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void BoolType::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void FloatType::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}

void StringType::accept(AstVisitor &visitor) const {
    visitor.valid(*this);
}






}