#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenize(const std::string& str){
    std::vector<Token> tokens;
    std::string buf = "";
    for (int i = 0 ; i < str.length() ; i++){
        char c = str.at(i);
        if(std::isalpha(c)){
            buf.push_back(c);
            i++;
            while (std::isalnum(str.at(i))){
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if (buf == "return"){
                tokens.push_back({.type = TokenType::_return});
            }
            else{
                std::cerr << "You messed up!" << std::endl;
                exit(EXIT_FAILURE);
            }
            }
        else if(std::isdigit(c)){
            buf.push_back(c);
            i++;
            while(std::isdigit(str.at(c))){
                buf.push_back(str.at(c));
                i++ ;
            }
            i--;
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();
        }
        else if (c == ";"){
            tokens.push_back({.type= TokenType::semi});
        }
        else if(std::isspace(c)){
            continue;
        }
        else {
            std::cerr << "You messed up !" << std::endl;
            exit(EXIT_FAILURE)
        }
        }
    
    }

int main(int argc , char* argv[]){
    if (argc != 2 ){
        std::cerr << "Incorrect usage" << std::endl;
        std::cerr << "hydro <input.hy>" << std::endl;
        return EXIT_FAILURE ; 
    }

    std::cout << argv[1] <<std::endl;
    std::string contents ;     
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }
    std::cout << "Displaying Content of the file : " << std::endl; 
    std::cout << contents << std::endl;
    //std::cout << argv[0] << std::endl;
    return 0 ;
}