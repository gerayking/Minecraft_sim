//
// Created by geray on 2022/12/27.
//

#ifndef CGRA_CGRA_H
#include "Pe.h"
#include <map>
#define CGRA_CGRA_H


class CGRA {
public:
    void parseInsFile(std::string filename);
    void parseMemFile(std::string filename);
    CGRA(int sizex,int sizey);
    std::map<addrType,dataType>dram;
    void run();
    void printCMEM();
    void printDRAM();
private:
    Pe **tiles;
    int sizeX,sizeY;
};


#endif //CGRA_CGRA_H
