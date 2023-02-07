#pragma once

#include<iostream>
#include"Ast.hpp"

using namespace ast;
namespace parser{
    using namespace lex;

    class Parser {   
        tok_t toks;
        uint cur_index;
        int m_preced;
        // std::string path;
        // std::string file_name;
        Token_type cur_token;
        tokt next_t();
        void next();
        AstPtr m_node;
        void dump(std::string msg);
        void dump2(std::string msg);

         bool check(Token_type tok);
         bool checkh(Token_type tok);
        int preced(Token_type op);
        bool BineryOP(Token_type tok);
        bool UnaryOP(Token_type tok);
        bool AssignOP(Token_type tok);
        bool isLiteral(Token_type tok);
        bool isTerminal(Token_type tok);
        bool PreDefType(Token_type tok);


        bool parseBlockStatement();
        bool parseExtern();
        
        bool parseFullExpr();
        bool parseCallExpr();
        bool parsefullArrayexpr();
        bool parsePointerExpr();
        bool parseRefExpr();
        bool parseSemiConsumedExpr();
        bool parseSpecialExpr();
        bool parsePreParenExpr();
        bool parseExpr();
        bool parseBineryLRExpr();
        //bool parseFieldExpr();

        bool parseCastExpr();
        bool parsePathExpr();
        bool parseIdenExp();

        bool parsePointerType();
        bool parseIdentifier();
        bool parseLiteral();
        bool parseParenExpr();
        bool parseType();
        bool parseTypeStatm();
        bool parseArrayType();
        bool parseArrayExpr();
        bool parseArrayAccess(); 
        bool parseFor();
        bool parseWhile();
        bool parseTupleType();
        bool parseDotOrArrow();
        bool parseAssignment();
        bool parseSecondryExpr();
        bool parseUseStatm();
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
        Parser(tok_t &_toks, int index, int prece)
        : toks(_toks), cur_index(index), cur_token(toks[cur_index].tok_type), m_preced(prece)
        {}
        ~Parser() {}
        AstPtr parse();
    };

}

