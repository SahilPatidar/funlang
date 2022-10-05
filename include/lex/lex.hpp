#ifndef LEX_HPP
#define LEX_HPP

#include <cstdio>
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
        NOT_OP,
        AND_ASSN,
        OR_ASSN,
        XOR_ASSN,
        NOT_ASSN,

        LSHIFT,
        RSHIFT,
        LSHIFT_ASSN,
        RSHIFT_ASSN,

        SUBS,

        PreVA,
        PostVA,

        DOT,
        COL,
        SCOPE,
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

    struct tok
    {
        int pos;
        std::string data;
        Token_type tok;
    };
    typedef std::vector<tok> tok_t;

    tok_t tokenizer(std::string &src, tok_t&tokes);

}

#endif
