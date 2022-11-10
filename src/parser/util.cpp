#include"../../include/parser/parser.hpp"

namespace parser {
    void Parser::advance() {
        cur_index++;
        if(cur_index < toks.size())
           cur_token = toks[cur_index].tok_type;
    }

    Token_type Parser::next() {
        Token_type tok;
        if(cur_index + 1 < toks.size())
            tok = toks[cur_index + 1].tok_type;
        return tok;
    }

}