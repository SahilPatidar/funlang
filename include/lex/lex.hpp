#ifndef LEX_HPP
#define LEX_HPP

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
        IDEN,

        IMPORT,
        TYPE,
        CONST,
        FN,
        FOR,
        VAR,
        WHILE,
        RETURN,
        CONTINUE,
        BREAK,
        NIL,
        TRUE,
        FALSE,
        IF,
        ELIF,
        ELSE,
        STRUCT,
        ENUM,
        STRING,
        VOID,
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
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        ASSN_ADD,
        ASSN_MUL,
        ASSN_SUB,
        ASSN_DIV,
        ASSN_MOD,

        V_INC,
        V_DEC,
        INC_V,
        DEC_V,

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
        COMP_OP,
        AND_ASSN,
        OR_ASSN,
        XOR_ASSN,
        COMP_ASSN,

        LSHIFT,
        RSHIFT,
        LSHIFT_ASSN,
        RSHIFT_ASSN,

        ARROW,
        DOT,
        SCOL,
        COL,
        COMMA,
        SPC,
        TAB,
        NEWL,

        LBRACE,
        RBRACE,
        LPAREN,
        RPAREN,
        LBRACK,
        RBRACK,

        FEOF,
        INVALID,
        _LAST
    };
    extern const char *token[_LAST];
    struct tok
    {
        int line;
        int pos;
        std::string data;
        Token_type tok_type;
        tok(const int &_line, const int &_pos, const std::string &_data, const int &_type)
		:line(_line), pos(_pos),  data(_data), tok_type((Token_type)_type)
	    {}
    };
    typedef std::vector<tok> tok_t;

    bool tokenizer(const std::string &src, tok_t &tokes, int begin, int end);

}

#endif
