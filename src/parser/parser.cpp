#include"../../include/parser/parser.hpp"

namespace parser {  
    AstPtr Parser::parse() {
        
    }

    AstPtr Parser::parseStatement() {
        AstPtr statm;
        switch(cur_token){
            case FOR:
                statm = parseFor();
            case IF:
                statm = parseIf();
            case WHILE:
                statm = parseWhile();
            case VAR:
                statm = parseVar();
            case RETURN:
                statm = parseReturn();
        }

        return statm;
    }

    AstPtr Parser::parseFor() {
        
    }
}

