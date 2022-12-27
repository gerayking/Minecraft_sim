#include <iostream>
#include "CGRA.h"
int main() {
    CGRA cgrainstance(4,4);
    cgrainstance.parseInsFile(); // 解析指令文件
    cgrainstance.parseMemFile(); // 解析数据文件
    cgrainstance.run(); // 运行
}
