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

    AstPtr Parser::parseType() {
        AstPtr type;
        switch(cur_token){
            case I8:
            case I16:
            case I32:
            case I64:
            case UI8:
            case UI16:
            case UI32:
            case UI64:
                type = std::make_shared<IntType>(cur_token);
                break;
            case F32:
            case F64:
                type = std::make_shared<FloatType>(cur_token);
                break;
            case STRING:
                type = std::make_shared<StringType>(cur_token);
            case BOOL:
                type = std::make_shared<BoolType>(cur_token); 

        }
        return type;
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
                statm = parseConst();
                break;

            case BREAK:
                statm = std::make_shared<BreakState>(cur_token);
                break;

            case STRUCT:
                statm = parseStruct();
                break;

            case ENUM:
                statm = parseEnum();
                break;

            case FN:
                statm = parseFuncdef();
                break;

            default:
                break;
        }
        return statm;
    }

    AstPtr Parser::parseFuncCall() {
        Token_type tok = cur_token;
        AstPtr name;
        std::vector<AstPtr> args;
        advance();

        name = parseIdentifier();

        if(cur_token != LBRACE){
            std::cerr<<"error:invalid expression "<<token[cur_token]<<std::endl;
        }
        advance();

        while(cur_token){

        }

        if(cur_token != LBRACE){
            std::cerr<<"error:invalid expression "<<token[cur_token]<<std::endl;
        }
        advance();
        
        return std::make_shared<FunctionCall>(tok, name, args);
    }


    AstPtr Parser::parseFuncdef(){
        Token_type tok = cur_token;
        AstPtr name;
        std::vector<param>parameter;
        AstPtr retype;
        AstPtr body;

        name = parseIdentifier();
        if(cur_token != LBRACE) {
            std::cerr<<"error:invalid expression "<<token[cur_token]<<std::endl;
        }
        advance();



        if(cur_token != RBRACE) {
            std::cerr<<"error:invalid expression "<<token[cur_token]<<std::endl;
        }
        advance();

        retype = parseType();

         if(cur_token != LPAREN) {
            std::cerr<<"error:invalid expression "<<token[cur_token]<<std::endl;
        }
        advance();

        body = parseBlockStatement();

        if(cur_token != RPAREN) {
            std::cerr<<"error:invalid expression "<<token[cur_token]<<std::endl;
        }
        advance();

        return std::make_shared<FunctionDef>(tok, name, parameter, retype, body);
    }


    AstPtr Parser::parseReturn() {
        Token_type tok = cur_token;
        advance();
        AstPtr val;
        val = parseExpression();
        if(cur_token != SCOL){
            exit(EXIT_FAILURE);
        }
        advance();
        return std::make_shared<ReturnState>(tok, val);
    }

    AstPtr Parser::parseElif() {
        Token_type tok = cur_token;
        advance();

        AstPtr condition, body;

        condition = parseExpression();

        if( cur_token != LPAREN ){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
            exit(EXIT_FAILURE);
        }
        advance();

        body = parseBlockStatement();
        
        if( cur_token != RPAREN ){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
            exit(EXIT_FAILURE);
        }
        advance();

        return std::make_shared<ElifStatement>(tok, condition, body);
    }
   
    AstPtr Parser::parseIf() {
        Token_type tok = cur_token;
        advance();
        AstPtr condition;
        AstPtr ifbody;
        AstPtr elsebody;
        condition = parseExpression();

        if( cur_token != LPAREN ){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
            exit(EXIT_FAILURE);
        }

        advance();

        ifbody = parseBlockStatement();
        
        if( cur_token != RPAREN ){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
            exit(EXIT_FAILURE);
        }
            
        advance();

        std::vector<AstPtr> elifbody;

        while(cur_token == ELIF){
            AstPtr body = parseElif();
            elifbody.push_back(body);
        }
        if(cur_token == ELSE) {
            if( cur_token != LPAREN ){
                std::cerr<<"invalid expression: "<<token[cur_token]<<std::endl;
                exit(EXIT_FAILURE);
            }
            advance();

            elsebody = parseBlockStatement();
            
            if( cur_token != RPAREN ){
                std::cerr<<"invalid expression: "<<token[cur_token]<<std::endl;
                exit(EXIT_FAILURE);
            }
            advance();
        }


        return std::make_shared<IfStatement>(condition, ifbody, elifbody, elsebody);

    }

    AstPtr Parser::parseVar() {

    }

    AstPtr Parser::parseWhile() {
        Token_type tok =cur_token;
        advance();
        AstPtr expr;
        AstPtr body;

        expr = parseExpression();

        if(cur_token != LPAREN){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
        }
        advance();

        body = parseBlockStatement();

        if(cur_token != RPAREN){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
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

        if(cur_token != LPAREN){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
            exit(EXIT_FAILURE);
        }
        advance();

        AstPtr body = parseBlockStatement();

        if(cur_token != RPAREN){
            std::cerr<<"invalid expression "<<token[cur_token]<<std::endl;
            exit(EXIT_FAILURE);
        }
        advance();

        return std::make_shared<ForLoopState>(var, condi, expr, body, tok);
    
    }
}

