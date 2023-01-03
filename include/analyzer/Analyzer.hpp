#pragma once

#include<iostream>
#include"ast_visitor.hpp"
namespace analyzer{
using namespace ast;
class Analyzer: public AstVisitor {
    private:
    bool visit(const Program& astnode);
    bool visit(const BlockStatement& astnode );
    bool visit(const FunctionDef& astnode );
    bool visit(const ForLoopState& astnode );
    bool visit(const StructState& astnode );
    bool visit(const BranchState& astnode );
    bool visit(const ConstState& astnode );
    bool visit(const FreeState& astnode );
    bool visit(const LetState& astnode );
    bool visit(const IfStatement& astnode );
    bool visit(const ReturnState& astnode );
    bool visit(const InState& astnode );
    
    bool visit(const BineryExper& astnode );
    bool visit(const AssignmentExpr& astnode );
    bool visit(const ListExpr& astnode ) ;
    bool visit(const FunctionCall& astnode );
    bool visit(const MemberExpr& astnode );
    bool visit(const IndexExpr& astnode );
    bool visit(const PostfixExper& astnode );
    bool visit(const PrefixExper& astnode );
    bool visit(const Parameter& astnode );

    bool visit(const PointerType& astnode );
    bool visit(const ArrayType& astnode ) ;
    bool visit(const FloatType& astnode );
    bool visit(const StringType& astnode );
    bool visit(const Identifier& astnode );
    bool visit(const IntType& astnode );
    bool visit(const BoolType& astnode );


    bool visit(const FloatLitral& astnode );
    bool visit(const BoolLitral& astnode );
    bool visit(const NumericLitral& astnode );
    bool visit(const NullLitral& astnode );
    bool visit(const StringLitral& astnode );

// bool visit(const TypeState& astnode );
// bool visit(const EnumLitral& astnode );
// bool visit(const NewState& astnode );
// bool visit(const FreeState& astnode );
};

}