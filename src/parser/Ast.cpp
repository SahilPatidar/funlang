
#include"../../include/parser/Ast.hpp"

namespace ast {
    
    std::string Program::toString() const {
        std::string str = "";

        for(int i = 0 ; i < statms.size(); i++){
            str += statms[i]->toString();
            str += '\n';
        }
        return str;
    }

    std::string NumericLiteral::toString() const{
        return tok.data;
    }

    std::string FloatLiteral::toString() const{
        return tok.data;
    }

    std::string BoolLiteral::toString() const {
        return tok.data;
    }

    std::string StringLiteral::toString() const {
        return tok.data;
    }

    std::string NullLiteral::toString() const {
        return tok.data;
    }

    std::string Identifier::toString() const {
        return tok.data;
    }

    std::string BlockStatement::toString() const {
        std::string str = "";
        for(int i = 0 ; i < statms.size(); i++){
            str += statms[i]->toString();
            str += "\n";
        }
        return str;
    }

    std::string Extern::toString() const {
        std::string str = "extern ";
        str += lib->toString();
        str += block->toString();
        return str;
    }
    
    std::string Use::toString() const {
        std::string str = "use";
        str += name->toString();
        str += path->toString();
        str += ";\n";
        return str;
    }
    
    std::string Tuple::toString() const {
        std::string str = "(";
        for(auto& t:tuple){
            str += t->toString();
            str += ", ";
        }
        str += ")";
        return str;
    }

    // std::string EnumLitral::toString() const {
    //     std::string str = "enum ";

    //     for (size_t i = 0; i < u_data.size(); i++) {
    //         if (i)
    //             str += "\n";

    //         str += u_data[i].first->toString();
    //         if (u_data[i].second) {
    //             str += " = ";
    //             str += u_data[i].second->toString();
    //         }
    //     }

    //     return str;
    // }

    std::string PreDefineType::toString() const {
        return tok.data;
    }

    std::string TypeState::toString() const {
        std::string str = "";
        str += tok.data;
        str += " ";
        str += left->toString();
        str += " ";
        str += right->toString();
        str += ";";
        return str;
    }

    std::string VarState::toString() const {
        std::string str = tok.data;
        str += " ";
        str += name->toString();
        str += " : ";
        if(type){
            str += type->toString();
        }
        if(val){
            str += " = ";
            str += val->toString();
        }
        str += ";";
        return str;
    }


    std::string ArrayType::toString() const {
        std::string str = "[";
        for(int i = 0 ; i < size.size(); i++){
            str += size[i]->toString();
            str += ";";
        }
        str += "]";
        str += type->toString();
        return str;
    }

    std::string GroupedExpr::toString() const {
        std::string str = "(";
        str += expr->toString();
        str += ")";
        return str;
    }

    std::string AsState::toString() const {
        std::string str = left->toString();
        str += " as ";
        str += right->toString();
        return str;
    }

    
    std::string FunType::toString() const {
        std::string str = "fn";
        str += "(";
        if(!ty.empty()){
            for(int i = 0 ; i < ty.size(); i++){
                str += ty[i]->toString();
                str += ", ";
            }
        }
        str += ")";
        if(ret){
            str += ret->toString();
        }
        return str;
    }
    
    std::string RefExpr::toString() const {
        std::string str = tok.data;
        str += base->toString();
        return str;
    }

    std::string Path::toString() const {
        std::string str = "";
        str += lexpression()->toString();
        str += "::";
        str += rexpression()->toString();
        str += "\n";
        return str;
    }


    std::string IndexExpr::toString() const {
        std::string str = "";
        str += iden->toString();
        str += "[";
        for(int i = 0 ; i < index.size(); i++){
            str += index[i]->toString();
            str += ";";
        }
        str += "]";
        return str;
    }
    
    std::string BineryExper::toString() const {
        std::string str = "";
        // str += " ( ";
        str += left->toString();
        str += lex::token[op];
        str += right->toString();
        // str += " ) ";
        return str;
    }
    
    std::string PrefixExper::toString() const {
        std::string str = "";
        str += lex::token[op];
        str += var->toString();
        return str;
    }
    
    
    std::string ForInLoop::toString() const {
        std::string str = "for ";
        str += left->toString();
        str += " in ";
        str += right->toString();
        str += " : {\n";
        str += body->toString();
        str += "}\n";
        return str;
    }

    std::string WhileLoop::toString() const {
        std::string str = "while ";
        str += expr->toString();
        str += " {\n";
        str += body->toString();
        str += "}\n";
        return str;
    }

    
    std::string IfStatement::toString() const {
        std::string str = "if ";
        str += cond->toString();
        str += " {\n";
        str +=  ifbody->toString();
        str += " } ";
        if(elbody){
            str += "else ";
            str += " {\n";
            str += elbody->toString();
            str += " }";
        }
        return str + "\n";
    }
    
    std::string PointerExpr::toString() const {
        std::string str = "*";
        str += base->toString();
        return str;
    }
    
    std::string BranchState::toString() const {
        return tok.data + ";\n";
    }
    
    std::string MemberExpr::toString() const {
        std::string str = "";
        str += left->toString();
        if(mem_op == DOT)
            str += ".";
        else
            str += "->";
        str += right->toString();
        return str;
    }
    
    std::string StructState::toString() const {
        std::string str = "struct ";
        str += iden->toString();
        str += "{\n";
        for(int i = 0 ; i < elemt.size(); i++){
            str += elemt[i]->toString();
            str += ",\n";
        }
        str += " };";
        return str;
    }
    
    std::string ListExpr::toString() const {
        std::string str = " [ ";
        for(int i = 0 ; i < list.size(); i++){
            str += list[i]->toString();
            str += ",";
        }
        str += " ] ";
        return str;
    }
    
    std::string AssignmentExpr::toString() const {
        std::string str = "";
        str += left->toString();
        str += tok.data;
        str += right->toString();
        str += ";\n";
        return str;
    }
    
    std::string Parameter::toString() const {
        std::string str = "";
        str += iden->toString();
        str += " : ";
        str += type->toString();
        return str;
    }
    
    std::string FunctionDef::toString() const {
        std::string str = "fn ";
        str += name->toString();
        str += " ( ";
        if(!param.empty()){
         
            for(size_t i = 0; i < param.size(); i++){
                str += param[i]->toString();
                str += ",";
            }
        }

        str += " ) ";
        if(retype){
            str += " -> ";
            str += retype->toString();
        }
        if(body)
        {    
            str += " {\n";
            str += body->toString();
            str += " }\n";
        }else{
            str += ";\n";
        }
        return str;
    }

    std::string ReturnState::toString() const {
        std::string res = "return ";

        res += val->toString();
        res += ";\n";
        return res;
    }

    std::string Variadic::toString() const {
        std::string res = left->toString();
        res += "..";
        res += right->toString();
        return res;
    }
    
    std::string FunctionCall::toString() const {
        std::string res = "";

        res += name->toString();
        res += "(";

        for (size_t i = 0; i < args.size(); i++) {
            if (i)
                res += ", ";

            res += args[i]->toString();
        }

        res += ")";
        return res;
    }
}
