#pragma once


//#include <cstdio>
#include <iostream>
#include <vector>

namespace lex
{
    enum Token_type
    {
        INT,
        STR,
        CHAR,
        FLOAT,
        NIL,
        IDEN,

        EXTERN,
        WHILE,
        AS,
        IN,
        USE,
        TYPE,
        CONST,
        FN,
        FOR,
        LET,
        RETURN,
        CONTINUE,
        BREAK,
        TRUE,
        FALSE,
        IF,
        ELSE,
        STRUCT,
        ENUM,
        STRING,
        BOOL,
        I8,
        I16,
        I32,
        I64,
        UI8,
        UI16,
        UI32,
        UI64,
        F32,
        F64,

        ASSN,
        PLUS,
        MINUS,
        STAR,
        DIV,
        MOD,
        ASSN_PLUS,
        ASSN_STAR,
        ASSN_MINUS,
        ASSN_DIV,
        ASSN_MOD,


        AND,
        OR,
        NOT,

        EQL,
        NEQL,
        LT,
        GT,
        LEQL,
        GEQL,

        AND_OP,
        OR_OP,
        XOR_OP,
        NOT_OP,
        AND_ASSN,
        OR_ASSN,
        XOR_ASSN,
        NOT_ASSN,

        LSHIFT,
        RSHIFT,
        LSHIFT_ASSN,
        RSHIFT_ASSN,

        DOTDOT,

        ARROW,
        DOT,
        SCOL,
        COL,
        COLCOL,
        COMMA,
        SPC,
        TAB,
        NEWL,

        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        LBRACK,
        RBRACK,

        FEOF,
        INVALID,
        _LAST
    };
    extern const char *token[_LAST];
    struct tokt
    {
        int line;
        int pos;
        std::string data;
        Token_type tok_type;
        tokt(const int &_line, const int &_pos, const std::string &_data, const int &_type)
		:line(_line), pos(_pos),  data(_data), tok_type((Token_type)_type)
	    {}
    };
    typedef std::vector<tokt> tok_t;

    bool tokenizer(const std::string &src, tok_t &toks, int begin, int end);
    
    
}


