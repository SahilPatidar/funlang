#include"../../include/analyzer/type_checker.hpp"

namespace analyzer{


TablePtr TypeChecker::newTable(TablePtr table) {
    return std::make_shared<SymTable<TypePtr>>(table);
}


std::string TypeChecker::identifier(const AstPtr& iden) {
    if(iden->nodeCategory() != NODE_IDEN){
        //todo
    }

    return std::dynamic_pointer_cast<ast::Identifier>(iden)->iden();
}

bool TypeChecker::isValid(TypePtr &type, AstPtr &node) {
    node->accept(*this);
    if(type->type() != m_type->type()){
        //tdod
    }
    return true;
}   

bool TypeChecker::isValid(const TypePtr &type1, const TypePtr &type2) {
    if((retype != NULL && m_type == NULL ) ||
        (retype == NULL && m_type != NULL )) {
        //todo
    } 
    if((retype != NULL && m_type != NULL) && (retype->type() != m_type->type())){
        //todo
    }

    return true;
}   

bool TypeChecker::visit(const Identifier& astnode) {
    if(!table->contains(astnode.iden())){
        //todo
    }else{
        m_type = table->get(astnode.iden());
    }

    //if(m_type->type() != unserdefined){
        //todo
    //}
    return true;
}


bool TypeChecker::visit(const BineryExper& astnode) {
    astnode.leftOpr()->accept(*this);
    TypePtr left = m_type;
    astnode.rightOpr()->accept(*this);
    if(m_type == NULL){

    }

    if(!left->OperatorMatch(astnode.oprator(), m_type)){

    }
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
    if(m_type->type() != TYPE_FUNCTION){
            //todo
    }
    auto functype = std::dynamic_pointer_cast<ast::FuncType>(m_type);
    if(functype->paramType().size() != astnode.arg().size()){
        //todo
    }else{
        for(int i = 0 ; i < astnode.arg().size(); i++){
           isValid(functype->paramType()[i], astnode.arg()[i]);            
        }
    }

    m_type = functype->retType();
    return true;
}

//todo--------============
bool TypeChecker::visit(const FunctionDef& astnode) {
    
    table->setFlag(true);
    std::string name = identifier(astnode.func_name());
    if(table->contains(name)){
        //todo
    }
    std::vector<TypePtr>p_type;
    for(auto &param: astnode.parameter()){
        std::dynamic_pointer_cast<ast::Parameter>(param)->p_type()->accept(*this);
        if(m_type == NULL){
            //todo
        } else {
            p_type.push_back(m_type);
            table->insert(identifier(param),m_type);
        }
    }       
    astnode.ret_type()->accept(*this);
    if(m_type == NULL){
        //todo
    }
    retype = m_type;
    m_type = TypeGenerator::FuncTypeGenerate(p_type,retype);
    table->pop();
    table->setFlag(false);
    table->insert(name, m_type);
    return true;
}


bool TypeChecker::visit(const ReturnState& astnode) {
    astnode.value()->accept(*this);
    isValid(m_type, retype);
    return true;
}

//todo
bool TypeChecker::visit(const FieldExpr& astnode) {
    astnode.listof()[0]->accept(*this);
    TypePtr prev_type = m_type;
    for(auto &val: astnode.listof()){
        val->accept(*this);
        if(m_type->type() != prev_type->type()){
            //todo
        }
        prev_type = m_type;
    }
    return true;
}


bool TypeChecker::visit(const PrefixExper& astnode) {
    astnode.variable()->accept(*this);
    TypePtr type = m_type;
    if(m_type == NULL){
        //todo
    }
    m_type->UnaryOpMatch(astnode.oprator());
    return true;
}

bool TypeChecker::visit(const LetState& astnode) {
    std::string name = identifier(astnode.varName());
    astnode.varType()->accept(*this);
    if(m_type == NULL) {
        astnode.varVal()->accept(*this);
        if(m_type == NULL) {
            //todo
        }else {
            astnode.setType(m_type);
        }
    }else { 
        TypePtr ty = m_type;
        astnode.varVal()->accept(*this);
        if(m_type != NULL) {
            if(m_type->type() != ty->type()){
                //todo
            }
        }
    }
    table->insert(name, m_type);
    return true;
}



bool TypeChecker::visit(const ConstState& astnode) {
    astnode.vartype()->accept(*this);
    if(m_type == NULL) {
        //todo
    }else{
        std::string name = identifier(astnode.vname());
        TypePtr type = m_type;
        astnode.value()->accept(*this);
        if(m_type == NULL){
            //todo
        }
        isValid(type, m_type);
       table->insert(name, m_type);

    }

    return true;
}

bool TypeChecker::visit(const ForInLoop& astnode) {
    TablePtr old = table;
    table = newTable(table);
    astnode.leftExpr()->accept(*this);
    astnode.rightExpr()->accept(*this);
    if(m_type){
        //todo
    }
    //body
    table = old;
    return true;
}


bool TypeChecker::visit(const IfStatement &astnode) {
    astnode.condition()->accept(*this);
    if(m_type == NULL){
        //todo
    }
    TypePtr type = m_type;
    //body;
    return true;
}

bool TypeChecker::visit(const StructState &astnode) {
    TypePtr ty;
    if(astnode.isDeclaration()){
        std::string name = identifier(astnode.name());
        std::map<std::string,TypePtr>ele;
        if(!astnode.element().empty()){
            for(size_t i = 0 ; i < astnode.element().size(); i++){
                auto val = std::dynamic_pointer_cast<Parameter>(astnode.element()[i]);
                std::string name = identifier(val->identifier());
                val->p_type()->accept(*this);
                if(m_type == NULL){
                    //todo
                }else{
                    ele.insert({name, m_type});
                }
            }
        }
        m_type = TypeGenerator::StructTyGen(ele);
        table->insert(name,m_type);
        return true;
    }else{
        astnode.name()->accept(*this);
        TypePtr ty;
        if(m_type->type() != TYPE_STRUCT){
        ///todo
        }else{
            ty = m_type;
            auto type = std::dynamic_pointer_cast<StructType>(m_type);
            if(astnode.element().size() != type->member().size()){
                //todo
            }else{
                for(size_t i = 0; i < astnode.element().size(); i++){
                    auto val = std::dynamic_pointer_cast<Parameter>(astnode.element()[i]);
                    std::string n = identifier(val->identifier());
                    val->p_type()->accept(*this);
                    if(!type->contain(n)){
                        //todo
                    }else if(m_type == NULL){
                        if(!type->matchType(n, m_type)){
                                //todo
                        }
                    }
                    
                }
            }
        }
    }
    m_type = ty;
    return true;
}

}
 