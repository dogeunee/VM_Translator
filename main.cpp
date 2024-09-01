#include "include/CodeWriter.h"
#include "include/Parser.h"
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
void mainFileWriter(fs::path addr){
    Parser parser(addr.string());
    CodeWriter codeWriter(addr.replace_extension(".asm").string(),std::ios::trunc);
    while(true){
        parser.advance();
        if(parser.hasMoreLines()){
        commandType ctype = parser.commandType();
        if(ctype== commandType::C_ARITHMETIC){
            codeWriter.writeArithmetic(parser.arg1());
        }else if(ctype==commandType::C_POP||ctype==commandType::C_PUSH){
            codeWriter.writePushPop(ctype,parser.arg1(),parser.arg2());
        }else if(ctype==commandType::C_LABEL||ctype==commandType::C_GOTO||ctype==commandType::C_IF){
            codeWriter.writeBranching(ctype,parser.arg1());
        }else if(ctype==commandType::C_CALL||ctype==commandType::C_FUNCTION||ctype==commandType::C_RETURN){
            codeWriter.writeFunction(ctype,parser.arg1(),parser.arg2());
        }
        }else break;
}
}
void bootstrapWriter(fs::path dir){
    string strdir=dir.string()+"/"+(dir.filename().replace_extension(".asm")).string();
    fs::path dirname = strdir;
    CodeWriter codeWriter(dirname.string(),std::ios::trunc);
    codeWriter.writeInit();
}
void mainDirFileWriter(fs::path addr,fs::path dir){
    Parser parser(addr.string());
    string strdir=dir.string()+"/"+(dir.filename().replace_extension(".asm")).string();
    fs::path dirname = strdir;
    CodeWriter codeWriter(dirname.string(),std::ios::app);

    codeWriter.setFileName(addr.filename().replace_extension("").string());

    while(true){
        parser.advance();
        if(parser.hasMoreLines()){
        commandType ctype = parser.commandType();
        if(ctype== commandType::C_ARITHMETIC){
            codeWriter.writeArithmetic(parser.arg1());
        }else if(ctype==commandType::C_POP||ctype==commandType::C_PUSH){
            codeWriter.writePushPop(ctype,parser.arg1(),parser.arg2());
        }else if(ctype==commandType::C_LABEL||ctype==commandType::C_GOTO||ctype==commandType::C_IF){
            codeWriter.writeBranching(ctype,parser.arg1());
        }else if(ctype==commandType::C_CALL||ctype==commandType::C_FUNCTION||ctype==commandType::C_RETURN){
            codeWriter.writeFunction(ctype,parser.arg1(),parser.arg2());
        }
        }else break;
    }
}

int main(){
    string filename;
    cin>>filename;

    fs::path p(filename);
    vector<fs::path> vmFileList;

    if(fs::is_regular_file(p)){
        mainFileWriter(p);
    }
    else if(fs::is_directory(p)){
        for (const auto& entry : fs::directory_iterator(p)) {
            if (fs::is_regular_file(entry)) {
                fs::path filePath = entry.path();
                if(filePath.extension() == ".vm"){
                    vmFileList.push_back(filePath);
                }
            }
        }
        bootstrapWriter(p);
        for(fs::path file : vmFileList){
            mainDirFileWriter(file ,p);
            }
    }
    return 0;
}