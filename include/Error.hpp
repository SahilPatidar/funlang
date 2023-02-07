#pragma once

#include"lex/lex.hpp"

namespace err{
    void out(std::string msg, lex::tokt tok){
        std::cerr<<"error:: "<<tok.line+1<<":"<<tok.pos<<" { "<<msg<<" \' "<<tok.data<<" \'"<<" } "<<std::endl;
        //exit(1);
    }
}


