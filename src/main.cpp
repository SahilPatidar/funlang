#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<sstream>
#include<filesystem>
#include"../include/parser/parser.hpp"
#include"../include/parser/Ast.hpp"
#include"../include/lex/lex.hpp"
#include"../include/Error.hpp"

void compile(){
   std::ifstream file("call.fn");
   std::stringstream buf;
   buf << file.rdbuf();
   std::cout<<buf.str();
   std::string src = buf.str();
   lex::tok_t toks;
   int ipos=0;
   int str_len = src.size();
   bool c = lex::tokenizer(src, toks, ipos, str_len);
   if(!c){
    printf("invalid src string..\n");
   }
    // std::cout<<str_len<<std::endl;
    // for(int i = 0; i < str_len; i++){
    //     std::cout<<toks[i].data<<"    "<<toks[i].pos<<"    "<<toks[i].tok_type<<std::endl;
    // }
    

}

int main(int argc, char *argv[]){
    // if(argc < 0){
    //     printf("too few args");
    //     return EXIT_FAILURE;
    // }else{
        compile();

   // }
}