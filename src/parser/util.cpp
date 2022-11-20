#include"../../include/parser/parser.hpp"

namespace parser {
    void Parser::advance() {
        if(cur_index + 1 < toks.size()) {
            ++cur_index;
            cur_token = toks[cur_index].tok_type;
        }
    }

    void Parser::expectToken(Token_type tok){
        if(toks[cur_index].tok_type == tok){
            advance();
        }else {
            //err
            advance();
        }
    }
    Token_type Parser::next() {
        return (cur_index+1 < toks.size())?toks[cur_index+1].tok_type:toks[cur_index].tok_type;
    }

}