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

        "let",
        "const"
        "fn",
        "for",
        "in",
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
    
    tok_t tokenizer(std::string &src, tok_t& toks,int begin, int end){
        ssize_t i = begin;
        bool comment_line = false;
        bool comment_block = false;
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
                    fprintf(stderr,"wrong comment symbol :: %d",i);
                }
                comment_block = false;
                i+=2;
                continue;
            }
            if(CUR(src) == '/'&& NXT(src) == '*'){
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
            if()

        }
        
    }


    bool is

}
