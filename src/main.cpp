#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>
#include<sstream>
#include<filesystem>
#include"../include/lex/lex.hpp"

void compile(){
   std::ifstream file("../call.fn");
   std::stringstream buf;
   buf << file.rdbuf();
   std::cout<<buf.str();
   std::string src = buf.str();
   lex::tok_t toks;

}

int main(int argc, char *argv[]){
    if(argc < 0){
        printf("too few args");
        return EXIT_FAILURE;
    }else{
        compile();
    }
}