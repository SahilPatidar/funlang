#include"../../include/analyzer/Analyzer.hpp"

namespace analyzer {
    
    bool Analyzer::visit(const ast::Program& astnode) {
        for(int i = 0 ; i < astnode.statements().size(); i++){
            switch(astnode.statements()[i]->nodeCategory()){
                case NODE_IF_STM:
                case NODE_FOR_STM:
                case NODE_WHILE_STM:
                case NODE_RET_STM:
                case NODE_ASSN_EXPR:
                case NODE_LET_STM:
                case NODE_STRUCT_STM:
                case NODE_BRANCH_STM:
                case NODE_EXTERN:
                case NODE_FUNC_DEF:
                {
                    astnode.statements()[i]->accept(*this);
                }
                default:
                    //todo
            }
        }
        return true;
    }

    bool Analyzer::visit(const ast::FunctionDef& astnode){
        astnode.func_name()->accept(*this);
        if(!astnode.parameter().empty()) {
            for(int i = 0; i < astnode.parameter().size(); i++){
                auto pty = std::dynamic_pointer_cast<ast::Parameter>(astnode.parameter()[i]);
                if(pty->p_type()){

                }
            }
        }
        
        return true;
    }
    
    
    

}
