#include"../../include/parser/parser.hpp"

namespace parser {  
    AstPtr Parser::parse() {
        while(cur_token != FEOF){
            advance();
        }
        return ;
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
                type = std::make_shared<IntType>(toks[cur_index]);
                break;
            case F32:
            case F64:
                type = std::make_shared<FloatType>(toks[cur_index]);
                break;
            case STRING:
                type = std::make_shared<StringType>(toks[cur_index]);
            case BOOL:
                type = std::make_shared<BoolType>(toks[cur_index]); 

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
                statm = parseIfStatm();
                break;

            case VAR:
                statm = parseVar();
                break;

            case RETURN:
                statm = parseReturn();
                break;

            case CONTINUE:
                statm = std::make_shared<BranchState>(toks[cur_index]);
                break;

            case CONST:
                statm = parseConst();
                break;

            case BREAK:
                statm = std::make_shared<BranchState>(toks[cur_index]);
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

    AstPtr Parser::parseArgList(){
        int pos = cur_index;
        std::vector<AstPtr>args;
        int isRight_P = 1;
        expectToken(LPAREN);
        while(cur_token != RPAREN||isRight_P != 1) {
            
        }
        expectToken(RPAREN);
        return std::make_shared<FeildList>(toks[pos],args);
    }

    AstPtr Parser::parseFuncCall() {
        int pos = cur_index;
        AstPtr name;
        AstPtr args;
        name = parseIdentifier();
        
        args = parseArgList();
        return std::make_shared<FunctionCall>(toks[pos], name, args);
    }


    AstPtr Parser::parseFuncdef(){
        int pos = cur_index;
        AstPtr name;
        AstPtr parameter;
        AstPtr retype;
        AstPtr body;
        expectToken(FN);

        name = parseIdentifier();

        expectToken(LPAREN);
        parameter = parseParamList();
        expectToken(RPAREN);
        retype = parseType();

        expectToken(LBRACE);

        body = parseBlockStatement();

        expectToken(RBRACE);

        return std::make_shared<FunctionDef>(toks[cur_index], name, parameter, retype, body);
    }


    AstPtr Parser::parseReturn() {
        int pos = cur_index;
        expectToken(RETURN);
        AstPtr val;
        val = parseExpression();
        expectToken(SCOL);
        return std::make_shared<ReturnState>(toks[pos], val);
    }

    AstPtr Parser::parseifHeader() {
        AstPtr expr;

        while(cur_token != LBRACE) {

        }        
    }
       
    AstPtr Parser::parseIfStatm() {
        int pos = cur_index;
        expectToken(IF);
        AstPtr condition;
        AstPtr if_;
        AstPtr else_;

        condition = parseifHeader();
        
        if_ = parseBlockStatement();

        if(cur_token == ELSE) {
            advance();
            switch(cur_token){
                case IF:
                    else_ = parseIfStatm();
                case LBRACE:
                    else_ = parseBlockStatement();
                default:
                    //err
            }
        }

        return std::make_shared<IfStatement>(condition, if_, else_);

    }

    AstPtr Parser::parseVar() {

    }


    AstPtr Parser::parseFor() {
        int pos = cur_index;
        AstPtr h1, h2, h3, body;
        advance();
        bool isIN = false;
        if(cur_token != LBRACE) {
            advance();
            if(cur_token != SCOL) {
                if(cur_token != IN){
                    // like in go lang nil lhs

                    advance();
                    isIN = true;
                    
                } else {
                    h2 = parseStatement();
                }
            } 

            if(!isIN && cur_token == SCOL) {
                advance();
                h1 = h2;
                h2 = NULL;
                if(cur_token != SCOL){
                    h2 = parseStatement();
                }
                expectToken(SCOL);
                if(cur_token != LBRACE){
                    h3 = parseExpression();
                }
            } else {
                //error
            }

        } 
        
        body = parseBlockStatement();
        expectToken(LBRACE);

        if(isIN){


        }

        return std::make_shared<ForLoopState>(h1,h2,h3,body,toks[pos]);
        
    
    }
}

