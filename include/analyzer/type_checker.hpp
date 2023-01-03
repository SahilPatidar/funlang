#pragma once
#include"ast_visitor.hpp"
#include"../parser/type.hpp"
#include"symbol_table.hpp"

namespace analyzer{

using TablePtr = std::shared_ptr<Table<TypePtr>>;
using namespace ast;

class TypeChecker: public AstVisitor {
private:
    TablePtr table;
    TypePtr m_type;

    std::string identifier(const AstPtr& iden);
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
    // bool visit(const Parameter& astnode );

    bool visit(const PointerType& astnode );
    bool visit(const ArrayType& astnode ) ;
    bool visit(const FloatType& astnode );
    bool visit(const StringType& astnode );
    bool visit(const Identifier& astnode );
    bool visit(const IntType& astnode );
    bool visit(const BoolType& astnode );


    bool visit(const FloatLiteral& astnode );
    bool visit(const BoolLiteral& astnode );
    bool visit(const NumericLiteral& astnode );
    bool visit(const NullLiteral& astnode );
    bool visit(const StringLiteral& astnode );
public:
    TypeChecker();
};
}
