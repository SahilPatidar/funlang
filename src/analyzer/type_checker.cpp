#include"../../include/analyzer/type_checker.hpp"

namespace analyzer{

std::string TypeChecker::identifier(const AstPtr& iden) {
    if(iden->nodeCategory() != NODE_IDEN){
        //todo
    }

    return std::dynamic_pointer_cast<ast::Identifier>(iden)->iden();
}


bool TypeChecker::visit(const BineryExper& astnode) {
    astnode.leftOpr()->accept(*this);
    TypePtr left = m_type;
    astnode.rightOpr()->accept(*this);
    if(m_type == NULL){

    }

    if(!left->OperatorMatch(astnode.oprator(), m_type)){

    }
    
    m_type = TypeGenerator::Generate(m_type->type());
    return true;
}

bool TypeChecker::visit(const AssignmentExpr& astnode) {
    astnode.lvalue()->accept(*this);
    TypePtr lval = m_type;
    astnode.rvalue()->accept(*this);
    if(m_type == NULL){

    }

    if(!lval->OperatorMatch(astnode.oprator(), m_type)){

    }

    m_type = TypeGenerator::Generate(m_type->type());
    return true;
}


bool TypeChecker::visit(const FunctionCall& astnode) {
    astnode.funcname()->accept(*this);
    if(m_type->type() != FUNCTION){
            //todo
    }
    TypePtr func = m_type;
    for(auto &arg: astnode.arg()){
        arg->accept(*this);
        TypePtr argtype = m_type;
        if(func->type() != argtype->type()){
            //todo
        }
    } 
    TypePtr type = table->get(astnode.funcname()->toString());
    m_type = TypeGenerator::Generate(type->type());
    return true;
}


bool TypeChecker::visit(const FunctionDef& astnode) {
    std::string name = identifier(astnode.func_name());
    std::vector<TypePtr>p_type;
    for(auto &param: astnode.parameter()){
        std::dynamic_pointer_cast<ast::Parameter>(param)->p_type()->accept(*this);
        if(m_type == NULL){
            //todo
        }
        p_type.push_back(m_type);
    }       
    astnode.ret_type()->accept(*this);
    if(m_type == NULL){
        //todo
    }
    TypePtr retype = m_type;
    m_type = TypeGenerator::FuncTypeGenerate(p_type,retype);
    table->insert(name, m_type);
    return true;
}

bool TypeChecker::visit(const ListExpr& astnode){
    
}

}
 