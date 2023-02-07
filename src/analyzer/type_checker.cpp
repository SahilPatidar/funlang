#include"../../include/analyzer/type_checker.hpp"

namespace analyzer{


TablePtr TypeChecker::newTable(TablePtr table) {
    return std::make_shared<SymTable<TypePtr>>(table);
}

bool TypeChecker::checkTuple(TypePtr &type1, TypePtr &type2) {
    auto ty1 = std::dynamic_pointer_cast<TupleType>(type1);
    auto ty2 = std::dynamic_pointer_cast<TupleType>(type2);

    if(ty1->tupleTy().size() != ty2->tupleTy().size()){
       //todo
    }

    if(!ty1->tupleTy().empty()&&!ty2->tupleTy().empty()){
        for(int i = 0; i < ty1->tupleTy().size(); i++){
            if(ty1->tupleTy()[i]->type() == TYPE_POINTER){
                auto ty1 = std::dynamic_pointer_cast<Pointer>(type1);
                auto ty2 = std::dynamic_pointer_cast<Pointer>(type2);
                if(ty1->baseType()->type() != ty2->baseType()->type()){
                    //todo
                }
            }
            if(ty1->tupleTy()[i]->type() != ty2->tupleTy()[i]->type()){
                //todo
            }
        }
    }
    return true;
}

std::string TypeChecker::identifier(const AstPtr& iden) {
    if(iden->nodeCategory() != NODE_IDEN){
        //todo
    }

    return std::dynamic_pointer_cast<ast::Identifier>(iden)->iden();
} 

bool TypeChecker::isValid(const TypePtr &type1, const TypePtr &type2) {
    if((type1 != NULL && type2 == NULL ) ||
        (type1 == NULL && type2 != NULL )) {
        //todo
    } 
    if((type1 != NULL && type2 != NULL) && (type1->type() != type2->type())){
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

    if(lval->type() == TYPE_TUPLE){
        if(checkTuple(lval,m_type)){
            //todo
        }
    }
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
            astnode.arg()[i]->accept(*this);
            isValid(functype->paramType()[i],m_type);            
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
    if(retype->type() == TYPE_TUPLE){
        if(checkTuple(retype,m_type)){
            //todo
        }
    }
    isValid(m_type, retype);

    return true;
}

//todo
bool TypeChecker::visit(const ListExpr& astnode) {
    astnode.listof()[0]->accept(*this);
    TypePtr prev_type = m_type;
    if(!astnode.listof().empty()){
        for(auto &val: astnode.listof()){
            val->accept(*this);
            if(m_type->type() != prev_type->type()){
                //todo
            }
            prev_type = m_type;
        }
    }
    m_type = TypeGenerator::ArrayTyGen(prev_type);
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

bool TypeChecker::visit(const VarState& astnode) {
    auto& letnode = const_cast<VarState&>(astnode);
    std::string name = identifier(astnode.varName());
    if(table->contains(name)){
            //todo
    }
    if(astnode.token().tok_type == LET){
        
        astnode.varType()->accept(*this);
        if(m_type == NULL) {
            astnode.varVal()->accept(*this);
            if(m_type == NULL) {
                //todo
            }else {
                letnode.setType(m_type);
            }
        }else { 
            TypePtr ty = m_type;
            astnode.varVal()->accept(*this);
             if(ty->type() == TYPE_TUPLE){
                if(checkTuple(ty,m_type)){
                    //todo
                }
            }
            if(m_type != NULL) {
                if(m_type->type() != ty->type()){
                    //todo
                }
            }
        }
    }else if(astnode.token().tok_type == CONST) {
        //todo
        astnode.varType()->accept(*this);
        if(m_type == NULL) {
            //todo
        }else{
            TypePtr type = m_type;
            astnode.varVal()->accept(*this);
            if(m_type == NULL){
                //todo
            }
            isValid(type, m_type);
        }

    }
    table->insert(name, m_type);
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


bool TypeChecker::visit(const MemberExpr &astnode){
    astnode.leftid()->accept(*this);
    if(astnode.mem_operator() == DOT){
        if(m_type == NULL){
            //todo
        }
        if(m_type->type() == TYPE_STRUCT) {
            auto ty = std::dynamic_pointer_cast<StructType>(m_type);
            std::string n = identifier(astnode.rightid());
            if(!ty->contain(n)){
                //todo
            }
            m_type = ty->getMem(n);
        }
    } else if(astnode.mem_operator() == ARROW){
        if(m_type == NULL){
            //todo
        }
        if(m_type->type() == TYPE_POINTER) {
            auto ty1 = std::dynamic_pointer_cast<Pointer>(m_type);
            if(ty1->baseType()->type() != TYPE_STRUCT){
                //todo
            }
            auto ty2 = std::dynamic_pointer_cast<StructType>(ty1->baseType());
            std::string n = identifier(astnode.rightid());
            if(!ty2->contain(n)){
                //todo
            }
            m_type = ty2->getMem(n);
        }
    }
    return true;
}

bool TypeChecker::visit(const ArrayType& astnode) {
    astnode.arraytype()->accept(*this);
    std::vector<std::string>s;
    TypePtr ty; 
    if(m_type == NULL) {
        //todo
    }else{
        ty = m_type;
        if(astnode.arraysize().empty()){
            //todo
        }else{
            for(int i = 0 ; i < astnode.arraysize().size(); i++){
                astnode.arraysize()[i]->accept(*this);
                if(!m_type){
                    //todo
                }
                if(m_type->type() == TYPE_INT){
                    astnode.arraysize()[i]->toString();
                }
            }
        }
    }
    m_type = TypeGenerator::ArrayTyGen(ty);
    return true;
}

bool TypeChecker::visit(const IndexExpr& astnode ) {
    astnode.identifier()->accept(*this);
    if(m_type->type() != TYPE_ARRAY) {
        //todo
    }else {
        auto arr = std::dynamic_pointer_cast<Array>(m_type);
        
        
    }
}

bool TypeChecker::visit(const Tuple& astnode) {
    if(astnode.isTupleType()){
        std::vector<TypePtr>ty;
        if(!astnode.tupleEle().empty()){
            for(int i = 0 ; i < astnode.tupleEle().size(); i++){
                astnode.tupleEle()[i]->accept(*this);
                if(!m_type){
                    //todo
                }
                ty.push_back(m_type);
            }
        }
        m_type = TypeGenerator::TupleTyGen(ty);
    }else {
        if(!astnode.tupleEle().empty()){
            for(int i = 0 ; i < astnode.tupleEle().size(); i++){
                astnode.tupleEle()[i]->accept(*this);
                if(!m_type){
                    //todo
                }
                if(m_type->)
            }
        }
    }
}


}
 