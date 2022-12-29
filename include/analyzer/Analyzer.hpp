#pragma once

#include<iostream>
#include"ast_visitor.hpp"
namespace analyzer{
using namespace ast;
class Analyzer: public AstVisitor {
    private:
    bool valid(const Program& astnode);
    bool valid(const BlockStatement& astnode );
    bool valid(const FunctionDef& astnode );
    bool valid(const ForLoopState& astnode );
    bool valid(const StructState& astnode );
    bool valid(const BranchState& astnode );
    bool valid(const ConstState& astnode );
    bool valid(const FreeState& astnode );
    bool valid(const LetState& astnode );
    bool valid(const IfStatement& astnode );
    bool valid(const ReturnState& astnode );
    bool valid(const InState& astnode );
    
    bool valid(const BineryExper& astnode );
    bool valid(const AssignmentExpr& astnode );
    bool valid(const ListExpr& astnode ) ;
    bool valid(const FunctionCall& astnode );
    bool valid(const MemberExpr& astnode );
    bool valid(const IndexExpr& astnode );
    bool valid(const PostfixExper& astnode );
    bool valid(const PrefixExper& astnode );
    bool valid(const Parameter& astnode );

    bool valid(const PointerType& astnode );
    bool valid(const ArrayType& astnode ) ;
    bool valid(const FloatType& astnode );
    bool valid(const StringType& astnode );
    bool valid(const Identifier& astnode );
    bool valid(const IntType& astnode );
    bool valid(const BoolType& astnode );


    bool valid(const FloatLitral& astnode );
    bool valid(const BoolLitral& astnode );
    bool valid(const NumericLitral& astnode );
    bool valid(const NullLitral& astnode );
    bool valid(const StringLitral& astnode );

// bool valid(const TypeState& astnode );
// bool valid(const EnumLitral& astnode );
// bool valid(const NewState& astnode );
// bool valid(const FreeState& astnode );
};

}