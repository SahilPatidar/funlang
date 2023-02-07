#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<sstream>
#include<map>
#include<filesystem>
#include"../include/parser/parser.hpp"
#include"../include/parser/Ast.hpp"
#include"../include/lex/lex.hpp"



void compile(){
   std::ifstream file("call.fn");
   std::stringstream buf;
   buf << file.rdbuf();
   //std::cout<<buf.str();
   std::string src = buf.str();
   lex::tok_t toks;
   int ipos=0;
   int str_len = src.size();
   bool c = lex::tokenizer(src, toks, ipos, str_len);
   if(!c){
    printf("invalid src string..\n");
   }
   int in = 0;
   for(int i = 0 ; i < toks.size(); i++){
      std::cout<<toks[i].data<<" -> "<<toks[i].tok_type<<std::endl;
   }

   parser::Parser p(toks,in,in);
   ast::AstPtr tree = p.parse();

   auto t = std::dynamic_pointer_cast<ast::Program>(tree);
   // std::cout<<std::dynamic_pointer_cast<ast::WhileLoop>(t->statements()[0])->loopbody()->toString()<<std::endl;
   std::cout<<""<<t->statements().size()<<std::endl;
   std::cout<<" ->\n "<<tree->toString()<<std::endl;


}

int main(int argc, char *argv[]){
    // if(argc < 0){
    //     printf("too few args");
    //     return EXIT_FAILURE;
    // }else{
        compile();

   // }
}