#include"../../include/parser/parser.hpp"
#include"../../include/Error.hpp"

namespace parser {  
    AstPtr Parser::parse() {
        std::vector<AstPtr>statms;
        tokt tok = toks[cur_index];
        cur_token = toks[cur_index].tok_type;
        while(!check(FEOF)){
            AstPtr statm;
            m_preced = 0;
            if(parseStatement()){
                std::cout<<"yes"<<std::endl;
                statms.push_back(m_node);
            }else{
                break;
            }
        }
        dump2(__func__);
        return std::make_shared<Program>(tok,statms);
    }


    bool Parser::parseStatement() {
        dump(__func__);
        std::cout<<toks[cur_index].data<<std::endl;
        switch(cur_token){
            case FOR:
                if(!parseFor()){
                    return false;
                }
                break;
            case WHILE:
                if(!parseWhile()){
                    return false;
                }
                break;

            case IF:
                if(!parseIfStatm()){
                    return false;
                }
                break;

            case LET:
                if(!parseLetStatm()){
                    return false;
                }
                break;

            case RETURN:
                if(!parseReturn()){
                    return false;
                }
                break;

            case CONTINUE:
            case BREAK:
                m_node = std::make_shared<BranchState>(toks[cur_index]);
                next();
                break;

            case CONST:
                if(!parseConst()){
                    return false;
                }
                break;


            case STRUCT:
                if(!parseStruct()){
                    return false;
                }
                break;

            // case ENUM:

            //     break;

            case FN:
                if(!parseFuncdef()){
                    return false;
                }
                break;
            case TYPE:
                if(!parseTypeStatm()){
                    return false;
                }
                break;
            case EXTERN:
                if(!parseExtern()){
                    return false;
                }
                break;
            case USE:
                if(!parseUseStatm()){
                    return false;
                }
            default:
                if(!parseSemiConsumedExpr()){
                    return false;
                }
                break;
        }
                dump2(__func__);

        return true;
    }

    bool Parser::parseUseStatm() {
        
        return true;
    }

    bool Parser::parseExtern() {
        dump2(__func__);

        tokt tok = toks[cur_index];
        AstPtr lib;
        AstPtr block;
        next();
        if(!check(STR)){
            err::out("expected 'string' found -> ",toks[cur_index]);
            return false;
        }
        if(parseLiteral()){
            lib = m_node;
        }
        if(!parseStatement()){
            err::out("expected Statement expression found -> ",toks[cur_index]);
            return false;
        }
        block = m_node;
        m_node = std::make_shared<Extern>(tok,lib,block);
        dump2(__func__);

        return true;
    }

    bool Parser::parseIdentifier() {
        dump(__func__);

        if(!check(IDEN)){
            err::out("expected 'identifier' found -> ",toks[cur_index]);
            return false;
        }else{
            m_node = std::make_shared<Identifier>(toks[cur_index],toks[cur_index].data);
        }
        next();
                dump2(__func__);

        return true;
    }


    bool Parser::parseType() {
        //AstPtr type;
        dump(__func__);
        switch(cur_token){
            case LBRACK:
                if(!parseArrayType()){
                    return false;
                }
                break;
            case I8:
            case I16:
            case I32:
            case I64:
            case UI8:
            case UI16:
            case UI32:
            case UI64:
            case F32:
            case F64:
            case STRING:
            case BOOL:
                m_node = std::make_shared<PreDefineType>(toks[cur_index]);
                next();
                break;
            case LPAREN:
                if(!parseTupleType()){
                    return false;
                }
                break;
            case DOTDOT:
                m_node = std::make_shared<Variadic>(toks[cur_index]);
                break;
            case FN:
            {
                tokt tok = toks[cur_index];
                next();
                if(!check(LPAREN)){
                    err::out("expected '{' found -> ",toks[cur_index]);
                    return false;
                }else{
                    next();
                    std::vector<AstPtr>ty;
                    while(!check(RPAREN)){
                        if(!parseType()) {
                            return false;
                        }
                        ty.push_back(m_node);
                        if(check(RPAREN)){
                            break;
                        }
                        if(!check(COMMA)) {
                            err::out("expected ',' found -> ",toks[cur_index]);
                            return false;
                        }
                        next();
                    }
                    if(!check(RPAREN)) {
                        err::out("expected ')' found -> ",toks[cur_index]);
                        return false;
                    }
                    next();
                    AstPtr ret;
                    if(check(ARROW)){
                        if(parseType()){
                            ret = m_node;
                        }
                    }
                    m_node = std::make_shared<FunType>(tok, ty, ret);

                }
            }
                break;
            case IDEN:
                if(!parseExpr()){
                    return false;
                }
                //type = m_node;
                break;
            case STAR:
            {
                bool isType  = true;
                tokt tok  = toks[cur_index];
                Token_type op = cur_token;
                next();
                if(!parseType()){
                    return false;
                }
                m_node = std::make_shared<PointerExpr>(tok,m_node,isType);
            }
                break;
            case AND_OP:
            {
                tokt tok = toks[cur_index];
                Token_type op = cur_token;
                AstPtr type;
                bool istype = false;
                next();
                if(check(AND)) {
                    err::out("expected expression invalid",toks[cur_index]);
                    return false;
                }
                if(parseType()){
                    type = m_node;
                }
                m_node = std::make_shared<RefExpr>(tok,op,type,istype);
                break;
            }
            default:
                err::out("expected expression found ->",toks[cur_index]);
                return false;
        }
                dump2(__func__);

        //m_node = type;
        return true;
    }



    bool Parser::parseLiteral() {
        dump(__func__);
        switch(cur_token) {
            case INT:
                m_node = std::make_shared<NumericLiteral>(toks[cur_index]);
                break;
            case FLOAT:
                m_node = std::make_shared<FloatLiteral>(toks[cur_index]);
                break;
            case TRUE:
            case FALSE:
                m_node = std::make_shared<BoolLiteral>(toks[cur_index]);
                break;
            case NIL:
                m_node = std::make_shared<NullLiteral>(toks[cur_index]);
                break;
            case CHAR:
            case STR:
                m_node = std::make_shared<StringLiteral>(toks[cur_index],(toks[cur_index].tok_type == CHAR?true:false));
                break;
            default:
                err::out("expected 'literal' found -> ",toks[cur_index]);
                return false;
        }
        next();
        dump2(__func__);
        return true;
    }










bool Parser::parseSemiConsumedExpr() {
    dump(__func__);
    if(check(IDEN)) {
        if(!parseIdenExp()){
            return false;
        }
    }else if(check(STAR)) {
        if(!parsePrefixExpr()){
            return false;
        }
    }else if(check(LPAREN)) {
        if(!parseParenExpr()) {
            return false;
        }
    }else {
        err::out("expected expression is invalid -> ",toks[cur_index]);
        return false;
    }

    if(!parseSpecialExpr()){
        return false;
    }

    if(AssignOP(cur_token)) {
        if(!parseAssignment()){
            return false;
        }
    }
    if(!check(SCOL)){
        err::out("expected ';' found -> ",toks[cur_index]);
        return false;
    }
    next();
    dump2(__func__);
    return true;
}

bool Parser::parsePathExpr() {
        dump(__func__);
        AstPtr right,left; 
        tokt tok = toks[cur_index];
        left = m_node;

        while(check(COLCOL)){
            next();
            if(!parseExpr()){
                err::out("expected 'identifier' found -> ",toks[cur_index]);
                return false;
            }
            right = m_node;
            m_node = std::make_shared<Path>(tok, left, right);
        }
        dump2(__func__);

        return true;
}

bool Parser::parseRangeExpr() {
    dump(__func__);
    AstPtr right,left; 
    tokt tok = toks[cur_index];

    left = m_node;

    while(check(DOTDOT)){
        next();
        if(check(IDEN)&&!parseIdenExp()){
            return false;
        }else if(isLiteral(cur_token)&&!parseLiteral()){
            return false;
        }else if(check(LPAREN)&&!parseParenExpr()){
            return false;
        }
        right = m_node;
        m_node = std::make_shared<Variadic>(tok, left, right);
    }
    dump2(__func__);

    return true;
}

bool Parser::parseCastExpr(){
    dump(__func__);
    tokt tok = toks[cur_token];
    AstPtr left = m_node;
    while(check(AS)){
        next();
        if(PreDefType(cur_token)&&!parseType()){
            err::out("expected 'type' found -> ",toks[cur_index]);
            return false;
        }
    }
    AstPtr right = m_node;
    m_node = std::make_shared<AsState>(tok,left,right);
            dump2(__func__);

    return true;
}

bool Parser::parseAssignment() {
    dump(__func__);
    AstPtr right,left; 
    tokt tok = toks[cur_index];
    left = m_node;
    while(AssignOP(cur_token)){
        next();
        if(!parseExpr()){
            err::out("expected 'identifier' found -> ",toks[cur_index]);
            return false;
        }
        right = m_node;
        m_node = std::make_shared<AssignmentExpr>(tok, left, right);
    }
    dump2(__func__);
    return true;
}


bool Parser::parseSpecialExpr() {
    if(check(DOTDOT)) {
        if(!parseRangeExpr()) {
            return false;
        }
    }else if(check(COLCOL)) {
        if(!parsePathExpr()) {
            return false;
        }
    }else if(check(AS)) {
        if(!parseCastExpr()) {
            return false;
        }
    }
    return true;
}

bool Parser::parseExpr() {
    dump(__func__);

    if(UnaryOP(cur_token)){
        if(!parsePrefixExpr()){
            return false;
        }
    }else if(check(IDEN)){
        if(checkh(LBRACE)){
            next();
            if(!parseStructExpr()){
                return false;
            }
            return true;
        }
        if(!parseIdenExp()){
            return false;
        }
    }else if(check(LPAREN)){
        if(!parseParenExpr()){
            return false;
        }
    }else if(check(LBRACK)){
        if(!parseArrayExpr()){
            return false;
        }
        return true;
    }else if(isLiteral(cur_token)){
        if(!parseLiteral()){
            return false;
        }
    }

    if(!parseSpecialExpr()){
        return false;
    }

    if(BineryOP(cur_token)){
        if(!parseBineryExpr(m_preced)){
            return false;
        }
    }else if(AssignOP(cur_token)){
        if(!parseAssignment()){
            return false;
        }
    }

    dump2(__func__);
    return true;
}

bool Parser::parseBineryLRExpr() {
   if((check(IDEN)&&!check(LBRACE))||isLiteral(cur_token)||
        check(STAR)||check(MINUS)||check(LPAREN)) {
        if(!parseExpr()){
            return false;
        }
   }else{
        err::out("expected binery expression found -> ",toks[cur_index]);
        return false;
   }

   return true;
}

bool Parser::parseCallExpr() {
    dump(__func__);

    if(!parseFuncCall()){
        return false;
    }

    if(check(DOT)||check(ARROW)){
        if(!parseDotOrArrow()){
            return false;
        }
    }else if(check(LBRACK)) {
        if(!parsefullArrayexpr()){
            return false;
        }
    }
    dump2(__func__);

    return true;
}

bool Parser::parsefullArrayexpr() {
        dump(__func__);

    if(!parseArrayAccess()){
        return false;
    }

    if(check(DOT)||check(ARROW)){
        if(!parseDotOrArrow()){
            return false;
        }
    }else if(check(LPAREN)) {
        if(!parseCallExpr()){
            return false;
        }
    }
    dump2(__func__);

    return true;
}

bool Parser::parseDotOrArrow() {
    dump(__func__);
    AstPtr right,left; 
    tokt tok = toks[cur_index];
    Token_type op = cur_token;
    left = m_node;
    //while(check(DOT)||check(ARROW)){
        next();
        if(isLiteral(cur_token)){
            if(!parseLiteral()){
                return false;
            }
        }else if(check(IDEN)&&!parseIdenExp()){
            err::out("expected expression found -> ",toks[cur_index]);
            return false;
        }
        right = m_node;
        m_node = std::make_shared<MemberExpr>(tok, left, op, right);
    //}
    dump2(__func__);

    return true;
}


bool Parser::parseIdenExp() {
    dump(__func__);

    parseIdentifier();
    if(check(LPAREN)){
        if(!parseCallExpr()){
            return false;
        }
    }else if(check(LBRACK)){
        if(!parsefullArrayexpr()){
            return false;
        }
    }else if(check(DOT)||check(ARROW)){
        if(!parseDotOrArrow()){
            return false;
        }
    }
    dump2(__func__);

    return true;
}

bool Parser::parsePointerExpr() {
    dump(__func__);

    bool isType = false;
    Token_type op = cur_token;
    tokt tok = toks[cur_index];
    AstPtr base;
    next();
    if(check(STAR)){
        parsePrefixExpr();
    }else if(check(LPAREN)) {
        if(!parseParenExpr()){
            return false;
        }
    }else if(check(IDEN)) {
        if(!parseIdenExp()){
            return false;
        }
    }
    base = m_node;
    m_node = std::make_shared<PointerExpr>(tok,base, isType);
    
    dump2(__func__);
    return true;
}


bool Parser::parseRefExpr() {
    dump(__func__);

    bool isType = false;
    Token_type op = cur_token;
    tokt tok = toks[cur_index];
    AstPtr base;
    next();
    if(check(LBRACK)){
        if(!parseArrayExpr()){
            return false;
        }
    }else if(check(LPAREN)) {
        if(!parseParenExpr()){
            return false;
        }
    }else if(check(IDEN)) {
        if(!parseIdenExp()){
            return false;
        }
    }
    base = m_node;
    m_node = std::make_shared<RefExpr>(tok,op, base,isType);
    
    dump2(__func__);
    return true;
}



bool Parser::parsePrefixExpr() {
    dump(__func__);

    if(check(STAR)){
        if(!parsePointerExpr()){
            return false;
        }
    }else if(check(AND_OP)){
        if(!parseRefExpr()){
            return false;
        }
    }else if(check(MINUS)){
        if(check(IDEN)){
            if(!parseIdenExp())
                return false;
        }else if(isLiteral(cur_token)) {
            if(!parseLiteral()){
                return false;
            }
        }else if(check(LPAREN)) {
            if(!parseParenExpr()){
                return false;
            }
        }
    }else {
        return false;
    }
    dump2(__func__);

    return true;
}


bool Parser::parseParenExpr() {
    next();
    dump(__func__);
    int old = m_preced;
    m_preced = 0;
    AstPtr node;
    if(check(RPAREN)){
        err::out("expected expression found -> ",toks[cur_index]);
        return false;
    }else if(!parseExpr()){
        return false;
    }
    node = m_node;
    if(check(COMMA)) {
        bool isType = false;;
        tokt tok = toks[cur_index];
        std::vector<AstPtr>vals;
        vals.push_back(node);
        if(!check(RPAREN)) {
            next();
            while(!check(RPAREN)){ 
                m_preced = 0;
                if(!parseExpr()){
                    err::out("expected expression found -> ",toks[cur_index]);
                    return false;
                }
                vals.push_back(m_node);
                if(check(RPAREN)){
                    break;
                }
                if(!check(COMMA)){
                    err::out("expected ',' found -> ",toks[cur_index]);
                    return false;
                }
                next();   
            }

        } 
        if(cur_token != RPAREN){
            err::out("expected ')' found -> ",toks[cur_index]);
            return false;
        }
        next(); 
        node = std::make_shared<Tuple>(tok,vals,isType);
        m_preced = old;
        m_node = node;
                        dump2(__func__);

        return true;
    }

    if(cur_token != RPAREN){
        err::out("expected ')' found -> ",toks[cur_index]);
        return false;
    } 
    next();
    m_preced = old;
    m_node = node;
    m_node = std::make_shared<GroupedExpr>(m_node);
            dump2(__func__);

    return true;
}

bool Parser::parseBineryExpr(int prev_prece) {
    dump(__func__);
    tokt tok = toks[cur_index];
    Token_type opr;
    AstPtr right,left;
    left = m_node;
    if(m_node == nullptr){
        if(!parseBineryLRExpr()){
            return false;
        }
        left = m_node;
    }else
        left = m_node;

    //2+3*3/4+2*3
    while(BineryOP(cur_token)) {
        opr = cur_token;
        m_preced = preced(opr);
        if(prev_prece > m_preced) {
            std::cout<<"return ------======"<<m_preced<<" "<<prev_prece<<std::endl;
            m_node = left;
            return true;
        }
        next();
        m_node = nullptr;
        if(parseBineryExpr(m_preced + 1)){
            right = m_node;
        }
        left = std::make_shared<BineryExper>(tok, left, opr, right);
        m_preced = 0;
    }
    m_node = left;
            dump2(__func__);

    return true;
}



















    bool Parser::parseTupleType() {
        dump(__func__);
        bool isType = true; 
        tokt tok = toks[cur_index];
        std::vector<AstPtr>types;
        if(!check(LPAREN)){
            err::out("expected '(' found -> ",toks[cur_index]);
            return false;
        }
        next();

        if(!check(RPAREN)){
            while(!check(RPAREN)){
                if(!parseType()){
                    return false;
                }
                types.push_back(m_node);
                if(check(RPAREN)){
                    break;
                }
                if(!check(COMMA)){
                    err::out("expected ',' found -> ",toks[cur_index]);
                    return false;
                }
                next(); 
            }
        }
        if(!check(RPAREN)){
            err::out("expected ')' found -> ",toks[cur_index]);
            return false;
        }
        next();
        m_node = std::make_shared<Tuple>(tok, types,isType);
                dump2(__func__);

        return true;
    }


    bool Parser::parseBlockStatement() {
        dump(__func__);
        std::vector<AstPtr> statms;
        
        if(!check(LBRACE)){
            err::out("expected '{' found ->",toks[cur_index]);
            return false;
        }
        next();

        if(!check(RBRACE)){
            while(!check(RBRACE)) {
                if(!parseStatement()){
                    return false;
                }
                statms.push_back(m_node);
                if(check(FEOF)){
                    return false;
                }
                if(check(RBRACE)){
                    break;
                }
                
            } 
        }
        
        if(!check(RBRACE)){
            err::out("expected '}' found -> ",toks[cur_index]); 
            return false;
        }       
        next();
        m_node = std::make_shared<BlockStatement>(statms);
                dump2(__func__);

        return true;
    }


    bool Parser::parseTypeStatm() {
        dump(__func__);
        tokt tok = toks[cur_index];
        if(!check(TYPE)){
            err::out(" expected keyword 'type' found -> ", toks[cur_index]);     
            return false;
        }
        next();
        if(!check(IDEN)){
            err::out(" expected 'identifier' found -> ", toks[cur_index]);     
            return false;
        }
        parseIdentifier();
        AstPtr left = m_node;
        
        if(!check(COL)){
            err::out(" expected ':' found -> ", toks[cur_index]);     
            return false;
        }
        next();

        AstPtr right;
        if(!parseType()){
            err::out(" expected 'type specifier' found -> ", toks[cur_index]);     
            return false;
        }
        right = m_node; 

        if(!check(SCOL)){
            err::out(" expected ';' found -> ", toks[cur_index]);     
            return false;
        }
        next();

        m_node = std::make_shared<TypeState>(tok, left, right);
                dump2(__func__);

        return true;
    }


    bool Parser::parseArrayType() {
        dump(__func__);
        std::vector<AstPtr>d;
        AstPtr type;
        tokt tok = toks[cur_index];

        next();
        if(check(RBRACK)){
            err::out("expected '[' found -> ",toks[cur_index]);
            return false;
        } else {
            while(!check(RBRACK)){
                //todo
                if(!parseExpr()){
                    err::out("expected expression found -> ",toks[cur_index]);
                    return false;
                }
                d.push_back(m_node);
                if(check(RBRACK)){
                    break;
                }
                if(!check(SCOL)){
                    err::out("expected ';' found -> ",toks[cur_index]);
                    return false;
                }
                next();
            }
        }
        if(!check(RBRACK)){
            err::out("expected ']' found -> ",toks[cur_index]);
            return false;
        }
        next();
        if(parseType()){
            type = m_node;
        }
                    
        m_node = std::make_shared<ArrayType>(tok, d, type);
                dump2(__func__);

        return true;
    }



    bool Parser::parseArrayAccess() {
        dump(__func__);
        AstPtr sig = m_node;
        std::vector<AstPtr>e;
        if(!check(LBRACK)){
            err::out("expected '[' found -> ",toks[cur_index]);
            return false;
        }
        next();
        
        if(check(RBRACK)){
             err::out("expected expression found -> ",toks[cur_index]);
             return false;
        } 
           
        while(!check(RBRACK)){
            if(!parseExpr()) {
                err::out("expected expression invalid -> ",toks[cur_index]);
                return false;
            }
            e.push_back(m_node);
            if(check(RBRACK)){
                break;
            }
            if(!check(SCOL)){
                err::out("expected ';' found -> ",toks[cur_index]);
                return false;
            }else{
                next();
            }
        }
        
        if(cur_token != RBRACK){
            err::out("expected ']' found -> ",toks[cur_index]);
            return false;
            
        }
        next();
        m_node = std::make_shared<IndexExpr>(sig,e);
                dump2(__func__);


        return true;
    }

    bool Parser::parseArrayExpr() {
        dump(__func__);
        tokt tok = toks[cur_index];
        std::vector<AstPtr>vals;
        next();
        if(!check(RBRACK)){
            while(!check(RBRACK)){
                m_preced = 0;
                if(parseExpr()){
                    vals.push_back(m_node);
                }else{
                    err::out("expected array exression is invalid -> ",toks[cur_index]);   
                    return false;
                }
                if(check(RBRACK)){
                    break;
                }
                if(!check(COMMA)){
                    err::out("expected ',' found -> ",toks[cur_index]);   
                    return false;
                }
                next();
            }

            if(!check(RBRACK)){
                err::out("expected ']' found -> ",toks[cur_index]);   
                return false;
            }
        }

        next();

        m_node = std::make_shared<ListExpr>(tok,vals);
                dump2(__func__);

        return true;
    }


    bool Parser::parseStructExpr() {  
        dump(__func__);      
        bool isDecl = false;;
        tokt tok = toks[cur_index];
        std::vector<AstPtr> e;
        AstPtr sig = m_node;
        if(!check(LBRACE)){
            err::out("expected '{' found -> ",toks[cur_index]);
            return false;
        }
        next();

        if(!check(RBRACE)){
            while(!check(RBRACE)){
                AstPtr key,val;
                m_preced = 0;
                if(parseExpr()){
                    key = m_node;
                }
                if(check(COL)) {
                    next();
                    if(!parseExpr()){
                        err::out("expected 'value' found -> ",toks[cur_index]);
                        return false;
                    }
                    val = m_node;
                    e.push_back(std::make_shared<Parameter>(key,val));
                }else {
                    err::out("expected ':' found -> ",toks[cur_index]);
                    return false;
                }
                if(check(RBRACE)){
                    break;
                }
                if(!check(COMMA)){
                    err::out("expected ',' found -> ",toks[cur_index]);
                    return false;
                }
                next();
            }
        }

        if(!check(RBRACE)) {
            err::out("expected '}' found -> ",toks[cur_index]);
            return false;
        }
        next();
        m_node = std::make_shared<StructState>(tok,sig,e,isDecl);
                dump2(__func__);

        return true;
    }
// unary expression = expression

    bool Parser::parseFuncCall() {
        dump(__func__);
        tokt tok = toks[cur_index];
        std::vector<AstPtr> args;
        AstPtr sig = m_node;

        if(!check(LPAREN)){
            err::out("expected '(' found -> ",toks[cur_index]);
            return false;
        }
        next();
   
        if(!check(RPAREN)) {
            int prec_old = m_preced;
            while(!check(RPAREN)) {
                m_preced = 0;
                if(!parseExpr()){
                    err::out("expected expression invalid -> ",toks[cur_index]);
                    return false;
                }
                args.push_back(m_node);
                if(check(RPAREN)){
                    break;
                }
                if(!check(COMMA)){
                    err::out("expected ',' found -> ",toks[cur_index]);
                    return false;
                }
                next();

            }
            int m_preced = prec_old;
        }

        if(cur_token != RPAREN){
            err::out("expected ')' found -> ",toks[cur_index]);
            return false;
        }else
           next();
        
        m_node = std::make_shared<FunctionCall>(tok, sig, args);
                dump2(__func__);

        return true;
    }


    bool Parser::parseTypeValuePair() {
        dump(__func__);
        tokt tok = toks[cur_index];
        AstPtr iden,type;
        
        if(parseIdentifier()){
            iden = m_node;
        } else {
            err::out("expected 'identifier' found -> ",toks[cur_index]);
            return false;
        }
        if(!check(COL)){
            err::out("expected \':\' found ->",toks[cur_index]);
            return false;
        }else{
            next();
            if(!parseType()){
                return false;
            }
            type = m_node;
        }
        m_node = std::make_shared<Parameter>(iden, type);
                dump2(__func__);

        return true;
    }

    bool Parser::parseStruct() {
        dump(__func__);
        bool isDecl = true;
        tokt tok = toks[cur_index];
        std::vector<AstPtr> element;
        AstPtr sig;
        if(!check(STRUCT)) {
            err::out("expected keyword 'struct' found ->",toks[cur_index]);
            return false;
        }
        next();
        if(!check(IDEN)) {
            err::out("expected expression 'identifier' found -> ",toks[cur_index]);
            return false;
        }else{
            parseIdentifier();
            sig = m_node;
        }

        if(!check(LBRACE)) {
            err::out("expected '{' found -> ",toks[cur_index]);
            return false;
        }
        next();

        if(check(RBRACE)){
            err::out("expected expression invalid -> ",toks[cur_index]);
            return false;
        }


        while(cur_token !=  FEOF && !check(RBRACE)){
                
                if(parseTypeValuePair()){
                    element.push_back(m_node);
                }
                if(check(RBRACE)){
                    break;
                }
                if(!check(COMMA)){
                    err::out("expected ',' found -> ",toks[cur_index]);
                    return false;
                }else
                    next();
        }

        if(!check(RBRACE)){
            err::out("expected '}' found -> ",toks[cur_index]);
            return false;
        }
        next();

        if(!check(SCOL)){
            err::out("expected '}' found -> ",toks[cur_index]);
            return false;
        }
        next();
        m_node = std::make_shared<StructState>(tok, sig, element,isDecl);
                dump2(__func__);

        return true;
    }



    bool Parser::parseReturn() {
        dump(__func__);
        tokt tok = toks[cur_index];
        AstPtr val;
        next();

        if(!check(SCOL)){

            if(!parseExpr()) {
                return false;
            }
            val = m_node;
        }
        if(!check(SCOL)){
                err::out("expected ';' found -> ",toks[cur_index]);
                return false;
        }

        next();
        m_node = std::make_shared<ReturnState>(tok, val);
                dump2(__func__);

        return true;
    }


    bool Parser::parseIfStatm() {
        dump(__func__);
        if(!check(IF)){
            err::out("expected if ",toks[cur_index]);   
            return false;
        }
        tokt tok = toks[cur_index];
        next();
        AstPtr condition;
        AstPtr if_;
        AstPtr else_;

        if(check(LBRACE)) {
            err::out("expected if expression is invalid -> ",toks[cur_index]);
            return false;
        } else {
            if(!parseExpr()){
                return false;
            }
            condition = m_node;
        }

        if(!check(COL)){
            err::out("expected ':' found -> ",toks[cur_index]);
            return false;
        }
        next();

        if(!check(LBRACE)) {
            err::out("expected '{' found -> ",toks[cur_index]);
            return false;
        }

        if(parseBlockStatement()){
            if_ = m_node;
        }

        if(check(ELSE)) {
            next();
            switch(cur_token){
                case IF:
                    if(!parseIfStatm()){
                        return false;
                    }
                    else_ = m_node;
                    break;
                case LBRACE:
                    if(!parseBlockStatement()){
                        return false;
                    }
                    else_ = m_node;
                    break;
                default:
                    err::out("invalid else expression ",toks[cur_index]);
                    return false;

            }
        }
        m_node = std::make_shared<IfStatement>(tok,condition, if_, else_);
                dump2(__func__);

        return true;
    }


    bool Parser::parseFor() {
        dump(__func__);
        tokt tok = toks[cur_index];
        AstPtr left,right;
        AstPtr body;
        if(!check(FOR)) {
            err::out("expected keyword 'for' found -> ",toks[cur_index]);
            return false;
        }
        next();
        if(!parseIdentifier()) {
            return false;
        }
        left = m_node;
        if(!check(IN)){
            err::out("expected keyword 'in' found -> ",toks[cur_index]);
            return false;
        }
        next();
        

        if(check(LBRACE)){
            err::out("expected expression found -> ",toks[cur_index]);
             return false;
        }
          
        if(!parseExpr()) {
            err::out("unexpected expression -> ",toks[cur_index]);
            return false;
        }
        right = m_node;
        
        if(!check(COL)){
            err::out("expected ':' found -> ",toks[cur_index]);
             return false;
        }
        next();

        if(!parseBlockStatement()){
            return false;
        }
        body = m_node;            

        m_node = std::make_shared<ForInLoop>(tok, left, right, body);
                dump2(__func__);

        return true;
    }


    bool Parser::parseWhile() {
        dump(__func__);
        tokt tok = toks[cur_index];
        AstPtr expr;
        AstPtr body;
        if(!check(WHILE)) {
            err::out("expected keyword 'while' found -> ",toks[cur_index]);
            return false;
        }
        next();
        
        if(check(LBRACE)){
            err::out("expected expression found -> ",toks[cur_index]);
             return false;
        }
          
        if(!parseExpr()) {
            err::out("unexpected expression -> ",toks[cur_index]);
            return false;
        }
        expr = m_node;
        
        if(!check(COL)){
            err::out("expected expression found -> ",toks[cur_index]);
             return false;
        }
        next();

        if(!parseBlockStatement()){
            return false;
        }
        body = m_node;            

        m_node = std::make_shared<WhileLoop>(tok, expr, body);
                dump2(__func__);

        return true;
    }


    bool Parser::parseFuncdef() {
        dump(__func__);
        tokt tok = toks[cur_index];
        AstPtr sig;
        std::vector<AstPtr>p;
        AstPtr ret;
        AstPtr body;

        if(!check(FN)) {
            err::out("expected keyword 'fn' found ->\'",toks[cur_index]);
            return false;
        }
        next();

        if(check(IDEN)){
            parseIdentifier();
            sig = m_node;
        }else{
            err::out("expected function 'identifier' found ->  \'",toks[cur_index]);
            return false;
        }

        if(check(LPAREN)) {
            next();
            while(!check(RPAREN)) {
                if(!parseTypeValuePair()) {
                    return false;
                }
                p.push_back(m_node);
                if(check(RPAREN)){
                    break;
                }
                if(!check(COMMA)) {
                    err::out("expected \',\' found -> \'",toks[cur_index]);
                    return false;
                }
                next();
            }
        }else{
            err::out("expected function expression -> ",toks[cur_index]);
            return false;
        }

        if(!check(RPAREN)){
            err::out("expected ')' found -> ",toks[cur_index]);
            return false;
        }
        next();
        if(check(ARROW)){
            next();
            if(!parseType()){
                err::out("expected 'type' found -> ",toks[cur_index]);
                return false;
            }
            ret = m_node;
        }

        if(check(LBRACE)) {
            if(!parseBlockStatement()){
                return false;
            }
            body = m_node;
        }else if(check(SCOL)){
            next();
        } else {
            err::out("expected '{' found -> ",toks[cur_index]);
            return false;
        }
        m_node = std::make_shared<FunctionDef>(tok,sig,p,ret,body);
                dump2(__func__);

        return true;
    }


    bool Parser::parseLetStatm() {
        dump(__func__);
        tokt tok = toks[cur_index];
        AstPtr v;
        AstPtr type;
        AstPtr val;
        if(!check(LET)) {
            err::out("expected keyword 'let' found -> \'",toks[cur_index]);
            return false;
        }
        next();
        
        if(check(IDEN)) {
            parseIdentifier();
            v = m_node;
        } else {
            err::out("expected expression identifier\'",toks[cur_index]);
            return false;
        }


        if(check(SCOL)) {
            err::out("expected exprssion 'type' require found -> \'",toks[cur_index]);
            return false;
        }else if(check(COL)) {
            next();
            if(!parseType()){
                err::out("expected 'type' found -> ",toks[cur_index]);
                return false;
            }
            type = m_node;
        }

        if(check(ASSN)) {
            next();
            if(!parseExpr()){
                err::out("expected expression found -> ",toks[cur_index]);
                return false;
            }
            val = m_node;
        }else if(!check(SCOL)){
            err::out(" -> ",toks[cur_index]);
            return false;
        }
        
        if(check(SCOL)) {
            next();
        } else {
            err::out("expected ';'found -> ",toks[cur_index]);
            return false;
        }

        m_node = std::make_shared<VarState>(tok, v, type, val);
                dump2(__func__);

        return true;
        
    }
    

    bool Parser::parseConst() {
        dump(__func__);
        tokt tok = toks[cur_index];
        
        if(!check(CONST)){
            err::out("expected keyword 'const' found -> ",toks[cur_index]);  
            return false;
        }
        next();

        AstPtr name;
        if(parseIdentifier()){
            name = m_node;
        }

        AstPtr type;
        if(parseType()){
            type = m_node;
        }

        AstPtr val;
        if(check(ASSN)){
            next();
            if(parseExpr()){
                val = m_node;
            }
        }else {
            err::out("expected const ",toks[cur_index]);
            return false;
        }

        if(!check(SCOL)){
            err::out("expected ';' found -> ",toks[cur_index]);
            return false;
        }
        next();

        m_node = std::make_shared<VarState>(tok,name,type,val);
                dump2(__func__);

        return true;

    }
    
}



