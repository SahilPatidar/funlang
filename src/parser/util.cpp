
#include"../../include/parser/parser.hpp"

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

    tokt Parser::next_t() {
        return (cur_index+1 < toks.size())?toks[cur_index+1]:toks[cur_index];
    }


}