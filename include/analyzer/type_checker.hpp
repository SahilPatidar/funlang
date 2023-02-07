#pragma once
#include"ast_visitor.hpp"
#include"../parser/type.hpp"
#include"symbol_table.hpp"

namespace analyzer{

using namespace ast;
using TablePtr = std::shared_ptr<SymTable<TypePtr>>;

class TypeChecker: public AstVisitor {
private:
    TablePtr table;
    TypePtr m_type;
    TypePtr retype = NULL;
    std::string identifier(const AstPtr& iden);
    template<typename T>
    T dynamicPtrCast(const AstPtr& iden);
    TablePtr newTable(TablePtr globtable);
    bool isValid(TypePtr &type, AstPtr &node);
    bool isValid(const TypePtr &type1, const TypePtr &type2);
    bool visit(const Program& astnode);
    bool visit(const BlockStatement& astnode );
    bool visit(const FunctionDef& astnode );
    bool visit(const WhileLoop& astnode );
    bool visit(const ForInLoop& astnode );
    bool visit(const StructState& astnode );
    bool visit(const BranchState& astnode );
    bool visit(const ConstState& astnode );
    bool visit(const Tuple& astnode );
    bool visit(const LetState& astnode );
    bool visit(const IfStatement& astnode );
    bool visit(const ReturnState& astnode );
    
    bool visit(const BineryExper& astnode );
    bool visit(const AssignmentExpr& astnode );
    bool visit(const ListExpr& astnode ) ;
    bool visit(const FunctionCall& astnode );
    bool visit(const MemberExpr& astnode );
    bool visit(const IndexExpr& astnode );
    bool visit(const PrefixExper& astnode );

    bool visit(const PointerExpr& astnode );
    bool visit(const ArrayType& astnode ) ;
    bool visit(const PreDefType& astnode );
    bool visit(const Identifier& astnode );


    bool visit(const FloatLiteral& astnode );
    bool visit(const BoolLiteral& astnode );
    bool visit(const NumericLiteral& astnode );
    bool visit(const NullLiteral& astnode );
    bool visit(const StringLiteral& astnode );
public:
    TypeChecker();
};
}
