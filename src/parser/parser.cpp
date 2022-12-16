#include"../../include/parser/parser.hpp"

namespace parser {  
    AstPtr Parser::parse() {
        std::vector<AstPtr>statms;
        uint tok = 0;
        while(cur_token != FEOF){
            AstPtr statm;
            statm = parseStatement();
            next();
        }
        return std::make_shared<Program>(tok,statms);
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
            case IDEN:
                type = std::make_shared<Identifier>(toks[cur_index],toks[cur_index].data);
            case MUL:
            case LPAREN:
        }
        next();
        return type;
    }

    AstPtr Parser::parseLitral() {
        switch(cur_token) {
            case INT:
                return std::make_shared<NumericLitral>(toks[cur_index]);
            case FLOAT:
                return std::make_shared<FloatLitral>(toks[cur_index]);
            case TRUE:
            case FALSE:
                return std::make_shared<BoolLitral>(toks[cur_index]);
            case NIL:
                return std::make_shared<NullLitral>(toks[cur_index]);
            case CHAR:
            case STR:
                return std::make_shared<StringLitral>(toks[cur_index],(toks[cur_index].tok_type == CHAR?true:false));
        }
    }


    AstPtr Parser::parseArrayExpr() {
        uint tok = cur_index;
        AstPtr len;
        std::vector<AstPtr>vals;
        if(cur_token == LBRACK){
            next();
            if(cur_token != RBRACK){

            }else{
                //err
            }
        }else{
            //err
        }

        if(cur_token != RBRACK){
            //err
        }

        AstPtr type = parseType();

        if(cur_token == LBRACE){
            next();
            if(cur_token != RBRACE) {
                
                do {    
                    
                    AstPtr ele;
                    ele = parseExpression();
                    vals.push_back(ele);

                }while(cur_token == COMMA);

            }

        } else {
            //err
        }

        if(cur_token != RBRACE){
            //err
        }

        next();

        expectToken(SCOL);

        return std::make_shared<ArrayExpr>(tok,len,type,vals);
    }


    AstPtr Parser::parseArrayType() {
        AstPtr len, type;
        uint tok = cur_index;

        next();
        if(cur_token == RBRACK){
            //err
        } else {
            len = parseExpression();
        }
        expectToken(RBRACK);
        type = parseType();
        return std::make_shared<ArrayType>(tok, len, type);
    }

    

    AstPtr Parser::parseIdentifier() {
        return std::make_shared<Identifier>(toks[cur_index].data,cur_index);
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
            case FREE:
            case NEW:
            case TYPE:
            case IMPORT:

            default:

        }
        return statm;
    }

    AstPtr Parser::parseBlockStatement() {
        int lpos, rpos;
        std::vector<AstPtr> statms;
        
        
        if(cur_token == LBRACE){
            lpos = cur_index;
            next();

            if(cur_token != RBRACE){
                do {
                    
                    AstPtr statm;
                    
                    statm = parseStatement();
                    
                    statms.push_back(statm);
                
                } while(cur_token != RBRACE);
            }

        } else {
            //err
        }
        
        if(cur_token != RBRACE){
            //err
        }        
            rpos = cur_index;
        return std::make_shared<BlockStatement>(lpos, statms, rpos);
    }


    AstPtr Parser::parseNewStatm() {
        AstPtr ptr;
        uint tok = cur_index;

        if(cur_token != NEW){
            //err
        }


    }

    AstPtr Parser::parseFreeStatm() {

    }



    AstPtr Parser::parseExpression() {


    }

    AstPtr Parser::parseLUnaryExpr() {
        uint tok = cur_index;
        AstPtr right;
        Token_type op;
        op = cur_token;
        right = parseExpression();
        return std::make_shared<UnaryExper>(tok,right,op);
    }

    AstPtr Parser::parseRUnaryExpr(AstPtr left) {
        uint tok = cur_index;
        AstPtr x;
        Token_type op;
        if(match2(INC,DEC)){
            op = cur_token;
        }
        return std::make_shared<UnaryExper>(tok,left,op);

    }

    AstPtr Parser::parseBineryExpr(AstPtr left, int prev_prece) {
        uint tok = cur_index;
        Token_type opr;
        AstPtr right;
        if(left == nullptr) {
            left = parseExpression();
        }
        //2+3*3/4+2*3
        while(cur_token != SCOL||cur_token!=RPAREN){
            opr = cur_token;
            if(prev_prece > m_preced[opr]) {
                return left;
            }
            next();
            right = parseBineryExpr(nullptr, m_preced[opr]);
            left = std::make_shared<BineryExper>(tok, left, opr, right);
        }

        return left;
    }



    AstPtr Parser::parseDotOrArrow(AstPtr left) {
        AstPtr right;
        uint tok;
        Token_type mem_op;
        
        if(match2(ARROW,DOT)){
           
            if(next_t().tok_type == IDEN || next_t().tok_type == LPAREN){
           
                next();
                right = parseExpression();
           
            }else{
                //err
            }
        }

        return std::make_shared<MemberExpr>(tok, left, mem_op, right);
    }


    AstPtr Parser::parseArrayAccess(AstPtr left) {
        uint tok_pos = cur_index;
        int lpos,rpos;
        AstPtr expr;
        lpos = cur_index;
        expectToken(LBRACK);
        
        if(cur_token != RBRACK){

            expr = parseExpression();

        } else {
            //err
        }
        
        rpos = cur_index;
        expectToken(RBRACK);
        
        return std::make_shared<IndexExpr>(tok_pos,left,lpos,expr,rpos);
    }

   
    


    AstPtr Parser::parseFuncCall() {
        int pos = cur_index;
        AstPtr name;
        std::vector<AstPtr> args;
        name = parseIdentifier();
        next();
        if(cur_token == LPAREN){
            next();
            if(cur_token != RPAREN) {
                 
                do {

                AstPtr arg;

                arg = parseExpression();

                args.push_back(arg);

               } while(cur_token == COMMA);

            }
            
        } else {
            //err
        }

        if(cur_token != RPAREN){
            //err
        }

        return std::make_shared<FunctionCall>(pos, name, args);
    }



    AstPtr Parser::parseTypeValuePair() {
        int tok = cur_index;
        AstPtr iden,type;
        
        if(cur_token == MUL || cur_token == LPAREN || cur_token == IDEN){
            iden = parseExpression();
        } else {
            //err
        }

        type = parseType();
        return std::make_shared<Param>(tok, iden, type);
    }



    AstPtr Parser::parseStruct() {
        uint tok = cur_index;
        std::vector<AstPtr> element;
        
        expectToken(STRUCT);

        if(cur_token == LBRACE) {
            if(cur_token != RBRACE){

                do {
                    AstPtr member;
                    
                    member =  parseTypeValuePair();
                    
                    element.push_back(member);

                }while(cur_token == COMMA);
            }
        }else {
            //err
        }

        
        expectToken(RBRACE);
        expectToken(SCOL);
        return std::make_shared<StructState>(tok, element);
    }



    AstPtr Parser::parseFuncdef(){
        int pos = cur_index;
        AstPtr funtype;
        std::vector<AstPtr> parameter;
        AstPtr retype;
        AstPtr body;
        expectToken(FN);

        funtype = parseExpression();
        
        if(cur_token == LPAREN){
            next();
            if(cur_token != RPAREN){
                
                do {
                    AstPtr member;
                    
                    member = parseTypeValuePair();
                    
                    parameter.push_back(member);

                }while(cur_token == COMMA);

            }
        }else {
            //err
        }

        if(cur_token != RPAREN){

        }

        retype = parseType();

        if(cur_token )

        body = parseBlockStatement();

        return std::make_shared<FunctionDef>(pos, funtype, parameter, retype, body);
    }

    AstPtr Parser::parseConst() {
        uint tok;
        
        expectToken(CONST);

        if(cur_token != IDEN){
            //err
        }

        AstPtr name = parseIdentifier();
        AstPtr type = parseType();
        AstPtr val;
        if(cur_token == ASSN){
            next();
            val = parseExpression();
        }else {
            //err;
        }

        expectToken(SCOL);

        return std::make_shared<ConstState>(tok,name,type,val);

    }

    AstPtr Parser::parseReturn() {
        int pos = cur_index;
        AstPtr val;
        
        if(cur_token != SCOL){
            val = parseExpression();
        }

        if(cur_token != SCOL){
            //err
        }
        return std::make_shared<ReturnState>(pos, val);
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

        if(cur_token != LBRACE) {
            //err
        }

        if_ = parseBlockStatement();

        if(cur_token == ELSE) {
            next();
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
        return std::make_shared<IfStatement>(condition, if_, else_,pos);
    }



    AstPtr Parser::parseVarStatm() {
        uint tok = cur_index;
        std::vector<AstPtr> var;
        AstPtr type;

        expectToken(VAR);
        
        do {
            AstPtr v;
            if(cur_token == IDEN){
                v = parseIdentifier();
                var.push_back(v);
            }

        }while(cur_token == COMMA);
        
        type = parseType();
        
        return std::make_shared<VariableState>(tok, var, type);
    }



    AstPtr Parser:: parseAssignment(AstPtr left) {

        uint tok = cur_index;
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

                    next();
                    isIN = true;

                } else {
                    h2 = parseStatement();
                }
            } 

            if(!isIN && cur_token == SCOL) {
                next();
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

        return std::make_shared<ForLoopState>(h1,h2,h3,body,pos);
        
    
    }
}

