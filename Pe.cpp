//
// Created by geray on 2022/12/26.
//

#include "Pe.h"

Pe::Pe() {}
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
            operand = ALUTemp;
            break;
        case 6:
            operand = SELA(ins);
            break;
        default:
            throw "SELA error!";
    }
}
void Pe::recvData() {
    getOperand(this->operand1,SELA(ins));
    getOperand(this->operand2,SELB(ins));
}
void Pe::execute() {
    pc = pc + 1;
    ins = insBuffer[pc];
    // mux
    recvData();
    // alu
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
        default:
            throw "opcode error";
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
    }
    writeback();
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
void Pe::printExeInfo(std::iostream f) {
    f << "-----------------------------------------------------" << "pc : " << pc
      << "-----------------------------------------------------";
    f << "pc : " << this->pc << " ins: " << this->ins << "\n";
    f << "operand1 : " << operand1 << " operand2 : " << operand2 << "\n";
    f << "aluTemp : " << ALUTemp << " memData : " << memData << " outTemp :" << outTemp << "\n";
    f << "rf1 :" << std::bitset<32>(rf1) << " rf2 :" << std::bitset<32>(rf2) << " rf3 :" << std::bitset<32>(rf3)
      << " rf4 :" << std::bitset<32>(rf4) << "rf5 :" << std::bitset<32>(rf5);
    f << std::endl;
}