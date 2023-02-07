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
        AstPtr m_node;
        inline bool check(Token_type tok);
        inline bool checkh(Token_type tok);
        int preced(Token_type op);
        bool BineryOP(Token_type tok);
        bool UnaryOP(Token_type tok);
        bool AssignOP(Token_type tok);
        inline bool isLiteral(Token_type tok);
        bool isTerminal(Token_type tok);


        bool parseBlockStatement();
        bool parseExtern();

        bool parseExpr1();
        bool parseExpr2();
        bool parseExpr3();
        bool parseExpr4();
        bool parseExpr5();
        bool parseExpr6();
        bool parseExpr7();
        bool parseExpr8();
        bool parseRefExpr();
        bool parsePointerExpr();

        bool parsePointerType();
        bool parseIdentifier();
        bool parseLiteral();
        bool parseIdenExpr();
        bool parseParenExpr();
        bool parseSpecialType();
        bool parseType();
        bool parseTypeStatm();
        bool parseArrayType();
        bool parseArrayExpr();
        bool parseArrayAccess(); 
        bool parseFor();
        bool parseTupleType();
        bool parseDotOrArrow();
        bool parseForExpression();
        bool parseParenExpr();
        bool parseAssignment();
        bool parseSecondryExpr();
        bool parseRangeExpr();
        bool parsePrimaryExpr();
        bool parsePrefixExpr();
        bool parseBineryExpr(int prev_prece);
        bool parseStruct();
        bool parseStructExpr();
        bool parseReturn();
        bool parseIfStatm();
        bool parseConst();
        bool parseStatement();
        bool parseLetStatm();
        bool parseFuncdef();
        bool parseFuncCall();
        bool parseTypeValuePair();
        public:
        Parser(tok_t &_toks, int index)
        : toks(_toks), cur_index(index), cur_token(toks[cur_index].tok_type)
        {}
        ~Parser() {}
        AstPtr parse();
    };

}

