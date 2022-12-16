#ifndef PARSER_H
#define PARSER_H

#include"Ast.hpp"
#include<map>

using namespace ast;
namespace parser{
    using namespace lex;
    std::map<Token_type,int> preced_map();
    class Parser {   
        Token_type cur_token;
        tok_t toks;
        int cur_index = 0;
        std::map<Token_type,int> m_preced = preced_map();
        std::string path;
        std::string file_name;
        tokt next_t();
        void next();
        void expectErr(int index);
        __attribute__((flatten)) inline void expectToken(Token_type tok);
        __attribute__((flatten)) inline bool match1(Token_type t1);
        __attribute__((flatten)) inline bool match2(Token_type t1, Token_type t2);
        __attribute__((flatten)) inline bool match3(Token_type t1, Token_type t2, Token_type t3);
        AstPtr parseBlockStatement();
        AstPtr parsePointerExpr();
        AstPtr parseIdentifier();
        AstPtr parseLitral();
        AstPtr parseType();
        AstPtr parseTypeDef();
        AstPtr parseArrayType();
        AstPtr parseArrayExpr();
        AstPtr parseArrayAccess(AstPtr left); 
        AstPtr parseFor();
        AstPtr parseEnum();
        AstPtr parseDotOrArrow(AstPtr left);
        AstPtr parseAssignment(AstPtr left);
        AstPtr parseExpression();
        AstPtr parseRUnaryExpr(AstPtr left);
        AstPtr parseLUnaryExpr();
        AstPtr parseBineryExpr(AstPtr left, int prev_prece);
        AstPtr parseStruct();
       // AstPtr parseStructExpr();
        AstPtr parseReturn();
        AstPtr parseTypeCast();
        AstPtr parseIfStatm();
        AstPtr parseConst();
        AstPtr parseStatement();
        AstPtr parseFreeStatm();
        AstPtr parseNewStatm();
        AstPtr parseVarStatm();
        AstPtr parseVarList();
        AstPtr parseFuncdef();
        AstPtr parseFuncCall();
        AstPtr parseArgList();
        AstPtr parseTypeValuePair();
        public:
        Parser(tok_t &_toks, std::string _path, std::string _file_name)
        :toks(_toks), path(_path), file_name(_file_name) {}
        ~Parser();
        AstPtr parse();
    };

}

#endif