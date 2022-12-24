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

   parser::Parser p(toks,in);
   ast::AstPtr tree = p.parse();


   std::cout<<" -> "<<tree->node_str()<<std::endl;


}

int main(int argc, char *argv[]){
    // if(argc < 0){
    //     printf("too few args");
    //     return EXIT_FAILURE;
    // }else{
        compile();

   // }
}