#ifndef PARSER_H
#define PARSER_H

#include"Ast.hpp"

using namespace ast;
namespace parser{
    class Parser {   
        lex::Token_type cur_token;
        lex::tok_t toks;
        int cur_index = 0;
    //    AstPtr NodePtr;
        std::string path;
        std::string file_name;

        void next();
        void advance();
        AstPtr parseBlockStatement();
        AstPtr parseExpression();
        AstPtr IfStatement();
        AstPtr parseProgram();
        public:
        Parser(lex::tok_t& _toks, std::string _path, std::string _file_name)
        :toks(_toks), path(_path), file_name(_file_name) {}
        ~Parser();
        AstPtr parse();

    };

}

#endif