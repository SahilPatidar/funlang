
#include"../../include/parser/parser.hpp"

namespace parser {
    
    void Parser::next() {
        if(cur_index + 1 < toks.size()) {
            ++cur_index;
            cur_token = toks[cur_index].tok_type;
        }
    }

    void Parser::dump(std::string msg){
        std::cout<<"step :: "<<"entering in -> "<<msg<<" "<<toks[cur_index].data<<std::endl;
    }
    void Parser::dump2(std::string msg){
        std::cout<<"step :: "<<"returning from -> "<<msg<<" "<<toks[cur_index].data<<std::endl;
    }

    bool Parser::BineryOP(Token_type tok) {
        return tok == STAR || tok == DIV || tok == MOD ||
            tok == PLUS || tok == MINUS || tok == LSHIFT || 
            tok == RSHIFT || tok == LT || tok == LEQL || 
            tok == GT ||tok == GEQL || tok == EQL || tok == NEQL ||
            tok == AND || tok == XOR_OP || tok == OR || 
            tok == AND_OP || tok == OR_OP;
    }   

     bool Parser::check(Token_type tok) {
        return cur_token == tok;
    }

     bool Parser::checkh(Token_type tok) {
        return next_t().tok_type == tok;
    }

    tokt Parser::next_t() {
        return (cur_index+1 < toks.size())?toks[cur_index+1]:toks[cur_index];
    }

    bool Parser::UnaryOP(Token_type tok) {
        return tok == PLUS|| tok == MINUS||
         tok == STAR|| tok == AND_OP||tok == NOT_OP|| tok == NOT;
    }

    bool Parser::AssignOP(Token_type tok){
        return tok == ASSN|| tok == ASSN_DIV||
         tok == ASSN_MINUS|| tok == ASSN_MOD||tok == ASSN_PLUS|| tok == ASSN_STAR|| 
         tok == AND_ASSN|| tok == XOR_ASSN||tok == OR_ASSN|| tok == NOT_ASSN;
    }
    
    bool Parser::PreDefType(Token_type tok){
        return tok == I8 || tok == I16 ||
         tok == I32 || tok == I64 || tok == UI8 || tok == UI16 ||
         tok == UI32 || tok == UI64 || tok == F32 || tok == F64 ||
         tok == STRING || tok == BOOL;
    }

    bool Parser::isTerminal(Token_type tok){
        return tok == RPAREN || tok == COMMA ||
         tok == RBRACE || tok == RBRACK || tok == COL || tok == SCOL;
    }

    int Parser::preced(Token_type op){
        switch (op)
        {
        case STAR:
        case DIV:
        case MOD:
            return 10;
        case PLUS:
        case MINUS:
            return 9;
        case LSHIFT:
        case RSHIFT:
            return 8;
        case LT:
        case LEQL:
        case GT:
        case GEQL:
            return 7;
        case EQL:
        case NEQL:
            return 6;
        case AND:
            return 5;
        case XOR_OP:
            return 4;
        case OR:
            return 3;    
        case AND_OP:
            return 2;  
        case OR_OP:
            return 1;
        default:
            break;
        }
        return 0;
    }

    bool Parser::isLiteral(Token_type tok) {
        return tok == INT||tok == STR||tok == CHAR|| tok == FLOAT||tok == TRUE||tok == FALSE;
    }


}