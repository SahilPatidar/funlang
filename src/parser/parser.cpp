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
            case LBRACK:
                type = parseArrayType(); 
            case STRUCT:
                type = parseStruct();

        }
        return type;
    }

    AstPtr Parser::parseArrayType() {
        AstPtr len, type;
        tokt tok = toks[cur_index];
        advance();
        if(cur_token == RBRACK){
            //err
        } else {
            len = parseExpression();
        }
        expectToken(RBRACK);
        type = parseType();
        return std::make_shared<ArrayType>(tok, len, type);
    }

    AstPtr Parser::parseStruct() {
        tokt tok = toks[cur_index];
        AstPtr element;
        
        return std::make_shared<StructState>(tok, element);
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
                statm = parseVarStatm();
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

    AstPtr Parser::parseBlockStatement() {
        int lpos, rpos;
        std::vector<AstPtr> statms;
        int lpos = cur_index;
        
        expectToken(LBRACE);
        
        if(cur_token != RBRACE){
            do {
                
                AstPtr statm;
                
                statm = parseStatement();
                
                statms.push_back(statm);
            
            } while(cur_token != RBRACE);
        }

        expectToken(RBRACE);
        
        return std::make_shared<BlockStatement>(lpos, statms, rpos);
    }

    AstPtr Parser::parseExpression() {


    }

    AstPtr Parser::parseUnaryExpr() {

    }

    AstPtr Parser::parseBineryExpr(AstPtr left, int prev_prece) {
        tokt tok = toks[cur_index];
        Token_type opr;
        AstPtr right;
        if(left == NULL) {
            left = parseExpression();
        }
        //2+3*3/4+2*3
        while(1){
            opr = cur_token;
            if(prev_prece > m_preced[opr]) {
                return left;
            }
            advance();
            right = parseBineryExpr(NULL, m_preced[opr]);
            left = std::make_shared<BineryOp>(tok, left, opr, right);
        }

        return left;
    }

    AstPtr Parser::parseParenExpr() {

    }

    AstPtr Parser::parseArgList() {
        int lpos, rpos;
        lpos = cur_index;
        std::vector<AstPtr>args;
        expectToken(LPAREN);
        if(cur_token != RPAREN){
            do {
                AstPtr arg;

                arg = parseExpression();

                args.push_back(arg);

            } while(cur_token != COMMA);
        }
        rpos = cur_index;
        expectToken(RPAREN);
        return std::make_shared<FeildList>(lpos,args,rpos);
    }



    AstPtr Parser::parseFuncCall() {
        int pos = cur_index;
        AstPtr name;
        AstPtr args = NULL;
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

        body = parseBlockStatement();

        return std::make_shared<FunctionDef>(toks[cur_index], name, parameter, retype, body);
    }


    AstPtr Parser::parseReturn() {
        int pos = cur_index;
        expectToken(RETURN);
        AstPtr val;
        
        expectToken(SCOL);
        return std::make_shared<ReturnState>(toks[pos], val);
    }

       
    AstPtr Parser::parseIfStatm() {
        int pos = cur_index;
        expectToken(IF);
        AstPtr condition;
        AstPtr if_;
        AstPtr else_;

        if(cur_token == LBRACE) {
            //err
        } else {
            condition = parseExpression();
        }
        
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
        expectToken(RBRACE);
        return std::make_shared<IfStatement>(condition, if_, else_);
    }


    AstPtr Parser::parseVarStatm() {
        tokt tok = toks[cur_index];
        AstPtr var, type;
        expectToken(VAR);
        var = parseVarList();
        type = parseType();
        return std::make_shared<VariableState>(tok, var, type);
    }

    AstPtr Parser:: parseAssignment(AstPtr left) {
        tokt tok = toks[cur_index];
        AstPtr right;
        Token_type op;
        op = cur_token;
        expectToken(ASSN);
        right = parseExpression();
        expectToken(SCOL);
        return std::make_shared<AssignmentState>(tok, left, op, right);
    }


    AstPtr Parser::parseFor() {
        int pos = cur_index;
        AstPtr h1, h2, h3, body;
        expectToken(FOR);
        bool isIN = false;
        if(cur_token != LBRACE) {
            
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
                    h3 = parseStatement();
                }
            } 

        } 
        
        body = parseBlockStatement();
        // expectToken(LBRACE);

        if(isIN){
            

        }

        return std::make_shared<ForLoopState>(h1,h2,h3,body,toks[pos]);
        
    
    }
}

