#include "commandType.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


class Parser{
    public:
    Parser(string file);
    ~Parser();
    bool hasMoreLines();
    void advance();
    enum commandType commandType();
    string arg1();
    int arg2();
    std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    void removeTab(string& s);
    void trimTrailingSpaces(std::string& str);
    private:
    enum commandType ctype;
    ifstream ifile;
    string currentLine;
    string firstArg;
    string secondArg;


};