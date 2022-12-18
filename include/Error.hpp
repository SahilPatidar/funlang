#ifndef ERROR_H
#define ERROR_H
#include"lex/lex.hpp"

namespace err{
    void out(std::string msg, lex::tokt tok){
        std::cerr<<"error:"<<tok.line<<" : "<<tok.pos<<msg<<" token type { "<<tok.tok_type<<" }"<<" "<<std::endl;
    }
}


#endif