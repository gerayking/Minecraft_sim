//
// Created by geray on 2022/12/27.
//

#ifndef CGRA_CGRA_H
#include "Pe.h"
#include <map>
#define CGRA_CGRA_H


class CGRA {
public:
    void parseInsFile();
    void parseMemFile();
    CGRA(int sizex,int sizey);
    std::map<addrType,dataType>dram;
    void run();
private:
    Pe **tiles;
    int sizeX,sizeY;
};


#endif //CGRA_CGRA_H
