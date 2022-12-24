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

        NEW,
        FREE,
        IMPORT,
        TYPE,
        CONST,
        FN,
        FOR,
        IN,
        VAR,
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

        INC,
        DEC,

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

        ARROW,
        DOT,
        SCOL,
        COL,
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
    
     __attribute__((flatten)) inline bool is_unary_op(Token_type tok) {
        return tok == INC||tok == DEC||tok == ADD|| tok == SUB||
         tok == MUL|| tok == AND_OP||tok == NOT_OP|| tok == NOT;
    }

     __attribute__((flatten)) inline bool is_litral_val(Token_type tok) {
        return tok == INT||tok == STR||tok == CHAR|| tok == FLOAT||tok == TRUE||tok == FALSE;
    }
}


