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
        tokt next();
        void advance();
        void expectErr(int index);
        void expectToken(Token_type tok);
        AstPtr parseBlockStatement();
        AstPtr parseIdentifier();
        AstPtr parseType();
        AstPtr parseInt();
        AstPtr parseString();
        AstPtr parseFloat();
        AstPtr parseBool();
        AstPtr parseOp();
        AstPtr parseArrayType();
        AstPtr parseFor();
        AstPtr parseEnum();
        AstPtr parseParenExpr();
        AstPtr parseAssignment(AstPtr left);
        AstPtr parseExpression();
        AstPtr parseUnaryExpr();
        AstPtr parseBineryExpr(AstPtr left, int prev_prece);
        AstPtr parseStruct();
        AstPtr parseReturn();
        AstPtr parseTypeCast();
        AstPtr parseIfStatm();
        AstPtr parseConst();
        AstPtr parseStatement();
        AstPtr parseVarStatm();
        AstPtr parseVarList();
        AstPtr parseFuncdef();
        AstPtr parseFuncCall();
        AstPtr parseArgList();
        AstPtr parseParamList();
        public:
        Parser(tok_t &_toks, std::string _path, std::string _file_name)
        :toks(_toks), path(_path), file_name(_file_name) {}
        ~Parser();
        AstPtr parse();
    };

}

#endif