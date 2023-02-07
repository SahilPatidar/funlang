#include <iostream>
#include <string>
#include "../../include/lex/lex.hpp"
//#include "../../include/Error.hpp"
namespace lex
{
    const char *token[_LAST] = {
        "INT",
        "STR",
        "CHAR",
        "FLOAT",
        "null",
        "IDEN",

        "extern",
        "while",
        "as",
        "in",
        "use",
        "type",
        "const",
        "fn",
        "for",
        "let",
        "return",
        "continue",
        "break",
        "true",
        "false",
        "if",
        "else",
        "struct",
        "enum",
        "string",
        "bool",
        "i8",
        "i16",
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
        "*=",
        "-=",
        "/=",
        "%=",

        // "++",
        // "--",

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

        "..",

        "->",
        ".",
        ";",
        ":",
        "::",
        ",",
        "SPC",
        "TAB",
        "NEWL",

        "(",
        ")",
        "{",
        "}",
        "[",
        "]",

        "<FEOF>",
        "<INVALID>"
        };

    #define CUR (src[i])
    #define NXT (i < str_len?src[i+1]:0)
    #define PRV (str_len > 0&&i > 0?src[i-1]:0)
    Token_type get_keyword(std::string &src);
     bool get_operator(const std::string &src, Token_type &op_type, int &i);
    std::string get_string(const std::string &src, int &i);
    bool get_const_string(const std::string &src, int &i, char &quote, std::string &str);
    bool get_num(const std::string &src, int &i, int base, std::string &num, Token_type &type);
    

    bool tokenizer(const std::string &src, tok_t &toks,int begin, int end){
        int i = begin;
        bool comment_line = false;
        bool comment_block = false;
        int line = 0;
        int str_len = src.size();
        int start_pos = 0;
        int line_start = 0;
        while(i < end){
            start_pos = i;
            if(CUR=='\n'){
                ++line;
                line_start = i+1;
            }

            if(comment_line){
                if(CUR == '\n')comment_line=false;
                ++i;
                continue;
            }
            
            if(isspace(src[i])){
                i++;
                continue;
            }
            if(CUR == '*' && NXT == '/'){
                if(!comment_block){
                    printf("wrong comment symbol :: %d", i);
                }
                comment_block = false;
                i+=2;
                continue;
            }
            if(CUR == '/' && NXT == '*'){
                comment_block = true;
                i+=2;
                continue;
            }
            if(comment_block){
                i++;
                continue;
            }
            if(CUR == '/'&& NXT == '/'){
                comment_line = true;
                i++;
                continue;
            }
            if(isalpha(src[i])&&!isalnum(PRV)&&!isalnum(PRV)&&PRV != '\''&&PRV != '\"'&&PRV!=')') {

                std::string str = get_string(src, i);

                if(str == ""){
                    return false;
                }
                Token_type tok_name = get_keyword(str);
                toks.push_back(tokt(line, i - line_start, str, tok_name));
                continue;
            }

            if(isdigit(src[i])){
                int base = 10;
                Token_type type = INT;
                std::string str;
                if(!get_num(src, i, base, str, type)){
                    printf("error: number\n");
                    return false;
                }
                toks.push_back(tokt(line, i - line_start, str ,type));
                continue;

            }

            if(CUR == '\"'||CUR == '\'') {
                std::string str;
                char quote = '\"';
                if(!get_const_string(src, i, quote, str)){
                    printf("error in const string %d\n",i);
                    return false;
                }
                toks.push_back(tokt(line, i - line_start , str, quote=='\"'?STR:CHAR));
                continue;
            }
            Token_type type = INVALID;
            if(get_operator(src, type, i)){
                toks.push_back(tokt(line, i - line_start, token[type], type));
                continue;
            }
            std::cout<<"error :: expected token "<<src[i]<<std::endl;
            exit(1);
        }
        toks.push_back(tokt(line, i - line_start , token[FEOF], FEOF));
        return true;
    }
    
    Token_type get_keyword(std::string &src) {
        if(src == token[FOR])return FOR;
        if(src == token[EXTERN])return EXTERN;
        if(src == token[WHILE])return WHILE;
        if(src == token[IF])return IF;
        if(src == token[AS])return AS;
        if(src == token[ELSE])return ELSE;
        if(src == token[FN])return FN;
        if(src == token[STRUCT])return STRUCT;
        if(src == token[NIL])return NIL;
        if(src == token[CONTINUE])return CONTINUE;
        if(src == token[BREAK])return BREAK;
        if(src == token[TRUE])return TRUE;
        if(src == token[TYPE])return TYPE;
        if(src == token[RETURN])return RETURN;
        if(src == token[FALSE])return FALSE;
        if(src == token[CONST])return CONST;
        if(src == token[LET])return LET;
        if(src == token[IN])return IN;
        if(src == token[ENUM])return ENUM;
        if(src == token[USE])return USE;
        if(src == token[STRING])return STRING;
        if(src == token[BOOL])return BOOL;
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

    std::string  get_string(const std::string &src, int &i){
        int str_len = src.size();
        std::string str;
        while (i < str_len)
        {   
            if(!isalnum(src[i]) && CUR != '_'){
               break;
            }
            str.push_back(src[i]);
            ++i;
        }
        return str;
    }

    bool get_const_string(const std::string &src, int &i, char &quote, std::string &str){
        quote = CUR;
        int start_pos = i;
        ++i;
        int str_len = src.size();
        int back_slash = 0;
        while(i < str_len){
            if(CUR == '\\') {
                ++back_slash;
                str.push_back(CUR);
                ++i;
                continue;
            }
            if(CUR == quote && back_slash%2 == 0)
                break;
            
            str.push_back(CUR);
             ++i;
            if(quote == '\''){
                if(CUR != quote){
                    printf("error: quote not matching\n");
                    return false;
                }
                break;
            }
            back_slash = 0;
        }
        // if(CUR != quote){
        //     i = start_pos;
        //     return false;
        // }
        ++i;
        return true;
    };

    bool get_num(const std::string &src, int &i, int base, std::string &num, Token_type &type){
        int str_len = src.size();
        bool hex = false;
        int frist_digit = i;
        int dot_pos = -1;
        while(i < str_len){
            const char cur = CUR;
            const char nxt = NXT;
            if(i == frist_digit && cur == '0' && (nxt == 'x'||nxt == 'X')){
                hex = true;
                base = 16;
                num.push_back(cur);
                num.push_back(nxt);
                i+=2;
                continue;
            }
            switch(cur){
                case '0':
                {
                    break;
                }
                case 'A':
                case 'a':
                case 'B':
                case 'b':
                case 'C':
                case 'c':
                case 'D':
                case 'd':
                case 'E':
                case 'e':
                case 'F':
                case 'f':
                {
                    if(hex)break;
                    goto fail;
                }
                case '1':
                    break;
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                {
                    if(hex||base > 2)break;
                    goto fail;                 
                }
                case '7':
                case '8':
                case '9':
                {
                    if(hex||base >= 8)break;
                    goto fail;
                }
                case '.':
                {
                    if(base != 10 || hex){
                        fprintf(stderr,"encountered dot character but base is not 10\n");
                        return false;
                    } else if(dot_pos == -1) {
                        if(nxt >= '0' && nxt <='9'){
                          dot_pos = i;
                          type = FLOAT;
                        }else{
                            goto fail;
                        }
                    }else{
                        printf("encountered double dot in single number\n");
                        return false;
                    }
                    break;
                } 
                default:
                {
                    fail:
                        if(isalnum(cur)){
                            printf("invalid number %c  %c\n",cur,nxt);
                            return false;
                        }else{
                            return true;
                        }
                }
            }

            num.push_back(cur);
            ++i;
        }
        return true;
    }

    #define SET(type) \
      op_type = type; \
      break                                 

    bool get_operator(const std::string &src, Token_type &op_type, int &i) {
        int str_len = src.size();
        int first_op = i;
        switch(CUR){
            case '+':
            {
                if(i < str_len - 1){
                    // if(NXT == '+'){
                    //     ++i;
                    //    SET(INC);
                    // }else 
                    if(NXT == '='){
                        ++i;
                        SET(ASSN_PLUS);
                    }
                }
               SET(PLUS);
            }
            case '-':
             {
                if(i < str_len - 1){
                    // if(NXT == '-'){
                    //     ++i;
                    //    SET(DEC);
                    // }else 
                    if(NXT == '='){
                        ++i;
                       SET(ASSN_MINUS);
                    }else if(NXT == '>'){
                        ++i;
                        SET(ARROW);
                    }
                }
                SET(MINUS);
            }
            case '%':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASSN_MOD); 
                    }
                }
                SET(MOD);
            }
            case '*':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASSN_STAR);
                    }
                }
                SET(STAR);
            }
            case '=':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(EQL);
                    }
                }
                SET(ASSN);
            }
            case '/':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(ASSN_DIV);
                    }
                }
                SET(DIV);
            }
            case '&':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(AND_ASSN);
                    }else if(NXT == '&'){
                        ++i;
                        SET(AND);
                    }
                }
                SET(AND_OP);
            }
            case '|':
             {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(OR_ASSN);
                    }else if(NXT == '|'){
                        ++i;
                        SET(OR);
                    }
                }
                SET(OR_OP);
            }
            case '!':
             {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(NEQL);
                    }
                }
                SET(NOT);
            }
            case '~':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(NOT_ASSN);
                    }
                }
                SET(NOT_OP);
            }
            case '<':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(LEQL);
                    }else if(NXT == '<'){
                        
                        if(i < str_len - 1){
                            ++i;
                            if(NXT == '='){
                                SET(LSHIFT_ASSN);
                            }
                        }
                        SET(LSHIFT);
                    }
                }
                SET(LT);
            }
            case '>':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(GEQL);
                    }else if(NXT == '<'){
                        ++i;
                        if(i < str_len - 1){
                            if(NXT == '='){
                                SET(RSHIFT_ASSN);
                            }
                        }
                        SET(RSHIFT);
                    }
                }
                SET(GT);
            }
            case '^':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        ++i;
                        SET(XOR_ASSN);
                    }
                }
                SET(XOR_OP);
            }
            case ':':
                if(i < str_len - 1){
                    if(NXT == ':'){
                        ++i;
                        SET(COLCOL);
                    }
                }
                SET(COL);
            case ',':
                SET(COMMA);
            case ';':
                SET(SCOL);
            case '\t':
                SET(TAB);
            case '\n':
                SET(NEWL);
            case ' ':
                SET(SPC);
            case '.':
            {
                if(i < str_len - 1){
                    if(NXT == '.'){
                        ++i;
                                SET(DOTDOT);

                    }
                }
                SET(DOT);
            }
            case '[':
                SET(LBRACK);
            case ']':
                SET(RBRACK);
            case '(':
                SET(LPAREN);
            case ')':
                SET(RPAREN);
            case '{':
                SET(LBRACE);
            case '}':
                SET(RBRACE);


            default:
                return false;

        }
        ++i;
        return true;
    }

}
