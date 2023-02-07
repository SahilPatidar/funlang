
#include"../../include/parser/p.hpp"

namespace parser {
    
    void Parser::next() {
        if(cur_index + 1 < toks.size()) {
            ++cur_index;
            cur_token = toks[cur_index].tok_type;
        }
    }

    bool Parser::BineryOP(Token_type tok) {
        return tok == MUL || tok == DIV || tok == MOD ||
            tok == ADD || tok == SUB || tok == LSHIFT || 
            tok == RSHIFT || tok == LT || tok == LEQL || 
            tok == GT ||tok == GEQL || tok == EQL || tok == NEQL ||
            tok == AND || tok == XOR_OP || tok == OR || 
            tok == AND_OP || tok == OR_OP;
    }   

    inline bool Parser::check(Token_type tok) {
        return cur_token == tok;
    }

    inline bool Parser::checkh(Token_type tok) {
        return next_t().tok_type == tok;
    }

    tokt Parser::next_t() {
        return (cur_index+1 < toks.size())?toks[cur_index+1]:toks[cur_index];
    }

    bool Parser::UnaryOP(Token_type tok) {
        return tok == ADD|| tok == SUB||
         tok == MUL|| tok == AND_OP||tok == NOT_OP|| tok == NOT;
    }

    bool Parser::AssignOP(Token_type tok){
        
    }

    bool Parser::isTerminal(Token_type tok){
        
    }

    int Parser::preced(Token_type op){
        switch (op)
        {
        case MUL:
        case DIV:
        case MOD:
            return 10;
        case ADD:
        case SUB:
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

    inline bool Parser::isLiteral(Token_type tok) {
        return tok == INT||tok == STR||tok == CHAR|| tok == FLOAT||tok == TRUE||tok == FALSE;
    }


}