
#include"../../include/parser/Ast.hpp"

namespace ast {
    
    std::string Program::node_str() const {
        std::string str = "";
        std::cout<<statms.size()<<std::endl;

        for(auto& statm:statms){
            str += statm->node_str();
            str += '\n';
        }
        return str;
    }

    std::string NumericLitral::node_str() const{
        return tok.data;
    }

    std::string FloatLitral::node_str() const{
        return tok.data;
    }

    std::string BoolLitral::node_str() const {
        return tok.data;
    }

    std::string StringLitral::node_str() const {
        return tok.data;
    }

    std::string NullLitral::node_str() const {
        return tok.data;
    }

    std::string Identifier::node_str() const {
        return tok.data;
    }

    std::string BlockStatement::node_str() const {
        std::string str = "";
        for(auto& statm:statms){
            str += statm->node_str();
            str += ";\n";
        }
        return str;
    }

    std::string EnumLitral::node_str() const {
        std::string str = "enum ";

        for (size_t i = 0; i < u_data.size(); i++) {
            if (i)
                str += "\n";

            str += u_data[i].first->node_str();
            if (u_data[i].second) {
                str += " = ";
                str += u_data[i].second->node_str();
            }
        }

        return str;
    }

    std::string IntType::node_str() const {
        return tok.data;
    }
    
    std::string StringType::node_str() const {
        return tok.data;
    }
    
    std::string FloatType::node_str() const {
        return tok.data;
    }

    std::string BoolType::node_str() const {
        return tok.data;
    }

    std::string TypeState::node_str() const {
        std::string str = "";
        str += tok.data;
        str += " ";
        str += left->node_str();
        str += " ";
        str += right->node_str();
        str += ";";
        return str;
    }

    std::string ConstState::node_str() const {
        std::string str = "const";
        str += " ";
        str += name->node_str();
        str += " ";
        str += type->node_str();
        str += " = ";
        str += val->node_str();
        str += ";";
        return str;
    }

    std::string LetState::node_str() const {
        std::string str = "let";
        str += " ";
        for(int i = 0 ; i < name.size(); i++){
            if(i)
                str += ",";
            str += name[i]->node_str();
        }
        
        str += " ";
        str += type->node_str();
        return str;
    }

    std::string ArrayType::node_str() const {
        std::string str = "[";
        str += size->node_str();
        str += "]";
        str += type->node_str();
        return str;
    }

    std::string IndexExpr::node_str() const {
        std::string str = "";
        str += expr->node_str();
        str += "[";
        str += index->node_str();
        str += "]";
        return str;
    }
    
    std::string BineryExper::node_str() const {
        std::string str = "";
        str += " (-> ";
        str += left->node_str();
        str += lex::token[op];
        str += right->node_str();
        str += " <-) ";
        return str;
    }
    
    std::string PrefixExper::node_str() const {
        std::string str = "";
        str += lex::token[op];
        str += var->node_str();
        return str;
    }
    
    std::string PostfixExper::node_str() const {
        std::string str = "";
        str += lex::token[op];
        str += var->node_str();
        return str;
    }
    
    std::string ForLoopState::node_str() const {
        std::string str = "for ";
        if(h1)
         str += h1->node_str();
    
        str += h2->node_str();

        if(h3)
         str += h3->node_str();
        str += "{\n";
        str += body->node_str();
        str += "}\n";
        return str;
    }
    
    std::string InState::node_str() const {
        std::string str = "for";
        str += left->node_str();
        str += "in";
        str += right->node_str();
        str += "{\n";
        str += body->node_str();
        str += "}\n";
        return str;
    }   
    
    std::string IfStatement::node_str() const {
        std::string str = "if ";
        str += cond->node_str();
        str += " {\n";
        str +=  ifbody->node_str();
        str += " } ";
        if(elbody){
            str += "else ";
            str += " {\n";
            str += elbody->node_str();
            str += " }";
        }
        return str + "\n";
    }
    
    std::string PointerType::node_str() const {
        std::string str = "*";
        str += base->node_str();
        return str;
    }
    
    std::string BranchState::node_str() const {
        return tok.data + ";\n";
    }
    
    std::string MemberExpr::node_str() const {
        std::string str = "";
        str += left->node_str();
        if(mem_op == DOT)
            str += ".";
        else
            str += "->";
        str += right->node_str();
        return str;
    }
    
    std::string StructState::node_str() const {
        std::string str = "struct";
        str += "{";
        for(int i = 0 ; i < elemt.size(); i++){
            str += elemt[i]->node_str();
            str += ";\n";
        }
        str += "};";
        return str;
    }
    
    std::string ListExpr::node_str() const {
        std::string str = " { ";
        for(int i = 0 ; i < list.size(); i++){
            str += list[i]->node_str();
            str += ",";
        }
        str += " };\n";
        return str;
    }
    
    std::string AssignmentExpr::node_str() const {
        std::string str = "";
        str += left->node_str();
        str += " = ";
        str += right->node_str();
        str += ";\n";
        return str;
    }
    
    std::string Parameter::node_str() const {
        std::string str = "";
        str += iden->node_str();
        str += " ";
        str += type->node_str();
        return str;
    }
    
    std::string FunctionDef::node_str() const {
        std::string str = "fn ";
        str += name->node_str();
        str += " ( ";
        if(!param.empty()){
         
            for(size_t i = 0; i < param.size(); i++){
                str += param[i]->node_str();
                str += ",";
            }
        }
        str += " ) ";
        str += retype->node_str();
        str += " {\n";
        str += body->node_str();
        str += " }\n";
        return str;
    }

    std::string ReturnState::node_str() const {
        std::string res = "return ";

        res += ret_val->node_str();

        return res;
    }
    
    std::string FunctionCall::node_str() const {
        std::string res = "";

        res += name->node_str();
        res += "(";

        for (size_t i = 0; i < args.size(); i++) {
            if (i)
                res += ", ";

            res += args[i]->node_str();
        }

        res += ")";
        return res;
    }
}
