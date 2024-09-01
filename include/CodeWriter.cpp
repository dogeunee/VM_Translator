#include "CodeWriter.h"
CodeWriter::CodeWriter(string file, std::ios_base::openmode mode){
    ofile.open(file, mode);
}
CodeWriter::~CodeWriter(){
    ofile.close();
}
void CodeWriter::writeArithmetic(string arg1){
    if(arg1!="eq"&&arg1!="gt"&&arg1!="lt"){
        string line;
        ifile.open("include/data/arithmetic/"+arg1+".txt");
        while(!ifile.eof()){
        getline(ifile,line);
        ofile<<line<<"\n";
        }
        ifile.close();
    }else if(arg1 == "eq"){
        ofile<<"//eq\n"
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@SP\n"
        "A=M-1\n"
        "D=M-D\n"
        "@NOT"<<setnum<<"\n" // not equal
        "D;JNE\n"
        "@EQUAL"<<setnum<<"\n" //equal
        "0;JMP\n"
        "(NOT"<<setnum<<")\n" // not equal
        "@SP\n"
        "A=M-1\n"
        "M=0\n"
        "@END"<<setnum<<"\n" // end
        "0;JMP\n"
        "(EQUAL"<<setnum<<")\n" // equal
        "@SP\n"
        "A=M-1\n"
        "M=-1\n"
        "(END"<<setnum<<")\n"; // end
        setnum++;
    }else if(arg1 == "gt"){
        ofile<<"//sub\n"
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@SP\n"
        "A=M-1\n"
        "D=M-D\n"
        "@NOT"<<setnum<<"\n" // not equal
        "D;JLE\n"
        "@EQUAL"<<setnum<<"\n"
        "0;JMP\n"
        "(NOT"<<setnum<<")\n" // not equal
        "@SP\n"
        "A=M-1\n"
        "M=0\n"
        "@END"<<setnum<<"\n" // end
        "0;JMP\n"
        "(EQUAL"<<setnum<<")\n" // equal
        "@SP\n"
        "A=M-1\n"
        "M=-1\n"
        "(END"<<setnum<<")\n"; // end
        setnum++;
    }else if(arg1 == "lt"){
        ofile<<"//lt\n"
        "@SP\n"
        "AM=M-1\n"
        "D=M\n"
        "@SP\n"
        "A=M-1\n"
        "D=M-D\n"
        "@NOT"<<setnum<<"\n" // not equal
        "D;JGE\n"
        "@EQUAL"<<setnum<<"\n" // equal
        "0;JMP\n"
        "(NOT"<<setnum<<")\n" // not equal
        "@SP\n"
        "A=M-1\n"
        "M=0\n"
        "@END"<<setnum<<"\n" // end
        "0;JMP\n"
        "(EQUAL"<<setnum<<")\n" // equal
        "@SP\n"
        "A=M-1\n"
        "M=-1\n"
        "(END"<<setnum<<")\n"; // end
        setnum++;
    }
}
void CodeWriter::setFileName(string filename){
    currentFileName=filename;
}
void CodeWriter::writeInit(){
    ofile<<"//init\n"
            "@256\n"
            "D=A\n"
            "@SP\n"
            "M=D\n";
    writeFunction(C_CALL,"Sys.init",0);
}
void CodeWriter::writePushPop(commandType ctype, string arg1, int arg2){
    if(ctype==C_PUSH){
        if(arg1=="constant"){
            ofile<<"//push constant "<<arg2<<"\n"
            "@"<<arg2<<"\n"
            "D=A\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"
            "@SP\n"
            "M=M+1\n";
        }else if(arg1=="local"){
            ofile<<"//push local "<<arg2<<"\n"
            "@LCL\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "A=D+A\n"
            "D=M\n"
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n"
            "M=D\n";
        }else if(arg1=="argument"){
            ofile<<"//push argument "<<arg2<<"\n"
            "@ARG\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "A=D+A\n"
            "D=M\n"
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n"
            "M=D\n";
        }else if(arg1=="this"){
            ofile<<"//push this "<<arg2<<"\n"
            "@THIS\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "A=D+A\n"
            "D=M\n"
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n"
            "M=D\n";
        }else if(arg1=="that"){
            ofile<<"//push argument "<<arg2<<"\n"
            "@THAT\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "A=D+A\n"
            "D=M\n"
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n"
            "M=D\n";
        }else if(arg1=="static"){
            ofile<<"//push static "<<arg2<<"\n"
            "@"<<currentFileName<<"."<<arg2<<"\n"
            "D=M\n"
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n"
            "M=D\n";
            cout<<"@"<<currentFileName<<"."<<arg2<<"\n";
        }else if(arg1=="temp"){
            ofile<<"//push temp "<<arg2<<"\n"
            "@5\n"
            "D=A\n"
            "@"<<arg2<<"\n"
            "A=D+A\n"
            "D=M\n"
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n"
            "M=D\n";
        }else if(arg1=="pointer"){
            ofile<<"//push pointer "<<arg2<<"\n"
            <<(arg2?"@THAT":"@THIS")<<"\n"
            "D=M\n"
            "@SP\n"
            "M=M+1\n"
            "A=M-1\n"
            "M=D\n";
        }
    }else if(ctype==C_POP){
        if(arg1=="local"){
            ofile<<"//pop local "<<arg2<<"\n"
            "@LCL\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "D=D+A\n"
            "@SP\n"
            "AM=M-1\n"
            "D=D+M\n"
            "A=D-M\n"
            "M=D-A\n";

        }else if(arg1=="argument"){
            ofile<<"//pop argument "<<arg2<<"\n"
            "@ARG\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "D=D+A\n"
            "@SP\n"
            "AM=M-1\n"
            "D=D+M\n"
            "A=D-M\n"
            "M=D-A\n";
        }else if(arg1=="this"){
            ofile<<"//pop this "<<arg2<<"\n"
            "@THIS\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "D=D+A\n"
            "@SP\n"
            "AM=M-1\n"
            "D=D+M\n"
            "A=D-M\n"
            "M=D-A\n";
        }else if(arg1=="that"){
            ofile<<"//pop argument "<<arg2<<"\n"
            "@THAT\n"
            "D=M\n"
            "@"<<arg2<<"\n"
            "D=D+A\n"
            "@SP\n"
            "AM=M-1\n"
            "D=D+M\n"
            "A=D-M\n"
            "M=D-A\n";
        }else if(arg1=="static"){
            ofile<<"//pop static "<<arg2<<"\n"
            "@"<<currentFileName<<"."<<arg2<<"\n"
            "D=A\n"
            "@SP\n"
            "AM=M-1\n"
            "D=D+M\n"
            "A=D-M\n"
            "M=D-A\n";
            cout<<"@"<<currentFileName<<"."<<arg2<<"\n";
        }else if(arg1=="temp"){
            ofile<<"//pop temp "<<arg2<<"\n"
            "@5\n"
            "D=A\n"
            "@"<<arg2<<"\n"
            "D=D+A\n"
            "@SP\n"
            "AM=M-1\n"
            "D=D+M\n"
            "A=D-M\n"
            "M=D-A\n";   
        }else if(arg1=="pointer"){
            ofile<<"//pop pointer "<<arg2<<"\n"
            "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            <<(arg2?"@THAT":"@THIS")<<"\n"
            "M=D\n"; 
        }
    }
}
void CodeWriter::writeBranching(commandType ctype,string arg1){
    if(ctype==C_LABEL){
        ofile<<"//label\n"
        "("<<currentFuncName<<"$"<<arg1<<")\n";
    }else if(ctype==C_GOTO){
        ofile<<"//goto\n"
        "@"<<currentFuncName<<"$"<<arg1<<"\n"
        "0;JMP\n";
    }else if(ctype==C_IF){
        ofile<<"//if\n"
        "@SP\n" 
        "AM=M-1\n" 
        "D=M\n"
        "@"<<currentFuncName<<"$"<<arg1<<"\n"
        "D;JNE\n";
    }
}
void CodeWriter::writeFunction(commandType ctype, string arg1, int arg2){
     if(ctype==C_CALL){
        ofile<<"//call"<<currentFuncName<<"\n"
        "@"<<currentFuncName<<"$ret."<<addrnum<<"\n"//push retAddrLabel
        "D=A\n"
        "@SP\n"
        "M=M+1\n"
        "A=M-1\n"
        "M=D\n"
        "@LCL\n"//push LCL
        "D=M\n"
        "@SP\n"
        "M=M+1\n"
        "A=M-1\n"
        "M=D\n"
        "@ARG\n"//push ARG
        "D=M\n"
        "@SP\n"
        "M=M+1\n"
        "A=M-1\n"
        "M=D\n"
        //push THIS
        "@THIS\n"
        "D=M\n"
        "@SP\n"
        "M=M+1\n"
        "A=M-1\n"
        "M=D\n"
        //push THAT
        "@THAT\n"
        "D=M\n"
        "@SP\n"
        "M=M+1\n"
        "A=M-1\n"
        "M=D\n"
        //ARG = SP - 5 - nArgs // Repositions ARG
        "@SP\n"
        "D=M\n"
        "@5\n"
        "D=D-A\n"
        "@"<<arg2<<"\n"
        "D=D-A\n"
        "@ARG\n"
        "M=D\n"
        //LCL = SP // Repositions LCL
        "@SP\n"
        "D=M\n"
        "@LCL\n"
        "M=D\n"
        //goto functionName // Transfers control to the callee
        "@"<<arg1<<"\n"
        "0;JMP\n"
        //(retAddrLabel) // Injects this label into the code
        "("<<currentFuncName<<"$ret."<<addrnum<<")\n";
        addrnum++;
    }else if(ctype==C_FUNCTION){
        currentFuncName=arg1;
        ofile<<"//function "<<arg1<<" "<<arg2<<"\n"
        "("<<arg1<<")\n";
        for(int i=0;i<arg2;i++) writePushPop(C_PUSH, "constant", 0);
    }else if(ctype==C_RETURN){
        //temp[0](endframe)=LCL
        ofile<<"//return of "<<currentFuncName<<"\n"
        "@LCL\n"
        "D=M\n"
        "@R13\n"
        "M=D\n"
        //retAddr = *(endFrame ? 5) // gets the return address
        "@5\n"
        "D=A\n"
        "@R13\n"
        "A=M-D\n"
        "D=M\n"
        "@R14\n"
        "M=D\n"
        //*ARG = pop() // puts the return value for the caller
        "@SP\n"
        "A=M-1\n"
        "D=M\n"
        "@ARG\n"
        "A=M\n"
        "M=D\n"
        //SP = ARG + 1 // repositions SP
        "@ARG\n"
        "D=M+1\n"
        "@SP\n"
        "M=D\n"
        //THAT = *(endFrame ? 1) // restores THAT
        "@R13\n"
        "AM=M-1\n"
        "D=M\n"
        "@THAT\n"
        "M=D\n"
        //THIS = *(endFrame ? 2) // restores THIS
        "@R13\n"
        "AM=M-1\n"
        "D=M\n"
        "@THIS\n"
        "M=D\n"
        //ARG = *(endFrame ? 3) // restores ARG
        "@R13\n"
        "AM=M-1\n"
        "D=M\n"
        "@ARG\n"
        "M=D\n"
        //LCL = *(endFrame ? 4) // restores LCL
        "@R13\n"
        "AM=M-1\n"
        "D=M\n"
        "@LCL\n"
        "M=D\n"
        //the global stack goto retAddr // jumps to the return address
        "@R14\n"
        "A=M\n"
        "0;JMP\n";
    }
}