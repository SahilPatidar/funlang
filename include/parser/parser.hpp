#pragma once

#include<iostream>
#include"Ast.hpp"

using namespace ast;
namespace parser{
    using namespace lex;

    class Parser {   
        tok_t toks;
        uint cur_index;
        int m_preced = 0;
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
        AstPtr parseLiteral();
        //AstPtr parseParenExpr();
        AstPtr parseType();
        AstPtr parseTypeStatm();
        AstPtr parseArrayType();
        AstPtr parseArrayExpr();
        AstPtr parseArrayAccess(AstPtr left); 
        AstPtr parseFor();
        AstPtr parseTupleType();
        AstPtr parseDotOrArrow(AstPtr left);
        AstPtr parseAssignment(AstPtr left);
        AstPtr parseSecondryExpr(AstPtr left);
        AstPtr parsePrimaryExpr();
        AstPtr parsePostfixExpr(AstPtr left);
        AstPtr parsePrefixExpr();
        AstPtr parseBineryExpr(AstPtr left, int prev_prece);
        AstPtr parseStruct();
        AstPtr parseStructExpr(AstPtr left);
        AstPtr parseReturn();
        AstPtr parseIfStatm();
        AstPtr parseConst();
        AstPtr parseStatement();
        AstPtr parseLetStatm();
        AstPtr parseFuncdef();
        AstPtr parseFuncCall(AstPtr sig);
        AstPtr parseTypeValuePair();
        public:
        Parser(tok_t &_toks, int index)
        : toks(_toks), cur_index(index), cur_token(toks[cur_index].tok_type)
        {}
        ~Parser() {}
        AstPtr parse();
    };

}

