#include <iostream>
#include <string>
#include "../../include/lex/lex.hpp"

namespace lex
{
    extern const char *token[_LAST] = {
        "INT",
        "STR",
        "CHAR",
        "FLOAT",
        "IDEN",

        "const"
        "fn",
        "for",
        "var",
        "while",
        "return",
        "continue",
        "break",
        "nil",
        "true",
        "false",
        "if",
        "elif",
        "else",
        "struct",
        "enum",
        "string",
        "i8",
        "i16"
        "i32",
        "i64",
        "ui8",
        "ui16",
        "ui32",
        "ui64",
        "f32", 
        "f64",

        "=",
        "+",
        "-",
        "*",
        "/",
        "%",
        "+=",
        "-=",
        "/=",
        "%=",

        "x++",
        "x--",
        "++x",
        "--x",

        "&&",
        "||",
        "!",

        "==",
        "!=",
        "<",
        ">",
        "<=",
        ">=",

        "&",
        "|",
        "^",
        "~",
        "&=",
        "|=",
        "^=",
        "~=",

        "<<",
        ">>",
        "<<=",
        ">>=",

        "()",
        "[]",
        "{}",

        "...",

        ".",
        ";",
        ":",
        ","
        "SPC",
        "TAB",
        "NEWL",

        "(",
        ")"
        "{",
        "}",
        "[",
        "]",

        "<FEOF>",
        "<INVALID>"};

    #define CUR(src) (src[i])
    #define NXT(src) (i < end?src[i+1]:0)
    #define PRV(src) (str_len > 0&&i > 0?src[i-1]:0)
    int get_keyword(std::string &src);
    std::string get_string(std::string &src, int &i);
    tok_t tokenizer(const std::string &src, tok_t& toks,int begin, int end){
        ssize_t i = begin;
        bool comment_line = false;
        bool comment_block = false;
        size_t str_len = src.size();

        while(i < end){
            if(comment_line){
                if(CUR(src) == '\n')comment_line=false;
                ++i;
                continue;
            }
            if(isspace(src[i])){
                i++;
                continue;
            }
            if(CUR(src) == '*' && NXT(src) == '/'){
                if(!comment_block){
                    fprintf(stderr, "wrong comment symbol :: %d", i);
                }
                comment_block = false;
                i+=2;
                continue;
            }
            if(CUR(src) == '/' && NXT(src) == '*'){
                comment_block = true;
                i+=2;
                continue;
            }
            if(comment_block){
                i++;
                continue;
            }
            if(CUR(src) == '/'&& NXT(src) == '/'){
                comment_line = true;
                i++;
            }

            //string
            if(isalpha(src[i])&&!isalnum(PRV(src))) {

            }

            //const string
            if(isalpha(src[i])&&!isalnum(PRV(src))) {

            }

        }
        
    }

    int get_keyword(std::string &src) {
        if(src == token[FOR])return FOR;
        if(src == token[IF])return IF;
        if(src == token[ELIF])return ELIF;
        if(src == token[ELSE])return ELSE;
        if(src == token[FN])return FN;
        if(src == token[WHILE])return WHILE;
        if(src == token[STRUCT])return STRUCT;
        if(src == token[NIL])return NIL;
        if(src == token[CONTINUE])return CONTINUE;
        if(src == token[TRUE])return TRUE;
        if(src == token[FALSE])return FALSE;
        if(src == token[CONST])return CONST;
        if(src == token[VAR])return VAR;
        if(src == token[STRING])return STRING;
        if(src == token[I8])return I8;
        if(src == token[I16])return I16;
        if(src == token[I32])return I32;
        if(src == token[I64])return I64;
        if(src == token[UI8])return UI8;
        if(src == token[UI16])return UI16;
        if(src == token[UI32])return UI32;
        if(src == token[UI64])return UI64;
        if(src == token[F32])return F32;
        if(src == token[F64])return F64;
        return IDEN;
    }

    std::string get_string(std::string &src, int &i){
        while(i < src.size()){
            
        }
    }



}
