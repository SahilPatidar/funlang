#ifndef PARSER_H
#define PARSER_H

#include<vector>
#include<memory>
#include"Ast.hpp"
#include"../lex/lex.hpp"

using namespace ast;
namespace parser{
    class Parser {   
        lex::Token_type cur_token;
        
        public:
        Parser(lex::tok_t& toks, std::string path);
        AstPtr IfStatement();




    };

}

#endif