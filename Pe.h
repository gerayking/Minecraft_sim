//
// Created by geray on 2022/12/26.
//

#ifndef CGRA_PE_H
#include "Ins.h"
#include <map>
#include <iostream>
#include <bitset>
#define CGRA_PE_H



// pe type
#define NPE 0
#define MPE 1
class Pe {
public:
    int id;
    dataType rf1,rf2,rf3,rf4,rf5; // 5 register
    dataType operand1,operand2,ALUTemp,outTemp,memData;
    insType ins,pc;// pc : address of instruction
    insType insBuffer[insLimit]; // instruction buffer;
    int x,y;
    void getOperand(dataType &operand,int sel);
    void recvData();
    void writeback();
    std::map<addrType,dataType>* DRAM; // dram
    int peType; // pe type
    Pe();
    Pe(int peType,std::map<addrType,dataType>* DRAM);
    void execute();
    void setCMEM(long ins, int cycle);
    Pe* inE,*inS,*inW,*inN; // Pe link
    void printExeInfo();

};


#endif //CGRA_PE_H
