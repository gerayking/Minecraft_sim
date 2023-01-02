#include <iostream>
#include "CGRA.h"
#include "string"
using namespace std;
int main() {
    string insfile = "insfile.txt";
    string memfile = "memfile.txt";
    CGRA cgrainstance(4,4);
    cgrainstance.parseInsFile(insfile); // 解析指令文件
    cgrainstance.parseMemFile(memfile); // 解析数据文件
    cout << "init finish.." << endl;
    cgrainstance.run(); // 运行
}
