//
// Created by geray on 2022/12/27.
//

#include "CGRA.h"
#include "fstream"
#include "sstream"
#include "string"
#define LOG
using namespace std;
void CGRA::parseMemFile(string filename) {
    // TODO :: parse Memfile
    ifstream file(filename);
    if(!file.is_open()){
        std::cout << "can not open file "<<filename << std::endl;
        exit(-1);
    }
    string line;
    int addr = 0;
    while(getline(file,line)){
        int index = stoi(line);
        getline(file,line);
        istringstream iss(line);
//        cout << " ------------------- index: " << index << " -----------------" << endl;
        for(int i = 0; i < 6; i++){
            int tmp = 0;
            iss >> tmp;
//            cout << tmp << endl;
            dram[index].insert(pair(i,tmp));
        }
    }
//    printDRAM();
//   exit(0);
}
void CGRA::parseInsFile(std::string filename) {
    // TODO :: parse Insfile
    std::ifstream insfile(filename);
    if(!insfile.is_open()){
        std::cout << "can not open file "<<filename << std::endl;
        exit(-1);
    }
    std::string line;
//    int index = 1;
    int cycle = 0;
    while(getline(insfile,line)){
        cycle = stoi(line);
        //      std::cout << cycle << std::endl;
       long ins = 0;
        for(int i=0; i< this->sizeX;i++) {
            for (int j = 0; j < this->sizeY; j++) {
                getline(insfile,line);
                ins = stol(line,0,2);
//                std::cout  <<ins << std::endl;
                tiles[i][j].setCMEM(ins,cycle);
            }
        }
    }
//    CGRA::printCMEM();
//    exit(0);


}
CGRA::CGRA(int sizex,int sizey) {
    sizeX = sizex;
    sizeY = sizey;
    tiles = new Pe * [sizex];
    for(int i=0;i<sizex;i++){
        tiles[i] = new Pe[sizey];
    }
    // classify petype
    for(int i=0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            if(j==0){
                tiles[i][j].peType = MPE;
                tiles[i][j].DRAM = &this->dram[i];
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
        // TODO::condition need re considerate, for example cycle <= require_cycle
        for(int i=0;i<sizeX;i++){
            for(int j=0;j<sizeY;j++){
                tiles[i][j].execute();
#ifdef LOG
                tiles[i][j].printExeInfo();
#endif
            }
        }
    }
}

void CGRA::printCMEM(){
    for(int cycle = 1; cycle < 24; cycle++){
        cout << cycle << endl;
        for(int i = 0; i < sizeX;i++){
            for(int j = 0; j < sizeY;j++){
                cout << tiles[i][j].insBuffer[cycle-1] << endl;
            }
        }

    }
}

void CGRA::printDRAM(){
    for(int i = 0 ; i < 4; i++){
        auto DRAM_map = dram[i];
        std::cout << "------------------ index: " << i << "--------------------" << std::endl;
        for (auto it=DRAM_map.begin(); it!=DRAM_map.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

    }

}