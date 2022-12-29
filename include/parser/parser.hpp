#pragma once

#include<iostream>
#include"Ast.hpp"
#include<map>

using namespace ast;
namespace parser{
    using namespace lex;

    class Parser {   
        tok_t toks;
        uint cur_index;

        // std::string path;
        // std::string file_name;
        Token_type cur_token;
        tokt next_t();
        void next();
        int preced(Token_type op);
        bool BineryOP(Token_type tok);


        AstPtr parseBlockStatement();
        AstPtr parsePointerType();
        AstPtr parseIdentifier();
        AstPtr parseLitral();
        AstPtr parseParenExpr();
        AstPtr parseType();
        AstPtr parseTypeStatm();
        AstPtr parseArrayType();
        AstPtr parseArrayExpr();
        AstPtr parseArrayAccess(AstPtr left); 
        AstPtr parseFor();
        AstPtr parseDotOrArrow(AstPtr left);
        AstPtr parseAssignment(AstPtr left);
        AstPtr parseSecondryExpr(AstPtr left,int precedence);
        AstPtr parsePrimaryExpr(int precedence);
        AstPtr parsePostfixExpr(AstPtr left);
        AstPtr parsePrefixExpr();
        AstPtr parseBineryExpr(AstPtr left, int prev_prece);
        AstPtr parseStruct();
        AstPtr parseStructExpr();
        AstPtr parseReturn();
        AstPtr parseIfStatm();
        AstPtr parseConst();
        AstPtr parseStatement();
        AstPtr parseLetStatm();
        AstPtr parseFuncdef();
        AstPtr parseFuncCall(AstPtr caller_name);
        AstPtr parseTypeValuePair();
        public:
        Parser(tok_t &_toks, int index)
        : toks(_toks), cur_index(index), cur_token(toks[cur_index].tok_type)
        {}
        ~Parser() {}
        AstPtr parse();
    };

}

