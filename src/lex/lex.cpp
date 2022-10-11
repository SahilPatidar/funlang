#include <iostream>
#include <string>
#include "../../include/lex/lex.hpp"
#include "../../include/Error.hpp"
namespace lex
{
    extern const char *token[_LAST] = {
        "INT",
        "STR",
        "CHAR",
        "FLOAT",
        "IDEN",

        "import",
        "type",
        "const",
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
        "*=",
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

        // "()",
        // "[]",
        // "{}",

        "->",
        ".",
        ";",
        ":",
        ",",
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

    #define CUR (src[i])
    #define NXT (i < str_len?src[i+1]:0)
    #define PRV (str_len > 0&&i > 0?src[i-1]:0)
    int get_keyword(std::string &src);
    std::string get_string(std::string &src, int &i);

    bool tokenizer(const std::string &src, tok_t& toks,int begin, int end){
        ssize_t i = begin;
        bool comment_line = false;
        bool comment_block = false;

        size_t str_len = src.size();
        int start_pos = 0;
        while(i < end){
            start_pos = i;
            if(comment_line){
                if(CUR == '\n')comment_line=false;
                ++i;
                continue;
            }
            if(CUR=='\n'){

            }
            if(isspace(src[i])){
                i++;
                continue;
            }
            if(CUR == '*' && NXT == '/'){
                if(!comment_block){
                    fprintf(stderr, "wrong comment symbol :: %d", i);
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
            }

            //string
            if(isalpha(src[i])&&!isalnum(PRV)) {

            }

            if(isdigit(src[i])){
                int base = 10;
                Token_type type;
                std::string str;
                if(!get_num(src, i, base, str, type)){
                    printf("error: number\n");
                    return false;
                }
                toks.emplace_back(i - str.size(),str,type);
                continue;

            }

            if(CUR == '\"'||CUR == '\'') {
                std::string str;
                char quote = '\"';
                if(!get_const_string(src, i, quote, str)){
                    printf("error in const string %d\n",i);
                }
                toks.emplace_back(i - str.length(),str, quote=='\"'?STR:CHAR);
                continue;
            }
            Token_type type = INVALID;
            if(get_operator(src, type, i)){
                std::string opr;
                toks.emplace_back(i - start_pos, opr, type);
                continue;
            }
        }

        return true;
    }
    
    int get_keyword(std::string &src) {
        if(src == token[FOR])return FOR;
        if(src == token[TYPE])return TYPE;
        if(src == token[IF])return IF;
        if(src == token[ELIF])return ELIF;
        if(src == token[ELSE])return ELSE;
        if(src == token[FN])return FN;
        if(src == token[WHILE])return WHILE;
        if(src == token[STRUCT])return STRUCT;
        if(src == token[NIL])return NIL;
        if(src == token[CONTINUE])return CONTINUE;
        if(src == token[BREAK])return BREAK;
        if(src == token[TRUE])return TRUE;
        if(src == token[FALSE])return FALSE;
        if(src == token[CONST])return CONST;
        if(src == token[VAR])return VAR;
        if(src == token[ENUM])return ENUM;
        if(src == token[STRUCT])return STRUCT;
        if(src == token[IMPORT])return IMPORT;
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

    bool get_const_string(const std::string &src, ssize_t &i, char quote, std::string &str){
        quote = CUR;
        int start_pos = i;
        ++i;
        int str_len = src.size();
        int back_slash = 0;
        while(i < str_len){
            if(CUR == '\\') {
                back_slash++;
                str.push_back(CUR);
                continue;
            }
            if(CUR == quote && back_slash%2 == 0)
                break;
            if(quote == '\''){
                if(CUR != quote){
                    return false;
                }
                break;
            }
            str.push_back(CUR);
            back_slash = 0;
            i++;
        }
        if(CUR != quote){
            i = start_pos;
            return false;
        }
        ++i;
        return true;
    };

    bool get_num(const std::string &src, ssize_t &i, int base, std::string &num, Token_type &type){
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
                        printf("encountered dot character but base is not 10\n");
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
                } 
                default:
                {
                    fail:
                        if(isalnum(cur)){
                            printf("invalid number\n");
                            return false;
                        }else{

                        }
                }
            }

            num.push_back(cur);
            ++i;
        }
        return true;
    }


    bool get_string( ) {

    }

    #define SET(type) \
      op_type = type;       \
      ++i;                  \
      break                                 

    bool get_operator(const std::string &src, Token_type &op_type, ssize_t &i) {
        int str_len = src.size();
        int first_op = i;
        switch(CUR){
            case '+':
            {
                if(i < str_len - 1){
                    if(NXT == '+'){
                       SET(V_INC);
                    }else if(NXT == '='){
                        SET(AND_ASSN);
                    }
                }
               SET(ADD);
            }
            case '-':
             {
                if(i < str_len - 1){
                    if(NXT == '-'){
                       SET(V_DEC);
                    }else if(NXT == '='){
                       SET(ASSN_SUB);
                    }else if(NXT == '>'){
                        SET(ARROW);
                    }
                }
                SET(SUB);
            }
            case '%':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(ASSN_MOD); 
                    }
                }
                SET(MOD);
            }
            case '*':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(ASSN_MUL);
                    }
                }
                SET(MUL);
            }
            case '=':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(EQL);
                    }
                }
                SET(ASSN);
            }
            case '/':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(ASSN_DIV);
                    }
                }
                SET(DIV);
            }
            case '&':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(AND_ASSN);
                    }else if(NXT == '&'){
                        SET(AND);
                    }
                }
                SET(AND_OP);
            }
            case '|':
             {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(OR_ASSN);
                    }else if(NXT == '|'){
                        SET(OR);
                    }
                }
                SET(OR_OP);
            }
            case '!':
             {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(NEQL);
                    }
                }
                SET(NOT);
            }
            case '~':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(COMP_ASSN);
                    }
                }
                SET(COMP_OP);
            }
            case '<':
            {
                if(i < str_len - 1){
                    if(NXT == '='){
                        SET(LEQL);
                    }else if(NXT == '<'){
                        ++i;
                        if(i < str_len - 1){
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
                        SET(XOR_ASSN);
                    }
                }
                SET(XOR_OP);
            }
            case ':':
                SET(COL);
            case ',':
                SET(COMMA);
            case ';':
                SET(SCOL);
            case '/t':
            case ' ':

            case '.':
                SET(DOT);
            case '[':
                SET(LBRACK);
            case ']':
                SET(RBRACK);
            case '(':
                SET(LBRACE);
            case ')':
                SET(RBRACE);
            case '{':
                SET(LPAREN);
            case '}':
                SET(LPAREN);


            default:
                return false;

        }
        
        return true;
    }

}
