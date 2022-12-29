#pragma once
#include"../parser/Ast.hpp"
namespace ast{
class AstVisitor{
    public:
    virtual ~AstVisitor() = default;

    virtual bool valid(const Program& astnode ){ return false; };
    virtual bool valid(const BlockStatement& astnode ){ return false; };
    virtual bool valid(const FunctionDef& astnode ){ return false; }
    virtual bool valid(const ForLoopState& astnode ){ return false; };
    virtual bool valid(const StructState& astnode ){ return false; }
    virtual bool valid(const BranchState& astnode ){ return false; };
    virtual bool valid(const ConstState& astnode ){ return false; };
    virtual bool valid(const FreeState& astnode ){ return false; };
    virtual bool valid(const LetState& astnode ){ return false; }
    virtual bool valid(const IfStatement& astnode ){ return false; }
    virtual bool valid(const ReturnState& astnode ){ return false; }
    virtual bool valid(const InState& astnode ){ return false; }
    
    virtual bool valid(const BineryExper& astnode ){ return false; };
    virtual bool valid(const AssignmentExpr& astnode ){ return false; };
    virtual bool valid(const ListExpr& astnode ) { return false; };
    virtual bool valid(const FunctionCall& astnode ){ return false; }
    virtual bool valid(const MemberExpr& astnode ){ return false; }
    virtual bool valid(const IndexExpr& astnode ){ return false; }
    virtual bool valid(const PostfixExper& astnode ){ return false; }
    virtual bool valid(const PrefixExper& astnode ){ return false; }
    virtual bool valid(const Parameter& astnode ){ return false; }
    
    virtual bool valid(const PointerType& astnode ){ return false; }
    virtual bool valid(const ArrayType& astnode ) { return false; };
    virtual bool valid(const FloatType& astnode ){ return false; };
    virtual bool valid(const StringType& astnode ){ return false; }
    virtual bool valid(const Identifier& astnode ){ return false; }
    virtual bool valid(const IntType& astnode ){ return false; }
    virtual bool valid(const BoolType& astnode ){ return false; }
    

    virtual bool valid(const FloatLitral& astnode ){ return false; };
    virtual bool valid(const BoolLitral& astnode ){ return false; };
    virtual bool valid(const NumericLitral& astnode ){ return false; }
    virtual bool valid(const NullLitral& astnode ){ return false; }
    virtual bool valid(const StringLitral& astnode ){ return false; }
    
    //virtual bool valid(const TypeState& astnode ){ return false; }
    //virtual bool valid(const EnumLitral& astnode ){ return false; }
    //virtual bool valid(const NewState& astnode ){ return false; }
    //virtual bool valid(const FreeState& astnode ){ return false; }
};

}