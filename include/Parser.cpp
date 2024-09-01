#include "Parser.h"
Parser::Parser(string file){
    ifile.open(file);
}
Parser::~Parser(){
    ifile.close();
}
bool Parser::hasMoreLines(){
    return bool(ifile);
}
void Parser::advance(){
    getline(ifile, currentLine);
    
    while(currentLine.size()==0||currentLine[0]=='/'){
            if(hasMoreLines()){
                getline(ifile, currentLine);
            }else break;
        }
    removeTab(currentLine);
    trimTrailingSpaces(currentLine);
    //set ctype and arguments
    std::vector<std::string> result = split(currentLine, " ");
    string commandStr = result[0];
    if(commandStr=="add"||commandStr=="sub"||commandStr=="neg"
        ||commandStr=="eq"||commandStr=="gt"||commandStr=="lt"||
        commandStr=="and"||commandStr=="or"||commandStr=="not"){
            ctype=C_ARITHMETIC;
            firstArg=commandStr;
    }else if(commandStr == "push"){
        ctype=C_PUSH;
        firstArg=result[1];
        secondArg=result[2];
    }else if(commandStr== "pop"){
        ctype=C_POP;
        firstArg=result[1];
        secondArg=result[2];
    }else if(commandStr == "label"){
        ctype=C_LABEL;
        firstArg=result[1];
    }else if(commandStr == "if-goto"){
        ctype=C_IF;
        firstArg=result[1];
    }else if(commandStr == "goto"){
        ctype=C_GOTO;
        firstArg=result[1];
    } else if(commandStr == "call"){
        ctype=C_CALL;
        firstArg=result[1];
        secondArg=result[2];
    }else if(commandStr == "function"){
        ctype=C_FUNCTION;
        firstArg=result[1];
        secondArg=result[2];
    }else if(commandStr == "return") {
        ctype=C_RETURN;
    }
    else ctype=C_NULL;
}

commandType Parser::commandType(){
    return ctype;
}
string Parser::arg1(){
    return firstArg;
}
int Parser::arg2(){
    return stoi(secondArg);
}

std::vector<std::string> Parser::split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    std::string s = str;
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s); // Add the last token

    return tokens;
}

void Parser::removeTab(string& str) {
    size_t pos = str.find_first_of('\t');

    // Check if a tab character was found
    if (pos != std::string::npos) {
        // Remove the first tab character
        str.erase(pos, 1);
    }
}
void Parser::trimTrailingSpaces(std::string& str) {
    auto end = std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base();  // Convert reverse iterator to normal iterator

    str.erase(end, str.end());
}