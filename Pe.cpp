//
// Created by geray on 2022/12/26.
//

#include "Pe.h"

Pe::Pe() {
    pc = 0;
    for(int i=0;i<insLimit;i++){
        insBuffer[i]=0;
    }
    rf1=rf2=rf3=rf4=rf5=0;
}
Pe::Pe(int peType, std::map<addrType,dataType>*DRAM) {
    this->DRAM = DRAM;
    this->peType = peType;
}
void Pe::getOperand(int &operand,int sel) {
    switch (sel) {
        case 0:
            operand = this->inE->rf3;
            break;
        case 1:
            operand = this->inS->rf4;
            break;
        case 2:
            operand = this->inW->rf1;
            break;
        case 3:
            operand = this->inN->rf2;
            break;
        case 4:
            operand = IMM(ins);
            break;
        case 5:
            operand = rf5;
            break;
        case 6:
            operand = SELA(ins);
            break;
        default:
            std::cout << " ***** sel: " << sel << std::endl;
            throw "SELA error!";
    }
}
void Pe::recvData() {
    getOperand(this->operand1,SELA(ins));
    getOperand(this->operand2,SELB(ins));
}
void Pe::execute() {
    ins = insBuffer[pc++];
    std::cout <<"x : "<<x<<" y : "<<y<< " ins: " << std::bitset<32>(this->ins) << "\n";
    // mux
    if(OPCODE(ins)!=NOP)recvData();
    // alu
 //   std::cout << OPCODE(ins) << std::endl;
    switch (OPCODE(ins)) {
        case ADD:
            ALUTemp = operand1 + operand2;
            break;
        case SUB:
            ALUTemp = operand1 - operand2;
            break;
        case MUL:
            ALUTemp = operand1 * operand2;
            break;
        case DIV:
            ALUTemp = operand1 / operand2; // 整除
            break;
        case AND:
            ALUTemp = operand1 & operand2;
            break;
        case OR:
            ALUTemp = operand1 | operand2;
            break;
        case XOR:
            ALUTemp = operand1 ^ operand2;
            break;
        case CMP:
            ALUTemp = (operand1 == operand2);
            break;
        case CLT:
            ALUTemp = (operand1 < operand2);
            break;
        case CGT:
            ALUTemp = (operand1 > operand2);
            break;
        case LOAD:
            break;
        case STORE:
            break;
        case NOP:
            break;
        default:
    //        throw "opcode error";
            std::cout << "******* opcode: default : " <<OPCODE(ins) <<  std::endl;
    }
    // lsu
    if(peType == MPE){
        if(OPCODE(ins) == LOAD){
            memData = (*DRAM)[operand1];
        }else if(OPCODE(ins) == STORE){
            (*DRAM)[operand1] = operand2;
        }
    }
    // muxm
    if(peType == MPE){
        if(OPCODE(ins) == LOAD){
            outTemp = memData;
        }else{
            outTemp = ALUTemp;
        }
    }else{
        outTemp = ALUTemp;
    }
}
void Pe::writeback() {
    switch (SELOUT(ins)) {
        case 0b00001:
            rf1 = outTemp;
            break;
        case 0b00010:
            rf2 = outTemp;
            break;
        case 0b00100:
            rf3 = outTemp;
            break;
        case 0b01000:
            rf4 = outTemp;
            break;
        case 0b10000:
            rf5 = outTemp;
            break;
    }
}

void Pe::setCMEM(long ins, int cycle){
    if(cycle==4){
        std::cout<<cycle;
    }
    insBuffer[cycle - 1] = ins;
}

void Pe::printExeInfo() {
    std::cout << "-----------------------------------------------------" << "pc : " << pc - 1 << "-----------------------------------------------------"<<"\n";
    std::cout<<"x :"<<x<<" y: "<<y<<" ins :"<<std::bitset<32>(ins)<<"\n";
    std::cout << "operand1 : " << operand1 << " operand2 : " << operand2 << "\n";
    std::cout << "aluTemp : " << ALUTemp << " memData : " << memData << " outTemp :" << outTemp << "\n";
    std::cout << "rf1 :" << rf1 << " rf2 :" << rf2 << " rf3 :" << rf3
              << " rf4 :" << rf4 << " rf5 :" << rf5;
//    std::cout << "rf1 :" << std::bitset<32>(rf1) << " rf2 :" << std::bitset<32>(rf2) << " rf3 :" << std::bitset<32>(rf3)
//      << " rf4 :" << std::bitset<32>(rf4) << " rf5 :" << std::bitset<32>(rf5);
    std::cout << std::endl;
}