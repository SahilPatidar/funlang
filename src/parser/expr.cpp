#include"../../include/parser/parser.hpp"
#include"../../include/Error.hpp"

namespace parser{

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
        }else {
            err::out("unexpected expression with '..' -> ",toks[cur_index]);
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
            err::out("expected 'identifier' found -> ",toks[cur_index]);
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
    }else if(check(LBRACE)){
        if(!parseStructExpr()){
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
        if(!parseExpr()){
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



    // bool Parser::parseBineryExpr(int prev_prece) {
    //     dump(__func__);
    //     tokt tok = toks[cur_index];
    //     Token_type opr;
    //     AstPtr right,left;
    //     left = m_node;
    //     if(m_node == nullptr){
    //         if(!parseExpr()){
    //             return false;
    //         }
    //         left = m_node;
    //     }else
    //         left = m_node;

    //     //2+3*3/4+2*3
    //     while(BineryOP(cur_token)) {
    //         opr = cur_token;
    //         m_preced = preced(opr);
    //         if(prev_prece > m_preced) {
    //             std::cout<<"return ------======"<<m_preced<<" "<<prev_prece<<std::endl;
    //             m_node = left;
    //             return true;
    //         }
    //         next();
    //         m_node = nullptr;
    //         if(parseBineryExpr(m_preced + 1)){
    //             right = m_node;
    //         }
    //         left = std::make_shared<BineryExper>(tok, left, opr, right);
    //         m_preced = 0;
    //     }
    //     m_node = left;
    //             dump2(__func__);

    //     return true;
    // }

//     bool Parser::parseRangeExpr() {
//         dump(__func__);
//         AstPtr right,left; 
//         tokt tok = toks[cur_index];

//         left = m_node;

//         while(check(DOTDOT)){
//             next();
//             if(!parseExpr()){
//                 err::out("expected 'identifier' found -> ",toks[cur_index]);
//                 return false;
//             }
//             right = m_node;
//             m_node = std::make_shared<Variadic>(tok, left, right);
//         }
//         dump2(__func__);

//         return true;
//     }

//     bool Parser::parseAssignment() {
//         dump(__func__);
//         AstPtr right,left; 
//         tokt tok = toks[cur_index];
//         left = m_node;
//         while(AssignOP(cur_token)){
//             next();
//             if(!parseExpr()){
//                 err::out("expected 'identifier' found -> ",toks[cur_index]);
//                 return false;
//             }
//             right = m_node;
//             m_node = std::make_shared<AssignmentExpr>(tok, left, right);
//         }
//         dump2(__func__);
//         return true;
//     }

//     bool Parser::parsePathExpr() {
//         dump(__func__);
//         AstPtr right,left; 
//         tokt tok = toks[cur_index];
//         left = m_node;

//         while(check(COLCOL)){
//             next();
//             if(!parseExpr()){
//                 err::out("expected 'identifier' found -> ",toks[cur_index]);
//                 return false;
//             }
//             right = m_node;
//             m_node = std::make_shared<Path>(tok, left, right);
//         }
//         dump2(__func__);

//         return true;
//     }


//     bool Parser::parseDotOrArrow() {
//         dump(__func__);
//         AstPtr right,left; 
//         tokt tok = toks[cur_index];
//         Token_type op = cur_token;
//         left = m_node;
//         while(check(DOT)||check(ARROW)){
//             next();
//             if(check(IDEN)&&!parsePreIdenExpr()){
//                 err::out("expected 'identifier' found -> ",toks[cur_index]);
//                 return false;
//             }
//             right = m_node;
//             m_node = std::make_shared<MemberExpr>(tok, left, op, right);
//         }
//         dump2(__func__);

//         return true;
//     }


//     bool Parser::parseIdenExp() {
//         dump(__func__);
//         if(check(IDEN)) {
//             parseIdentifier();        
//         }
//         while(check(DOT)||check(ARROW)||
//                         check(LPAREN)||check(LBRACK)) {
//            if(check(DOT)||check(ARROW)){
//                 if(!parseDotOrArrow()){
//                     return false;
//                 }
//             }else if((check(LPAREN)&&!parseFuncCall())||
//                         (check(LBRACK)&&!parseArrayAccess())) {
//                 return false;
//             }
//         }
//                 dump2(__func__);

//         return true;
//     }

//     bool Parser::parseCastExpr(){
//         dump(__func__);
//         tokt tok = toks[cur_token];
//         AstPtr left = m_node;
//         while(check(AS)){
//             next();
//             if(PreDefType(cur_token)&&!parseType()){
//                 err::out("expected 'type' found -> ",toks[cur_index]);
//                 return false;
//             }
//         }
//         AstPtr right = m_node;
//         m_node = std::make_shared<AsState>(tok,left,right);
//                 dump2(__func__);

//         return true;
//     }

//     bool Parser::parsePreIdenExpr() {
//         dump(__func__);
//         if(check(IDEN)) {
//             if(!parseIdenExp()){
//                 return false;
//             }
//         }else if(isLiteral(cur_token)) {
//             if(!parseLiteral()){
//                 return false;
//             }
//         }
//                 dump2(__func__);

//         return true;
//     }



//     bool Parser::parseSecondryExpr() {
//         dump(__func__);
//         if(UnaryOP(cur_token)){
//             if(!parsePrefixExpr()){
//                 return false;
//             }
//         }else if(check(IDEN)){
//             if(checkh(LBRACE)){
//                 next();
//                 if(!parseStructExpr()){
//                     return false;
//                 }
//             }else if(!parsePreIdenExpr()) {
//                 return false;
//             }
//         }else if(isLiteral(cur_token)){
//             if(!parseLiteral()){
//                 return false;
//             }
//         }else if(check(LPAREN)){
//             if(!parseParenExpr()){
//                 return false;
//             }
//         }else if(check(LBRACK)){
//             if(!parseArrayExpr()){
//                 return false;
//             }
//         }else {
//             err::out("expected expression is invalid -> ",toks[cur_index]);
//             return false;
//         }
//                 dump2(__func__);

//         return true;
//     }

//     bool Parser::parseExpr() {
// dump(__func__);
//         if(!parseSecondryExpr()){
//                 return false;
//         }

//         if(check(DOTDOT)){
//             if(!parseRangeExpr()){
//                 return false;
//             }
//         }else if(check(COLCOL)){
//             if(!parsePathExpr()){
//                 return false;
//             }
//         }else if(check(AS)){
//             if(!parseCastExpr()){
//                 return false;
//             }
//         }
//                 dump2(__func__);

//         return true;
//     }


//     bool Parser::parseExpr() {
//         dump(__func__);
//         if(!parseExpr()){
//             return false;
//         }

//         if(AssignOP(cur_token)){
//             if(!parseAssignment()){
//                 return false;
//             }
//         }else if(BineryOP(cur_token)){
//             if(!parseBineryExpr(m_preced)){
//                 return false;
//             }
//         }

//         dump2(__func__);

//         return true;
//     }



//     bool Parser::parsePrefixExpr() {
//         dump(__func__);
//         bool isType = false;
//         Token_type op = cur_token;
//         tokt tok = toks[cur_index];
//         AstPtr base;
//         if(check(STAR)){
//             next();
//             if(check(STAR)){
//                 parsePrefixExpr();
//                 base = m_node;
//             }else if(!parseSecondryExpr()){
//                 return false;
//             }
//             base = m_node;
//             m_node = std::make_shared<PointerExpr>(tok,base, isType);
//             return true;
//         }else if(check(AND_OP)){
//             next();
//             if(!parseSecondryExpr()){
//                 err::out("expected expression is invalid -> ",toks[cur_index]);
//                 return false;
//             }
//             base = m_node;
//             m_node = std::make_shared<RefExpr>(tok,op, base,isType);
//             return true;
//         }else if(!parseSecondryExpr()) {            
//             base = m_node;
//         }else{
//             return false;
//         }

//         m_node = std::make_shared<PrefixExper>(tok,base,op);
//                 dump2(__func__);

//         return true;
//     }
    
    
//     bool Parser::parseParenExpr() {
//         next();
//         dump(__func__);
//         int old = m_preced;
//         m_preced = 0;
//         AstPtr node;
//         if(check(RPAREN)){
//             err::out("expected expression found -> ",toks[cur_index]);
//             return false;
//         }else if(!parseExpr()){
//             return false;
//         }
//         node = m_node;
//         if(check(COMMA)) {
//             bool isType = false;;
//             tokt tok = toks[cur_index];
//             std::vector<AstPtr>vals;
//             vals.push_back(node);
//             if(!check(RPAREN)) {
//                 next();
//                 while(!check(RPAREN)){ 
//                     m_preced = 0;
//                     if(!parseExpr()){
//                         err::out("expected expression found -> ",toks[cur_index]);
//                         return false;
//                     }
//                     vals.push_back(m_node);
//                     if(check(RPAREN)){
//                         break;
//                     }
//                     if(!check(COMMA)){
//                         err::out("expected ',' found -> ",toks[cur_index]);
//                         return false;
//                     }
//                     next();   
//                 }

//             } 
//             if(cur_token != RPAREN){
//                 err::out("expected ')' found -> ",toks[cur_index]);
//                 return false;
//             }
//             next(); 
//             node = std::make_shared<Tuple>(tok,vals,isType);
//             m_preced = old;
//             m_node = node;
//                             dump2(__func__);

//             return true;
//         }

//         if(cur_token != RPAREN){
//             err::out("expected ')' found -> ",toks[cur_index]);
//             return false;
//         } 
//         next();
//         m_preced = old;
//         m_node = node;
//         m_node = std::make_shared<GroupedExpr>(m_node);
//                 dump2(__func__);

//         return true;
//     }


}