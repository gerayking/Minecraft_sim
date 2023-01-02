//
// Created by geray on 2022/12/27.
//

#include "CGRA.h"
#define LOG

void CGRA::parseMemFile() {
    // TODO :: parse Memfile
}
void CGRA::parseInsFile() {
    // TODO :: parse Insfile
}
CGRA::CGRA(int sizex,int sizey) {
    this->sizeX=sizeX;
    this->sizeY=sizey;
    tiles = new Pe * [sizex];
    for(int i=0;i<sizex;i++){
        tiles[i] = new Pe[sizey];
    }
    // classify petype
    for(int i=0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            if(j==0||j==sizey-1){
                tiles[i][j].peType = MPE;
                tiles[i][j].DRAM = &this->dram;
            }else{
                tiles[i][j].peType = NPE;
                tiles[i][j].DRAM = nullptr;
            }
        }
    }
    //connect pe
    for(int i=0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            if(i!=0)tiles[i][j].inN=&tiles[i-1][j];
            if(i!=sizex-1)tiles[i][j].inE=&tiles[i+1][j];
            if(j!=0)tiles[i][j].inW=&tiles[i][j-1];
            if(j!=sizey-1)tiles[i][j].inS=&tiles[i][j+1];
        }
    }
}

void CGRA::run() {

    while(1){
        // TODO::condition need re-considerate, for example cycle <= require_cycle
        for(int i=0;i<sizeX;i++){
            for(int j=0;j<sizeY;j++){
                tiles[i][j].execute();
#ifdef LOG
                //TODO:: print log here by call tiles.printExeInfo()
#endif
            }
        }
    }
}