#include "commandType.h"
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;

class CodeWriter{
    public:
    CodeWriter(string file,std::ios_base::openmode mode);
    ~CodeWriter();
    void writeArithmetic(string arg1);
    void writePushPop(commandType ctype, string arg1, int arg2);
    void writeBranching(commandType ctype,string arg1);
    void writeFunction(commandType ctype, string arg1, int arg2);
    void setFileName(string filename);
    void writeInit();
    
    private:
    string currentFuncName;
    string currentFileName;
    int setnum=0;
    int addrnum=1;
    ofstream ofile;
    ifstream ifile;
};
