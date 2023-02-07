#include"../../include/parser/p.hpp"
#include"../../include/Error.hpp"

namespace parser {  
    AstPtr Parser::parse() {
        std::vector<AstPtr>statms;
        tokt tok = toks[cur_index];
        cur_token = toks[cur_index].tok_type;
        while(cur_token != FEOF){
            AstPtr statm;
            m_preced = 0;
            std::cout<<"statmen starting "<<toks[cur_index].data<<std::endl;
            parseStatement();
            statms.push_back(m_node);
            if(cur_token == SCOL)
                next();
        }
        return std::make_shared<Program>(tok,statms);
    }


    bool Parser::parseStatement() {
        switch(cur_token){
            case FOR:
                break;

            case IF:
                break;

            case LET:
                parseLetStatm();
                break;

            case RETURN:

                break;

            case CONTINUE:
            case BREAK:
                m_node = std::make_shared<BranchState>(toks[cur_index]);
                next();
                break;

            case CONST:
                break;


            case STRUCT:
                break;

            case ENUM:

                break;

            case FN:
                break;
            case TYPE:
                break;
            case EXTERN:

                break;
            case USE:
            default:
                break;
        }
        return true;
    }

    bool Parser::parseExtern() {
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
        if(check(LBRACE)){
            next();
            std::vector<AstPtr>v;
            while(!check(RBRACE)) {
                if(parseStatement()){
                    v.push_back(m_node);
                }
                next();
            } 

            block = std::make_shared<BlockStatement>(v);
            
            if(!check(RBRACE)){
                err::out("expected '}' found -> ",toks[cur_index]);
                return false;
            }
        }else{
            err::out("expected '{' found -> ",toks[cur_index]);
            return false;
        }
        m_node = std::make_shared<Extern>(tok,lib,block);
        return true;
    }

    bool Parser::parseIdentifier() {
        if(!check(IDEN)){
            err::out("expected 'identifier' found -> ",toks[cur_index]);
            return false;
            return false;
        }else{
            m_node = std::make_shared<Identifier>(toks[cur_index],toks[cur_index].data);
        }
        return true;
    }


    bool Parser::parseType() {
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
            case F32:
            case F64:
            case STRING:
            case BOOL:
                m_node = std::make_shared<PreDefType>(toks[cur_index]);
                next();
                break;
            case LBRACK:
                if(parseArrayType()){
                    type = m_node;
                }
                break;
            case LPAREN:
                if(parseTupleType()){
                    type = m_node;
                }
                break;
            case DOTDOT:
                type = std::make_shared<Variadic>(toks[cur_index], true);
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
                        if(parseType()) {
                            ty.push_back(m_node);
                        }
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
                if(parsePrimaryExpr()){
                    type = m_node;
                }
                break;
            case MUL:
            {
                tokt tok  = toks[cur_index];
                Token_type op = cur_token;
                next();
                if(parseType()){
                    type = m_node;
                }
                type = std::make_shared<PointerExpr>(tok,type,op,true);
            }
                break;
            // case AND_OP:
            // {
            //     tokt tok = toks[cur_index];
            //     Token_type op = cur_token;
            //     next();
            //     if(check(AND)) {
            //         err::out("expected expression invalid",toks[cur_index]);
            //         return false;
            //     }
            //     if(parseType()){
            //         type = m_node;
            //     }
            //     m_node = std::make_shared<RefType>(tok,op,type);
            //     break;
            // }
            default:
                err::out("expected expression found ->",toks[cur_index]);
                return false;
        }
        m_node = type;
        return true;
    }



    bool Parser::parseLiteral() {

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
        return true;
    }



    bool Parser::parseBineryExpr(int prev_prece) {
        tokt tok = toks[cur_index];
        Token_type opr;
        AstPtr right,left;
        if(m_node != NULL){
            left = m_node;
        }else if(parsePrimaryExpr()){
            left = m_node;
        }else{
            return false;
        }

        //2+3*3/4+2*3
        while(BineryOP(cur_token)) {
            opr = cur_token;
            m_preced = preced(opr);
            if(prev_prece > m_preced) {
                m_node = left;
                return true;
            }
            next();
            m_node = NULL;
            if(parseBineryExpr(m_preced + 1)){
                right = m_node;
            }
            left = std::make_shared<BineryExper>(tok, left, opr, right);
            m_preced = 0;
        }
        m_node = left;
        return true;
    }
// *a = b.call()[i] + *a + 5 + (1+*b.c)
/* 
    *& -> iden -> () [] . .. ->

    iden ->
    *iden ->
    &.. -> 

    *+-& iden ();
    iden () [] +-. ...;
    123 .. +- ;
   iden()
   iden[]{.->} () +-* ..
*/


    bool Parser::parseExpr8() {
        AstPtr node;
        if(check(MUL)||check(AND_OP)){
            if(!parsePrefixExpr()){
                return false;
            }
            if(AssignOP(cur_token)){
                if(!parseExpr5()){
                    return false;
                }
            }else if(!isTerminal(cur_token)){
                return false;
            }
        }else if(check(IDEN)){
            parseIdentifier();
            if(check(LPAREN)||check(LBRACK)){
                if(!parseExpr2()){
                    return false;
                }
            }else if(check(DOT)||check(ARROW)||check(COLCOL)){
                if(!parseExpr3()){
                    return false;
                }
            }else if(AssignOP(cur_token)){
                if(!parseExpr5()){
                    return false;
                }
            }else if(!isTerminal(cur_token)){
                return false;
            }
        }else if(check(LPAREN)){
            if(!parseParenExpr()){
                return false;
            }
        }else{
            return false;
        }
        return true;
    }


    bool Parser::parseExpr1() {
        AstPtr node;
        if(UnaryOP(cur_token)){
            if(!parsePrefixExpr()){
                return false;
            }
            node = m_node;
            
        }else if(check(IDEN)){
            parseIdentifier();
            node = m_node;

            if(check(LPAREN)||check(LBRACK)){

            }else if(check(LBRACE)){
                if(!parseStructExpr()){
                    return false;
                }
            }else if(BineryOP(cur_token)){
                
            }else if(AssignOP(cur_token)){

            }else if(check(DOTDOT)||check(DOT)||check(ARROW)||check(COLCOL)){
                if(!parseExpr3()){
                    return false;
                }
            }else if(check(AS)){

            }

        }else if(isLiteral(cur_token)){
            parseLiteral();
            node = m_node;
            if(BineryOP(cur_token)){
                
            }else if(check(DOTDOT)){

            }
        }else{
            return false;
        }

        if(!isTerminal(cur_token)){
            return true;
        }
        return true;
    }



    bool Parser::parseExpr2() {
        while(check(LPAREN)||check(LBRACK)){
            if(check(LPAREN)){
                if(!parseFuncCall()){
                    return false;
                }
            }else if(check(LBRACK)){
                if(!parseArrayAccess()){
                    return false;
                }
            }else{
                break;
            }
        }
            
        if(BineryOP(cur_token)){
            
        }else if(AssignOP(cur_token)){

        }else if(check(DOTDOT)||check(DOT)||check(ARROW)){

        }else if(check(AS)){

        }else{

        }
        return true;
    }

    bool Parser::parseExpr3() {
        AstPtr right,left; 
        tokt tok = toks[cur_index];
        if(m_node!=NULL){
            left = m_node;
        }  
        right = m_node;

        while(check(DOT)||check(ARROW)||check(DOTDOT)||check(COLCOL)){
            if(check(DOT)||check(ARROW)){
                next();
                if(!check(IDEN)&&!parseExpr1()){
                    err::out("expected 'identifier' found -> ",toks[cur_index]);
                    return false;
                }
                m_node = std::make_shared<MemberExpr>(tok, left, right);
            }else if(check(DOTDOT)){
                next();
                if(!parseExpr1()){
                    err::out("expected expression found -> ",toks[cur_index]);
                    return false;
                }
                m_node = std::make_shared<Variadic>(tok, left, right);
            }else if(check(COLCOL)){
                //todo
            }else{
                break;
            }
        }

        if(AssignOP(cur_token)){
            if(!parseExpr5()){
                return false;
            }
        }else if(BineryOP(cur_token)){
            if(!parseBineryExpr(m_preced)){
                return false;
            }
        }else if(!parseExpr7()){}
        return true;
    }

    bool Parser::parseExpr4(){ 
        
        return true;
    }

    bool Parser::parseExpr5() {
        tokt tok = toks[cur_index];
        AstPtr left = m_node;
        AstPtr right;
        next();
        if((check(LPAREN)||check(LBRACK))){
            if(!parseExpr6()){
                return false;
            }
        }else if(check(IDEN)){
            if(checkh(LBRACE)){

            }else if(!parseExpr6()){
                return false;
            }
        }else if(isLiteral(cur_token)&&parseExpr1()){

        }else{
            err::out("expected expression found -> ",toks[cur_index]);
            return false;
        }
        right = m_node;
        m_node = std::make_shared<AssignmentExpr>(tok,left,right);
        return true;
    }

    bool Parser::parseExpr6() {
        if(check(LPAREN)){
            if(!parseParenExpr()){
                return false;
            }
            if(BineryOP(cur_token)){

            }else if(isTerminal(cur_token)){

            }else{

            }
        }else if(check(LBRACK)){
            if(!parseArrayExpr()){
                return false;
            }
            if(!isTerminal(cur_token)){

            }
        }else if(!parseExpr1()){
            return false;
        }
        return true;
    }

    bool Parser::parseExpr7() {
        if(isTerminal(cur_token)){

        }
        return true;
    }


    bool Parser::parseRefExpr(){
        switch(cur_token){
            case IDEN:
            {
                parseIdentifier();
                next();
                switch (cur_token)
                {
                case LBRACK:
                    if(!parseArrayAccess()){
                        return false;
                    }
                    break;
                case LBRACE:
                    if(!parseStructExpr()){
                        return false;
                    }   
                    break;
                case LPAREN:
                    if(!parseFuncCall()){
                        return false;
                    }
                default:
                    break;
                }
            }
            case LBRACK:
            {
                if(!parseArrayExpr()){
                    return false;
                }
            }
                break;
            case LPAREN:
            {
                if(!parseParenExpr()){
                    return false;
                }
            }
                break;
            case MUL:
            {
                if(!parsePointerExpr()){
                    return false;
                }
            }
                break;
            default:
            {    
                return false;
            }
        }

        return true;
    }

    bool Parser::parsePointerExpr(){
        if(check(IDEN)){
            parseIdentifier();
            if(check(LBRACK)){

            }else if(check(LPAREN)){

            }else if(check(DOT)){

            }
        }
        return true;
    }


    bool Parser::parsePrefixExpr() {
        Token_type op = cur_token;
        tokt tok = toks[cur_index];
        AstPtr base;
        if(check(MUL)){
            next();
            if(check(MUL)){
                parsePrefixExpr();
                base = m_node;
            }else if(!parsePointerExpr()){
                return false;
            }
            base = m_node;
            m_node = std::make_shared<PointerExpr>(tok,base,op, false);
            return true;
        }else if(check(AND_OP)){
            next();
            if(!parseRefExpr()){
                err::out("expected expression is invalid -> ",toks[cur_index]);
                return false;
            }
            base = m_node;
            m_node = std::make_shared<RefExpr>(tok,base,op);
            return true;
        }else if(parsePrimaryExpr()) {            
            base = m_node;
        }else{
            return false;
        }

        m_node = std::make_shared<PrefixExper>(tok,base,op);
        return true;
    }
    
    
    bool Parser::parseParenExpr() {
        next();
        int old = m_preced;
        m_preced = 0;
        AstPtr node;
        parsePrimaryExpr();
        node = m_node;
        if(cur_token == COMMA) {
            tokt tok = toks[cur_index];
            std::vector<AstPtr>vals;
            vals.push_back(node);
            if(!check(RPAREN)) {
                next();
                while(!check(RPAREN)){ 
                    if(parsePrimaryExpr()){
                        vals.push_back(m_node);
                    }
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
            node = std::make_shared<Tuple>(tok,vals,false);
            m_preced = old;
            m_node = node;
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
        return true;
    }

    bool Parser::parseTupleType() {
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
        m_node = std::make_shared<Tuple>(tok, types,true);
        return true;
    }


    bool Parser::parseBlockStatement() {
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
                next();
            } 
        }
        
        if(!check(RBRACE)){
            err::out("expected '}' found -> ",toks[cur_index]); 
            return false;
        }       
        next();
        m_node = std::make_shared<BlockStatement>(statms);
        return true;
    }


    bool Parser::parseTypeStatm() {
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
        }else
            next();

        m_node = std::make_shared<TypeState>(tok, left, right);
        return true;
    }
    //fn arr[8|9|0]

    bool Parser::parseArrayType() {
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
                if(parsePrimaryExpr()){
                    d.push_back(m_node);
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
        return true;
    }



    bool Parser::parseArrayAccess() {
        AstPtr sig = m_node;
        std::vector<AstPtr>e;
        if(!check(LBRACK)){
            err::out("expected '[' found -> ",toks[cur_index]);
            return false;
        }
        next();
        
        if(check(RBRACK)){
             err::out("expected expression invalid -> ",toks[cur_index]);
             return false;
        } 
           
        while(!check(RBRACK)){
            if(parsePrimaryExpr()) {
                e.push_back(m_node);
            }
            if(check(RBRACK)){
                break;
            }
            if(!check(COMMA)){
                err::out("expected ',' found -> ",toks[cur_index]);
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

        return true;
    }

    bool Parser::parseArrayExpr() {
        tokt tok = toks[cur_index];
        std::vector<AstPtr>vals;
        next();
        if(!check(RBRACK)){
            while(!check(RBRACK)){
                if(parsePrimaryExpr()){
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
        return true;
    }


    bool Parser::parseStructExpr() {
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
                if(parsePrimaryExpr()){
                    key = m_node;
                }
                if(check(COL)) {
                    next();
                    parsePrimaryExpr();
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
                }else{
                    next();
                }
            }
        }

        if(cur_token != RBRACE) {
            err::out("expected '}' found -> ",toks[cur_index]);
            return false;
        }

        m_node = std::make_shared<StructState>(tok, sig, e,false);
        return true;
    }
// unary expression = expression

    bool Parser::parseFuncCall() {
        tokt tok = toks[cur_index];
        std::vector<AstPtr> args;
        AstPtr sig = m_node;

        if(!check(LPAREN)){
            err::out("expected '(' found -> ",toks[cur_index]);
            return false;
        }
        next();
   
        if(!check(RPAREN)) {
                
            while(!check(RPAREN)) {
                if(parsePrimaryExpr()){
                    args.push_back(m_node);
                }
                if(!check(COMMA)){
                    err::out("expected ',' found -> ",toks[cur_index]);
                    return false;
                }else{
                    next;
                }
            }

        }

        if(cur_token != RPAREN){
            err::out("expected ')' found -> ",toks[cur_index]);
            return false;
        }else
           next();
        
        m_node = std::make_shared<FunctionCall>(tok, sig, args);
        return true;
    }


    bool Parser::parseTypeValuePair() {
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
            if(parseType()){
                m_node = type;
            }
        }
        m_node = std::make_shared<Parameter>(tok, iden, type);
        return true;
    }

    bool Parser::parseStruct() {
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


        while(cur_token !=  FEOF && cur_token != RBRACE){
                
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
        m_node = std::make_shared<StructState>(tok, sig, element,true);
        return true;
    }



     bool Parser::parseReturn() {
        tokt tok = toks[cur_index];
        AstPtr val;
        next();

        if(!check(SCOL)){
            next();
            if(parsePrimaryExpr()) {
                val = m_node;
            }
        }
        if(!check(SCOL)){
                err::out("expected ';' found -> ",toks[cur_index]);
                return false;
        }
        next();
        m_node = std::make_shared<ReturnState>(tok, val);
        return true;
    }



    bool Parser::parseIfStatm() {
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
            parseStatement();
            condition = m_node;
        }

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
                    if(parseIfStatm()){
                        else_ = m_node;
                    }
                    break;
                case LBRACE:
                    if(parseBlockStatement()){
                        else_ = m_node;
                    }
                    break;
                default:
                    err::out("expected else expression ",toks[cur_index]);
                    return false;

            }
        }
        m_node = std::make_shared<IfStatement>(tok,condition, if_, else_);
        return true;
    }


    bool Parser::parseFor() {
        tokt tok = toks[cur_index];
        AstPtr left,right;
        AstPtr body;
        if(!check(FOR)) {
            err::out("expected keyword 'for' found -> ",toks[cur_index]);
            return false;
        }
        next();
        if(parseIdentifier()) {
            left = m_node;
        }
        if(!check(IN)){
            err::out("expected keyword 'in' found -> ",toks[cur_index]);
            return false;
        }
        next();
        
        if(check(LBRACE)){
            err::out("expected expression found -> ",toks[cur_index]);
             return false;
        }
          
        if(!parsePrimaryExpr()) {
            err::out("unexpected expression -> ",toks[cur_index]);
            return false;
        }
        right = m_node;
        

        if(!parseBlockStatement()){
            return false;
        }
        body = m_node;            

        m_node = std::make_shared<ForInLoop>(tok, left, right, body);
        return true;
    }


    bool Parser::parseFuncdef() {
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
                if(parseTypeValuePair()) {
                    p.push_back(m_node);
                }
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
            err::out("expected function expression \'",toks[cur_index]);
            return false;
        }

        if(check(ARROW)){
            next();
            if(!parseType()){
                err::out("expected function expression \'",toks[cur_index]);
                return false;
            }
            ret = m_node;
        }

        if(check(LBRACE)) {
            parseBlockStatement();
            body = m_node;
        }else if(check(SCOL)){
            next();
        } else {
            err::out("expected function expression \'",toks[cur_index]);
            return false;
        }
        m_node = std::make_shared<FunctionDef>(tok,p,ret,body);
        return true;
    }
    

    bool Parser::parseLetStatm() {
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
                err::out("expected 'type' found -> \'",toks[cur_index]);
                return false;
            }else
                type = m_node;
        }

        if(check(ASSN)) {
            next();
            if(parsePrimaryExpr()){
                val = m_node;
            }
        }
        
        if(check(SCOL)) {
            next();
        } else { 
            err::out("expected expression\'",toks[cur_index]);
            return false;
        }

        m_node = std::make_shared<LetState>(tok, v, type, val);
        return true;
        
    }
    

    bool Parser::parseConst() {
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
            if(parsePrimaryExpr()){
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

        m_node = std::make_shared<ConstState>(tok,name,type,val);
        return true;

    }
    
}



