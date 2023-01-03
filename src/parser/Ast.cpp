
#include"../../include/parser/Ast.hpp"

namespace ast {
    
    std::string Program::toString() const {
        std::string str = "";
        std::cout<<statms.size()<<std::endl;

        for(auto& statm:statms){
            str += statm->toString();
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
        for(auto& statm:statms){
            str += statm->toString();
            str += ";\n";
        }
        return str;
    }

    std::string EnumLitral::toString() const {
        std::string str = "enum ";

        for (size_t i = 0; i < u_data.size(); i++) {
            if (i)
                str += "\n";

            str += u_data[i].first->toString();
            if (u_data[i].second) {
                str += " = ";
                str += u_data[i].second->toString();
            }
        }

        return str;
    }

    std::string IntType::toString() const {
        return tok.data;
    }
    
    std::string StringType::toString() const {
        return tok.data;
    }
    
    std::string FloatType::toString() const {
        return tok.data;
    }

    std::string BoolType::toString() const {
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

    std::string ConstState::toString() const {
        std::string str = "const";
        str += " ";
        str += name->toString();
        str += " ";
        str += type->toString();
        str += " = ";
        str += val->toString();
        str += ";";
        return str;
    }

    std::string LetState::toString() const {
        std::string str = "let";
        str += " ";
        for(int i = 0 ; i < name.size(); i++){
            if(i)
                str += ",";
            str += name[i]->toString();
        }
        
        str += " ";
        str += type->toString();
        return str;
    }

    std::string ArrayType::toString() const {
        std::string str = "[";
        str += size->toString();
        str += "]";
        str += type->toString();
        return str;
    }

    std::string IndexExpr::toString() const {
        std::string str = "";
        str += expr->toString();
        str += "[";
        str += index->toString();
        str += "]";
        return str;
    }
    
    std::string BineryExper::toString() const {
        std::string str = "";
        str += " (-> ";
        str += left->toString();
        str += lex::token[op];
        str += right->toString();
        str += " <-) ";
        return str;
    }
    
    std::string PrefixExper::toString() const {
        std::string str = "";
        str += lex::token[op];
        str += var->toString();
        return str;
    }
    
    std::string PostfixExper::toString() const {
        std::string str = "";
        str += lex::token[op];
        str += var->toString();
        return str;
    }
    
    std::string ForLoopState::toString() const {
        std::string str = "for ";
        if(h1)
         str += h1->toString();
    
        str += h2->toString();

        if(h3)
         str += h3->toString();
        str += "{\n";
        str += body->toString();
        str += "}\n";
        return str;
    }
    
    std::string InState::toString() const {
        std::string str = "for";
        str += left->toString();
        str += "in";
        str += right->toString();
        str += "{\n";
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
    
    std::string PointerType::toString() const {
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
        std::string str = "struct";
        str += "{";
        for(int i = 0 ; i < elemt.size(); i++){
            str += elemt[i]->toString();
            str += ";\n";
        }
        str += "};";
        return str;
    }
    
    std::string ListExpr::toString() const {
        std::string str = " { ";
        for(int i = 0 ; i < list.size(); i++){
            str += list[i]->toString();
            str += ",";
        }
        str += " };\n";
        return str;
    }
    
    std::string AssignmentExpr::toString() const {
        std::string str = "";
        str += left->toString();
        str += " = ";
        str += right->toString();
        str += ";\n";
        return str;
    }
    
    std::string Parameter::toString() const {
        std::string str = "";
        str += iden->toString();
        str += " ";
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
        str += retype->toString();
        str += " {\n";
        str += body->toString();
        str += " }\n";
        return str;
    }

    std::string ReturnState::toString() const {
        std::string res = "return ";

        res += ret_val->toString();

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
