#ifndef PARSER_H
#define PARSER_H

#include"Ast.hpp"

using namespace ast;
namespace parser{
    using namespace lex;
    class Parser {   
        Token_type cur_token;
        tok_t toks;
        int cur_index = 0;
        std::string path;
        std::string file_name;
        Token_type next();
        void advance();
        AstPtr parseBlockStatement();
        AstPtr parseIdentifier();
        AstPtr parseType();
        AstPtr parseInt();
        AstPtr parseString();
        AstPtr parseFloat();
        AstPtr parseBool();
        AstPtr parseOp();
        AstPtr parseArray();
        AstPtr parseFor();
        AstPtr parseWhile();
        AstPtr parseEnum();
        AstPtr parseStruct();
        AstPtr parseReturn();
        AstPtr parseTypeCast();
        AstPtr parseExpression();
        AstPtr parseIf();
        AstPtr parseElif();
        AstPtr parseConst();
        AstPtr parseStatement();
        AstPtr parseVar();
        AstPtr parseFuncdef();
        public:
        Parser(lex::tok_t& _toks, std::string _path, std::string _file_name)
        :toks(_toks), path(_path), file_name(_file_name) {}
        ~Parser();
        AstPtr parse();
    };

}

#endif