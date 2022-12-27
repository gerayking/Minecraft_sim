//
// Created by geray on 2022/12/27.
//

#ifndef CGRA_INS_H
#define CGRA_INS_H

#endif //CGRA_INS_H

#define IMM(x) (x & 0xffff)
#define OPCODE(x) ((x>>16)&0x1f)
#define SELA(x) ((x>>21)&0x7)
#define SELB(x) ((x>>24)&0x7)
#define SELOUT(x) ((x>>27)&0x1f)

#define ADD   0b00000
#define SUB   0b00001
#define MUL   0b00010
#define DIV   0b00011
#define LOAD  0b00100
#define STORE 0b00101
#define LS    0b00110
#define RS    0b00111
#define AND   0b01000
#define OR    0b01001
#define XOR   0b01010
#define CMP   0b01011
#define CLT   0b01100
#define CGT   0b01101


#define dataType int
#define insType int
#define insLimit 64
#define addrType int