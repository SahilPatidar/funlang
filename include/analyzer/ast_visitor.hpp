#pragma once
#include"../parser/Ast.hpp"
namespace ast{
class AstVisitor{
    public:
    virtual ~AstVisitor() = default;

    virtual bool visit(const Program& astnode ){ return false; }
    virtual bool visit(const BlockStatement& astnode ){ return false; }
    virtual bool visit(const FunctionDef& astnode ){ return false; }
    virtual bool visit(const WhileLoop& astnode ){ return false; }
    virtual bool visit(const ForInLoop& astnode ){ return false; };
    virtual bool visit(const StructState& astnode ){ return false; }
    virtual bool visit(const BranchState& astnode ){ return false; }
    virtual bool visit(const ConstState& astnode ){ return false; }
    virtual bool visit(const Tuple& astnode ){ return false; }
    virtual bool visit(const LetState& astnode ){ return false; }
    virtual bool visit(const IfStatement& astnode ){ return false; }
    virtual bool visit(const ReturnState& astnode ){ return false; }
    
    virtual bool visit(const BineryExper& astnode ){ return false; }
    virtual bool visit(const AssignmentExpr& astnode ){ return false; }
    virtual bool visit(const ListExpr& astnode ) { return false; };
    virtual bool visit(const FunctionCall& astnode ){ return false; }
    virtual bool visit(const MemberExpr& astnode ){ return false; }
    virtual bool visit(const IndexExpr& astnode ){ return false; }
    virtual bool visit(const PrefixExper& astnode ){ return false; }
    virtual bool visit(const Parameter& astnode ){ return false; }
    
    virtual bool visit(const PointerExpr& astnode ){ return false; }
    virtual bool visit(const ArrayType& astnode ) { return false; }
    virtual bool visit(const PreDefType& astnode ){ return false; }
    virtual bool visit(const Identifier& astnode ){ return false; }
    

    virtual bool visit(const FloatLiteral& astnode ){ return false; }
    virtual bool visit(const BoolLiteral& astnode ){ return false; }
    virtual bool visit(const NumericLiteral& astnode ){ return false; }
    virtual bool visit(const NullLiteral& astnode ){ return false; }
    virtual bool visit(const StringLiteral& astnode ){ return false; }
    
    //virtual bool visit(const TypeState& astnode ){ return false; }
    //virtual bool visit(const EnumLitral& astnode ){ return false; }
    //virtual bool visit(const NewState& astnode ){ return false; }
    //virtual bool visit(const FreeState& astnode ){ return false; }
};

}