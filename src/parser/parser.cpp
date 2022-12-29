#include"../../include/parser/parser.hpp"
#include"../../include/Error.hpp"

namespace parser {  
    AstPtr Parser::parse() {
        std::vector<AstPtr>statms;
        tokt tok = toks[cur_index];
        cur_token = toks[cur_index].tok_type;
        while(cur_token != FEOF){
            AstPtr statm;
            std::cout<<"statmen starting "<<toks[cur_index].data<<std::endl;
            statm = parseStatement();
            statms.push_back(statm);
            if(cur_token == SCOL)
                next();
        }
        return std::make_shared<Program>(tok,statms);
    }



    AstPtr Parser::parseType() {
        AstPtr type;
        std::cout<<"entring in type check "<<toks[cur_index].data<<std::endl;
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
                break;
            case BOOL:
                type = std::make_shared<BoolType>(toks[cur_index]);
                break;
            case LBRACK:
                type = parseArrayType(); 
                break;
            case STRUCT:
                type = parseStruct();
                break;
            case IDEN:
                type = parsePrimaryExpr(0);
                break;
            case MUL:
                type = parsePointerType();
                break;
            default:
                err::out("expected Type ",toks[cur_index]);
        }
        return type;
    }


    AstPtr Parser::parseLitral() {
        AstPtr type;
        std::cout<<"entring in litral check "<<toks[cur_index].data<<std::endl;
        switch(cur_token) {
            case INT:
                type = std::make_shared<NumericLitral>(toks[cur_index]);
                break;
            case FLOAT:
                type = std::make_shared<FloatLitral>(toks[cur_index]);
                break;
            case TRUE:
            case FALSE:
                type = std::make_shared<BoolLitral>(toks[cur_index]);
                break;
            case NIL:
                type = std::make_shared<NullLitral>(toks[cur_index]);
                break;
            case CHAR:
            case STR:
                type = std::make_shared<StringLitral>(toks[cur_index],(toks[cur_index].tok_type == CHAR?true:false));
                break;
            default:
                err::out("expected litral ",toks[cur_index]);

        }
        next();
        return type;
    }



    AstPtr Parser::parseArrayType() {
        AstPtr len, type;
        tokt tok = toks[cur_index];

        next();
        if(cur_token == RBRACK){
            err::out("expected array type ",toks[cur_index]);
        } else {
            len = parsePrimaryExpr(0);
        }
        if(cur_token != RBRACK){
            err::out("expected array type ",toks[cur_index]);
        }
        next();
        type = parseType();
                    
        return std::make_shared<ArrayType>(tok, len, type);
    }

    

    AstPtr Parser::parseIdentifier() {
        return std::make_shared<Identifier>(toks[cur_index]);
    }

    //============------------statement------------================

    AstPtr Parser::parseStatement() {
        std::cout<<"step :: entering statement checker "<<toks[cur_index].data<<std::endl;
        AstPtr statm;
        switch(cur_token){
            case FOR:
                statm = parseFor();
                break;

            case IF:
                statm = parseIfStatm();
                break;

            case LET:
                statm = parseLetStatm();
                break;

            case RETURN:
                statm = parseReturn();
                break;

            case CONTINUE:
            case BREAK:
                statm = std::make_shared<BranchState>(toks[cur_index]);
                break;

            case CONST:
                statm = parseConst();
                break;


            case STRUCT:
                statm = parseStruct();
                break;

            // case ENUM:
            //     statm = parseEnum();
            //     break;

            case FN:
                statm = parseFuncdef();
                break;
            case FREE:
            case NEW:
            case TYPE:
                statm = parseTypeStatm();
                break;
            case IMPORT:
            default:
                statm = parsePrimaryExpr(0);
                if(!statm){
                    err::out("expected statment checker ",toks[cur_index]); 
                    next();
                }
                break;
        }
        return statm;
    }

    AstPtr Parser::parseBlockStatement() {
        int lpos, rpos;
        std::vector<AstPtr> statms;
        
        if(cur_token != LBRACE){
            err::out("expected Block 1",toks[cur_index]);
        }

        if(next_t().tok_type != RBRACE){
            do {
                next();

                AstPtr statm;
                
                statm = parseStatement();
                
                statms.push_back(statm);
            
            } while(cur_token != RBRACE);
        }else{
            next();
        }
        
        if(cur_token != RBRACE){
            err::out("expected Block 2",toks[cur_index]); 
        }       
        rpos = cur_index;
        next();
        return std::make_shared<BlockStatement>(lpos, statms, rpos);
    }


    AstPtr Parser::parseTypeStatm() {
        tokt tok = toks[cur_index];
        if(cur_token != TYPE){
            err::out(" expected Type state ", toks[cur_index]);     
        }
        next();
        if(cur_token != IDEN){
            err::out(" expected Type iden ", toks[cur_index]);     
        }
        AstPtr left = parseIdentifier();
        
        next();

        AstPtr right = parseType();

        return std::make_shared<TypeState>(tok, left, right);

    }
             

    AstPtr Parser::parsePointerType(){
        tokt tok = toks[cur_index];
        Token_type op = cur_token;
        AstPtr base;
        next();
        parseType();
        std::cout<<"returning "<<toks[cur_index].data<<std::endl;
        return std::make_shared<PointerType>(tok, op, base);
    }


    AstPtr Parser::parsePrefixExpr(){
        Token_type op = cur_token;
        tokt tok = toks[cur_index];
        std::cout<<"prefix expr "<<toks[cur_index].data<<std::endl;
        next();
        AstPtr expr = parsePrimaryExpr(0);
        return std::make_shared<PrefixExper>(tok,expr,op);
    }

    AstPtr Parser::parsePostfixExpr(AstPtr left){
        Token_type op = cur_token;
        tokt tok = toks[cur_index];
        next();
        return std::make_shared<PrefixExper>(tok,left,op);
    }


    AstPtr Parser::parseArrayExpr() {
        tokt tok = toks[cur_index];

        std::vector<AstPtr>vals;
        std::cout<<"entering array exper "<<toks[cur_index].data<<std::endl;
        int lpos = cur_index;
        if(cur_token != RBRACK) {
            
            do { 
                next();   
                AstPtr ele;
                ele = parsePrimaryExpr(0);
                vals.push_back(ele);
                std::cout<<"after 1 "<<toks[cur_index].data<<std::endl;
            }while(cur_token == COMMA);

        } else {
            err::out("expected array exper ",toks[cur_index]);
        }

        if(cur_token != RBRACK){
            err::out("expected array ] exper ",toks[cur_index]);
        }
        int rpos = cur_index;

        next();
            std::cout<<"return array exper  "<<toks[cur_index].data<<std::endl;
        return std::make_shared<ListExpr>(tok,lpos,vals,rpos);
    }


    // lval opr rval

    AstPtr Parser::parsePrimaryExpr(int precedence){
        AstPtr left;
        switch(cur_token){
            case IDEN:
            {   
                left = parseIdentifier();
                next();
                switch(cur_token){
                    case LPAREN:
                        left = parseFuncCall(left);
                    case INC:
                    case DEC:
                        left = parsePostfixExpr(left);
                    case DOT:
                    case ARROW:
                        left = parseDotOrArrow(left);
                    case LBRACK:
                        left = parseArrayAccess(left);
                    default:
                        left = parseSecondryExpr(left,precedence);
                }
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
            case STR:
            case INT:
            case FLOAT:
            case CHAR:
            case TRUE:
            case NIL:
            case FALSE:
            {
                left = parseLitral();
                left = parseSecondryExpr(left,precedence);
                break;
            }
            case LPAREN:
            {
                next();
                std::cout<<"step :: entering paren exper "<<toks[cur_index].data<<std::endl;
                left = parsePrimaryExpr(0);
                std::cout<<"step :: returing paren exper "<<toks[cur_index].data<<std::endl;
                if(cur_token != RPAREN){
                    err::out("expected close PAREN ",toks[cur_index]);
                }
                next();
                switch(cur_token){
                    case DOT:
                    case ARROW:
                        left = parseDotOrArrow(left);
                        break;
                    // case LPAREN:
                    //     left = parseFuncCall(left);
                    //     break;
                    default:
                        left = parseSecondryExpr(left,precedence);
                        break;
                }
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
            case RPAREN:
            //case COMMA:
            case SCOL:
            case RBRACE:
            case RBRACK:
            case FEOF:
            {
                break;
            }
            default:
                err::out("expected exper \'",toks[cur_index]);
                break;
            
        }
        return left;
    }


    AstPtr Parser::parseSecondryExpr(AstPtr left, int precedence){
       std::cout<<"entering sec exper "<<toks[cur_index].data<<std::endl;
        switch(cur_token)
        {
            case ASSN_ADD:
            case ASSN_DIV:
            case ASSN_MOD:
            case ASSN_SUB:
            case ASSN_MUL:
            case AND_ASSN:
            case LSHIFT_ASSN:
            case RSHIFT_ASSN:
            case OR_ASSN:
            case NOT_ASSN:
            case XOR_ASSN:
            case ASSN:
            {
                left = parseAssignment(left);
                break;
            }
            case MUL:
            case DIV:
            case MOD:
            case ADD:
            case SUB:
            case RSHIFT:
            case LSHIFT:
            case LT:
            case LEQL:   
            case GT:
            case GEQL:
            case EQL:
            case NEQL:
            case AND_OP:
            case XOR_OP:
            case OR_OP:
            case AND:
            case OR:
            {
                left = parseBineryExpr(left, precedence);
                break;
            }
            case RPAREN:
            case COMMA:
            case SCOL:
            case RBRACE:
            case RBRACK:
            case FEOF:
            {
                break;
            }
            default:
                err::out("expected sec exper \'",toks[cur_index]);
                break;
        }

        return left;
    }


    int Parser::preced(Token_type op){
        switch (op)
        {
        case MUL:
        case DIV:
        case MOD:
            return 10;
        case ADD:
        case SUB:
            return 9;
        case LSHIFT:
        case RSHIFT:
            return 8;
        case LT:
        case LEQL:
        case GT:
        case GEQL:
            return 7;
        case EQL:
        case NEQL:
            return 6;
        case AND:
            return 5;
        case XOR_OP:
            return 4;
        case OR:
            return 3;    
        case AND_OP:
            return 2;  
        case OR_OP:
            return 1;
        default:
            err::out("operator Token ",toks[cur_index]);
        }
        return 0;
    }


    AstPtr Parser::parseBineryExpr(AstPtr left, int prev_prece) {
        tokt tok = toks[cur_index];
        Token_type opr;
        AstPtr right;
        if(left == nullptr) {
            left = parsePrimaryExpr(prev_prece);
        }
                    std::cout<<"step :: entering binery exper "<<" "<<toks[cur_index].data<<std::endl;

        //2+3*3/4+2*3
        while(BineryOP(cur_token)) {
            opr = cur_token;
            if(prev_prece > preced(opr)) {
                return left;
            }
            next();
            right = parseBineryExpr(nullptr, preced(opr)+1);
            left = std::make_shared<BineryExper>(tok, left, opr, right);
        }

        return left;
    }



    AstPtr Parser::parseDotOrArrow(AstPtr left) {
        AstPtr right;
        tokt tok = toks[cur_index];
        Token_type mem_op;
        
        if(cur_token == ARROW || cur_token == DOT){
           
            if(next_t().tok_type == IDEN || next_t().tok_type == LPAREN){
           
                next();
                right = parsePrimaryExpr(0);
           
            }else{
                err::out("expected member expression ",toks[cur_index]);
            }
        }

        return std::make_shared<MemberExpr>(tok, left, mem_op, right);
    }


    AstPtr Parser::parseArrayAccess(AstPtr left) {
        tokt tok = toks[cur_index];
        int lpos,rpos;
        AstPtr expr;
        lpos = cur_index;
        if(cur_token != LBRACK){
            err::out("expected index ",toks[cur_index]);
            
        }
        next();
        
        if(cur_token != RBRACK){

            expr = parsePrimaryExpr(0);

        } else {
            err::out("expected index ",toks[cur_index]);
        }
        
        rpos = cur_index;
        if(cur_token != RBRACK){
            err::out("expected index ] ",toks[cur_index]);
            
        }
        next();
        left = std::make_shared<IndexExpr>(tok,left,lpos,expr,rpos);

        if(cur_token == LBRACK){
            left = parseArrayAccess(left);
        }

        return left;
    }


    AstPtr Parser::parseFuncCall(AstPtr caller_name) {
        tokt tok = toks[cur_index];
        std::vector<AstPtr> args;

        if(cur_token != LPAREN){
            err::out("expected call ",toks[cur_index]);
        }
   
        if(next_t().tok_type != RPAREN) {
                
            do {
                next();
                AstPtr arg;

                arg = parsePrimaryExpr(0);

                args.push_back(arg);

            } while(cur_token == COMMA);

        }else{
            next();
        }
    

        if(cur_token != RPAREN){
            err::out("expected call ",toks[cur_index]);

        }else
           next();
        
        return std::make_shared<FunctionCall>(tok, caller_name, args);
    }



    AstPtr Parser::parseTypeValuePair() {
        tokt tok = toks[cur_index];
        AstPtr iden,type;
        
        if(cur_token == IDEN){
            iden = parseIdentifier();
        } else {
            err::out("expected type val checker ",toks[cur_index]);
        }
        next();
        
        type = parseType();
        return std::make_shared<Parameter>(tok, iden, type);
    }


    AstPtr Parser::parseStructExpr() {
        tokt tok = toks[cur_index];
        std::vector<AstPtr> vals;
        int lpos;
        if(cur_token != LBRACE){
            err::out("expected struct exper ",toks[cur_index]);
        }
        lpos = cur_index;
        if(next_t().tok_type != RBRACE){
            do{
                next();
                AstPtr mem;
                mem = parsePrimaryExpr(0);
                vals.push_back(mem);
            }while(cur_token == COMMA);
        }else{
            next();
        }

        if(cur_token != RBRACE) {
            err::out("expected struct exper ",toks[cur_index]);
        }
        int rpos = cur_index;

        return std::make_shared<ListExpr>(tok, lpos, vals, rpos);

    }


    AstPtr Parser::parseStruct() {
        tokt tok = toks[cur_index];
        std::vector<AstPtr> element;
        
        if(cur_token != STRUCT){
            err::out("expected struct ",toks[cur_index]);
        }
        next();
        if(cur_token != LBRACE) {
            err::out("expected struct ",toks[cur_index]);
        }
        next();

        if(cur_token != RBRACE){
            err::out("expected struct ",toks[cur_index]);
        }


        while(cur_token !=  FEOF && cur_token != RBRACE){
                
                AstPtr member;
                
                member =  parseTypeValuePair();
                
                element.push_back(member);

                next();
                if(cur_token != SCOL){
                    err::out("expected struct {;} ",toks[cur_index]);
                }else
                    next();
        }

        if(cur_token != RBRACE){
            err::out("expected struct ",toks[cur_index]);
            
        }
        
        std::cout<<"returning struct -> var "<<toks[cur_index].data<<std::endl;
         return std::make_shared<StructState>(tok, element);
    }


    // AstPtr Parser::parseNewStatm() {
    //     AstPtr ptr;
    //     tokt tok = toks[cur_index];

    //     if(cur_token != NEW){
    //         err::out("expected Token ",toks[cur_index]);
    //         next();
    //     }


    // }

    // AstPtr Parser::parseFreeStatm() {

    // }



    AstPtr Parser::parseFuncdef(){
        tokt tok = toks[cur_index];
        AstPtr name;
        std::vector<AstPtr> parameter;
        AstPtr retype;
        AstPtr body;
        if(cur_token != FN){
            err::out("expected FN ",toks[cur_index]);
            
        }
        next();
        if(cur_token != IDEN){
            err::out("expected func 1",toks[cur_index]);
        }else
            name = parseIdentifier();
        next();
        if(cur_token != LPAREN){
            err::out("expected func 1",toks[cur_index]);
        }

        if(next_t().tok_type != RPAREN){
            
            do {
                next();

                AstPtr member;
                
                member = parseTypeValuePair();
                
                parameter.push_back(member);

            } while(cur_token == COMMA);

        }else{
            next();
        }


        if(cur_token != RPAREN){
            err::out("expected func 2 ",toks[cur_index]);
            
        }
        next();
        retype = parseType();
        next();

        body = parseBlockStatement();

        return std::make_shared<FunctionDef>(tok, name, parameter, retype, body);
    }


    AstPtr Parser::parseConst() {
        tokt tok = toks[cur_index];
        
        if(cur_token != CONST){
            err::out("expected const ",toks[cur_index]);
            
        }
        next();

        if(cur_token != IDEN){
            err::out("expected const ",toks[cur_index]);
        }

        AstPtr name = parseIdentifier();
        next();
        AstPtr type = parseType();
        next();
        AstPtr val;
        if(cur_token == ASSN){
            next();
            val = parsePrimaryExpr(0);
        }else {
            err::out("expected const ",toks[cur_index]);
            next();
        }

        if(cur_token != SCOL){
            err::out("expected const ",toks[cur_index]);
            
        }
        next();

        return std::make_shared<ConstState>(tok,name,type,val);

    }

    AstPtr Parser::parseReturn() {
        tokt tok = toks[cur_index];
        AstPtr val;
        next();

        if(cur_token != SCOL){
            val = parsePrimaryExpr(0);
        }
        if(cur_token != SCOL){
                err::out("expected retuen ",toks[cur_index]);
        }
        std::cout<<"returning from return statm -> "<<toks[cur_index].data<<std::endl;
        next();

        return std::make_shared<ReturnState>(tok, val);
    }

       
    AstPtr Parser::parseIfStatm() {
        tokt tok = toks[cur_index];
        if(cur_token != IF){
            err::out("expected if ",toks[cur_index]);
            
        }
        next();
        AstPtr condition;
        AstPtr if_;
        AstPtr else_;

        if(cur_token == LBRACE) {
            err::out("expected if 1 ",toks[cur_index]);
            next();
        } else {
            condition = parsePrimaryExpr(0);
        }
        std::cout<<"entering after cond "<<toks[cur_index].data<<std::endl;
        if(cur_token != LBRACE) {
            err::out("expected if 2 ",toks[cur_index]);
            next();
        }

        if_ = parseBlockStatement();
        std::cout<<"entering after block "<<toks[cur_index].data<<std::endl;

        if(cur_token == ELSE) {
            next();
            switch(cur_token){
                case IF:
                    else_ = parseIfStatm();
                    break;
                case LBRACE:
                    else_ = parseBlockStatement();
                    break;
                default:
                    err::out("expected if 3 ",toks[cur_index]);

            }
        }
        
        return std::make_shared<IfStatement>(tok,condition, if_, else_);
    }



    AstPtr Parser::parseLetStatm() {
        tokt tok = toks[cur_index];
        std::vector<AstPtr> var;
        AstPtr type;
        std::cout<<"entering var "<<toks[cur_index].data<<std::endl;

        if(cur_token != LET){
            err::out("expected var ",toks[cur_index]);
            
        }
        if(next_t().tok_type == IDEN){
            do {
                next();
                AstPtr v;
                if(cur_token == IDEN){
                    v = parseIdentifier();
                    next();
                    var.push_back(v);
                }
            }while(cur_token == COMMA);
        }else{
            err::out("expected var ",toks[cur_index]);
        }
        type = parseType();
        next();

        if(cur_token != SCOL){
            //err::out("expected var ",toks[cur_index]);
                    next();

        }
        return std::make_shared<LetState>(tok, var, type);
    }



    AstPtr Parser::parseAssignment(AstPtr left) {
        tokt tok = toks[cur_index];
        AstPtr right;
        Token_type op;
        op = cur_token;
        std::cout<<"entering assinment oper = "<<toks[cur_index].data<<std::endl;
        next();
        right = parsePrimaryExpr(0);
        return std::make_shared<AssignmentExpr>(tok, left, op, right);
    }


    AstPtr Parser::parseFor() {
        tokt tok = toks[cur_index];
        AstPtr h1, h2, h3, body;
        if(cur_token != FOR){
            err::out("expected for ",toks[cur_index]);
            
        }
        next();
        bool isIN = false;
        if(cur_token != LBRACE) {

            if(cur_token != SCOL) {

                if(cur_token == IN){
                    err::out("expected for ",toks[cur_index]);
                    next();
                }else{
                    h2 = parseStatement();
                }

            } 

            if(cur_token == IN){
                isIN = true;
                next();
                h1 = h2;
                h2 = nullptr;
                if(cur_token == SCOL || cur_token == LBRACE){
                    err::out("expected for ",toks[cur_index]);
                    next();
                }else{
                    h1 = parseStatement();
                }


            }else if(!isIN && cur_token == SCOL) {
                next();
                h1 = h2;
                h2 = nullptr;
                if(cur_token != SCOL){
                    h2 = parseStatement();
                }
                if(cur_token != SCOL){
                    err::out("expected for ",toks[cur_index]);
                    
                }
                next();
                if(cur_token != LBRACE){
                    h3 = parseStatement();
                }
            } 

        } else {
            err::out("expected for ",toks[cur_index]);
            next();
        }

        std::cout<<"entering for -> block "<<toks[cur_index].data<<std::endl;
        
        body = parseBlockStatement();

        if(isIN){
            return std::make_shared<InState>(tok, h1,h2,body);
        }

        return std::make_shared<ForLoopState>(tok,h1,h2,h3,body);
    
    }
}

