#include"../../include/parser/parser.hpp"

namespace parser {
    
    void Parser::next() {
        if(cur_index + 1 < toks.size()) {
            ++cur_index;
            cur_token = toks[cur_index].tok_type;
        }
    }

    void Parser::expectErr(int index) {

    }

    void Parser::expectToken(Token_type tok){
        if(toks[cur_index].tok_type == tok){
            next();
        }else {
            expectErr(cur_index);
            next();
        }
    }

    __attribute__((flatten)) inline bool Parser::match2(Token_type t1, Token_type t2) {
        return cur_token == t1 || cur_token == t2;
    }

    
    tokt Parser::next_t() {
        return (cur_index+1 < toks.size())?toks[cur_index+1]:toks[cur_index];
    }

    std::map<Token_type,int> preced_map() {

    }

}