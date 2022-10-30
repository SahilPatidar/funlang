#include"../../include/parser/parser.hpp"

namespace parser {
    void Parser::advance() {
        cur_token = toks[++cur_index].tok_type;
    }

}