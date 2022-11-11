#include"../../include/parser/parser.hpp"

namespace parser {  
    AstPtr Parser::parse() {
        while(cur_token != FEOF){
            advance();
        }
        return ;
    }

    AstPtr Parser::parseExpression() {
        AstPtr expr;
        while(cur_token != SCOL){

        }
    }

    //============------------statement------------================

    AstPtr Parser::parseStatement() {
        AstPtr statm;
        switch(cur_token){
            case FOR:
                statm = parseFor();
                break;
            case IF:
                statm = parseIf();
                break;
            case WHILE:
                statm = parseWhile();
                break;
            case VAR:
                statm = parseVar();
                break;
            case RETURN:
                statm = parseReturn();
                break;
            case CONTINUE:
                statm = std::make_shared<ContinueState>(cur_token);
                break;
            case CONST:
            case BREAK:
                statm = std::make_shared<ContinueState>(cur_token);
                break;
            case STRUCT:
                statm = parseEnum();
                break;
            case ENUM:
                statm = parseEnum();
                break;
            default:
                break;
        }
        return statm;
    }

   
    AstPtr Parser::parseIf() {
        Token_type tok = cur_token;
        advance();
        AstPtr condition;
        AstPtr ifbody;
        AstPtr elsebody;
        AstPtr elifbody;
        if(cur_token != LBRACE){

        }

        advance();
        condition = parseExpression();

        if(cur_token != RBRACE){

        }
        advance();

        if(cur_token != LPAREN){

        }
        
        advance();
        ifbody = parseBlockStatement();

        if(cur_token != RPAREN){

        }
        advance();

        return std::make_shared<IfStatement>(condition, ifbody, elifbody, elsebody);

    }

    AstPtr Parser::parseVar() {

    }

    AstPtr Parser::parseWhile() {
        Token_type tok =cur_token;
        advance();
        AstPtr expr;
        AstPtr body;
        if(cur_token != LBRACE){

        }
        advance();

        expr = parseExpression();

        if(cur_token != RBRACE){

        }
        advance();

        if(cur_token != LPAREN){

        }
        advance();

        body = parseBlockStatement();

        if(cur_token != RPAREN){

        }
        advance();
        
        return std::make_shared<WhileLoopState>(expr, body, tok);
    }

    AstPtr Parser::parseFor() {
        Token_type tok = cur_token;
        advance();
        std::vector<AstPtr> var = {};

        while(cur_token != SCOL){
            AstPtr vr = parseVar();
            if(!vr){
                std::cerr<<"invalid var"<<std::endl;
            }
            if(cur_token != COMMA && cur_token != SCOL){
                std::cerr<<"invalid expression "<<std::to_string(cur_token)<<std::endl;
                exit(EXIT_FAILURE);
            }
            advance();
            var.push_back(vr); 
        }

        AstPtr condi = parseExpression();

        if(cur_token != SCOL){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
            exit(EXIT_FAILURE);
        }

        advance();
        AstPtr expr = parseExpression();


        return std::make_shared<ForLoopState>(var, condi, expr, tok);
    }
}

