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
                type = parsePointerType();
            default:{
                err::out("expected Token ",toks[cur_index]);
                next();
                }
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

        std::vector<AstPtr>vals;
        int lpos;
        if(cur_token == LBRACK){
            lpos = cur_index;
            next();
            if(cur_token != RBRACK) {
                
                do {    
                    AstPtr ele;
                    ele = parsePrimaryExpr();
                    vals.push_back(ele);

                }while(cur_token == COMMA);

            }

        } else {
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        if(cur_token != RBRACE){
            err::out("expected Token ",toks[cur_index]);
            next();
        }
        int rpos = cur_index;
        next();

        expectToken(SCOL);

        return std::make_shared<ListExpr>(tok,vals);
    }


    AstPtr Parser::parseArrayType() {
        AstPtr len, type;
        uint tok = cur_index;

        next();
        if(cur_token == RBRACK){
            err::out("expected Token ",toks[cur_index]);
            next();
        } else {
            len = parsePrimaryExpr();
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
                statm = parsePrimaryExpr();
        }
        expectToken(SCOL);
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
            err::out("expected Token ",toks[cur_index]);
            next();
        }
        
        if(cur_token != RBRACE){
            err::out("expected Token ",toks[cur_index]);
            next();
        }        
            rpos = cur_index;
        return std::make_shared<BlockStatement>(lpos, statms, rpos);
    }

             // case ASSN_ADD:
            // case ASSN_DIV:
            // case ASSN_MOD:
            // case ASSN_SUB:
            // case ASSN_MUL:
            // case AND_ASSN:
            // case OR_ASSN:
            // case NOT_ASSN:
            // case XOR_ASSN:
            // {

            // }

    AstPtr Parser::parsePointerType(){
        uint tok = cur_index;
        Token_type op = cur_token;
        AstPtr base;
        next();
        parseType();
        return std::make_shared<PointerType>(tok, op, base);
    }


    AstPtr Parser::parsePrefixExpr(){
        Token_type op = cur_token;
        uint tok = cur_index;
        AstPtr expr = parsePrimaryExpr();
        return std::make_shared<PrefixExper>(tok,expr,op);
    }

    AstPtr Parser::parsePostfixExpr(AstPtr left){
        Token_type op = cur_token;
        uint tok;
        return std::make_shared<PrefixExper>(tok,left,op);
    }



    AstPtr Parser::parsePrimaryExpr() {
        AstPtr left;
        switch(cur_token) {
            case STR:
            case INT:
            case FLOAT:
            case CHAR:
            case TRUE:
            case NIL:
            case FALSE:
            {
                left =  parseLitral();
                break;
            }
            case MUL:
            case ADD:
            case SUB:
            case INC:
            case DEC:
            case AND_OP:
            case NOT:
            case NOT_OP:
            {
                left = parsePrefixExpr();
                break;
            }
            case LPAREN:
            {
                left = parsePrimaryExpr();
                break;
            }
            case LBRACE:
            {
                left = parseStructExpr();
                break;
            }
            case LBRACK:
            {
                left = parseArrayExpr();
                break;
            }
            case IDEN:
            {
                AstPtr iden = parseIdentifier();
                next();
                return parseSecondryExpr(iden);
            }
            default:
            {    err::out("expected Token ",toks[cur_index]);
                next();}
        }

        return left;
    }


    


    AstPtr Parser::parseSecondryExpr(AstPtr expr) {
        switch(cur_token) {
            case MUL:
            case ADD:
            case SUB:
            case DIV:
            case MOD:
            case AND:
            case OR:
            case XOR_OP:
            case OR_OP:
            case AND_OP:
            case GEQL:
            case EQL:
            case NEQL:
            case GT:
            case LT:
            case LEQL:
            {
                return parseBineryExpr(expr, m_preced[cur_token]);
            }
            case ASSN_ADD:
            case ASSN_DIV:
            case ASSN_MOD:
            case ASSN_SUB:
            case ASSN_MUL:
            case AND_ASSN:
            case OR_ASSN:
            case NOT_ASSN:
            case XOR_ASSN:
            case ASSN:
            {
                return parseAssignment(expr);
            }
            case INC:
            case DEC:
            {
                return parsePostfixExpr(expr);
            }
            case DOT:
            case ARROW:
            {
                return parseDotOrArrow(expr);
            }
            case LPAREN:
            {
                return parseFuncCall();
            }
            case LBRACK:
            {
                return parseArrayAccess(expr);
            }
            default:
                {err::out("expected Token ",toks[cur_index]);
            next();}
        }

        return expr;
    }


    AstPtr Parser::parseBineryExpr(AstPtr left, int prev_prece) {
        uint tok = cur_index;
        Token_type opr;
        AstPtr right;
        if(left == nullptr) {
            left = parsePrimaryExpr();
        }
        //2+3*3/4+2*3
        while(cur_token != SCOL || cur_token!=RPAREN
                                || cur_token != RBRACE
                                || cur_token != RBRACK) {
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
                right = parsePrimaryExpr();
           
            }else{
                err::out("expected Token ",toks[cur_index]);
                next();
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

            expr = parsePrimaryExpr();

        } else {
            err::out("expected Token ",toks[cur_index]);
            next();
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

                arg = parsePrimaryExpr();

                args.push_back(arg);

               } while(cur_token == COMMA);

            }
            
        } else {
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        if(cur_token != RPAREN){
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        return std::make_shared<FunctionCall>(pos, name, args);
    }



    AstPtr Parser::parseTypeValuePair() {
        int tok = cur_index;
        AstPtr iden,type;
        
        if(cur_token == MUL || cur_token == LPAREN || cur_token == IDEN){
            iden = parsePrimaryExpr();
        } else {
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        type = parseType();
        return std::make_shared<Param>(tok, iden, type);
    }


    AstPtr Parser::parseStructExpr() {
        uint tok = cur_index;
        std::vector<AstPtr> vals;
        int lpos;
        if(cur_token != LBRACE){
            lpos = cur_index;
            next();
            if(cur_token != RBRACE){
                do{
                    AstPtr mem;
                    mem = parsePrimaryExpr();
                    vals.push_back(mem);
                }while(cur_token == COMMA);
            }else{
                err::out("expected Token ",toks[cur_index]);
                next();
            }
        }

        if(cur_token != RBRACE) {
            err::out("expected Token ",toks[cur_index]);
            next();
        }
        int rpos = cur_index;

        return std::make_shared<ListExpr>(tok, lpos, vals, rpos);

    }


    AstPtr Parser::parseStruct() {
        uint tok = cur_index;
        std::vector<AstPtr> element;
        
        expectToken(STRUCT);

        if(cur_token == LBRACE) {
            next();
            if(cur_token != RBRACE){

                do {
                    AstPtr member;
                    
                    member =  parseTypeValuePair();
                    
                    element.push_back(member);

                }while(cur_token == COMMA);
            }else{
                err::out("expected Token ",toks[cur_index]);
                next();
            }

        }else {
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        
        expectToken(RBRACE);
        expectToken(SCOL);
        return std::make_shared<StructState>(tok, element);
    }


    AstPtr Parser::parseNewStatm() {
        AstPtr ptr;
        uint tok = cur_index;

        if(cur_token != NEW){
            err::out("expected Token ",toks[cur_index]);
            next();
        }


    }

    AstPtr Parser::parseFreeStatm() {

    }


    AstPtr Parser::parseFuncdef(){
        int pos = cur_index;
        AstPtr funtype;
        std::vector<AstPtr> parameter;
        AstPtr retype;
        AstPtr body;
        expectToken(FN);

        funtype = parseIdentifier();
        
        if(cur_token == LPAREN){
            next();
            if(cur_token != RPAREN){
                
                do {
                    AstPtr member;
                    
                    member = parseTypeValuePair();
                    
                    parameter.push_back(member);

                } while(cur_token == COMMA);

            }
        }else {
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        if(cur_token != RPAREN){

        }

        retype = parseType();



        body = parseBlockStatement();

        return std::make_shared<FunctionDef>(pos, funtype, parameter, retype, body);
    }


    AstPtr Parser::parseConst() {
        uint tok;
        
        expectToken(CONST);

        if(cur_token != IDEN){
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        AstPtr name = parseIdentifier();
        AstPtr type = parseType();
        AstPtr val;
        if(cur_token == ASSN){
            next();
            val = parsePrimaryExpr();
        }else {
            err::out("expected Token ",toks[cur_index]);
            next();
        }

        expectToken(SCOL);

        return std::make_shared<ConstState>(tok,name,type,val);

    }

    AstPtr Parser::parseReturn() {
        int pos = cur_index;
        AstPtr val;
        
        if(cur_token != SCOL){
            val = parsePrimaryExpr();
        }

        if(cur_token != SCOL){
            err::out("expected Token ",toks[cur_index]);
            next();
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
            err::out("expected Token ",toks[cur_index]);
            next();
        } else {
            condition = parsePrimaryExpr();
        }

        if(cur_token != LBRACE) {
            err::out("expected Token ",toks[cur_index]);
            next();
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
                    err::out("expected Token ",toks[cur_index]);
                    next();
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
        expectToken(SCOL);
        
        return std::make_shared<VariableState>(tok, var, type);
    }



    AstPtr Parser:: parseAssignment(AstPtr left) {

        uint tok = cur_index;
        AstPtr right;
        Token_type op;

        op = cur_token;

        if(cur_token != ASSN){
            err::out("expected Token ",toks[cur_index]);
        }

        right = parsePrimaryExpr();
        
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

        if(isIN){
            

        }

        return std::make_shared<ForLoopState>(h1,h2,h3,body,pos);
    
    }
}

