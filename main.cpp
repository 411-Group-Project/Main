#include "pipeline.h"
//extern vector<string>* arr2; //use it when it needed later


int main(int argc, char *argv[]){
    
    vector<vector<string> > parsedInstrArr;
    Array_t cache[CACHE_DIM];
    Array_t mainMem[MEM_LOC];
    int intReg[REG_SIZE];
    float fpReg[REG_SIZE];

    string file;
    if(argv[1]){
        file = argv[1];
    }
    else{
        file = "input.txt";
    }
    int numLines = FileSize(file);
    string *arr = new string[numLines]; 
    ReadFile(numLines, file, arr);
    ParseInstr(arr, numLines);
    SetMemory();
    delete []arr;
    return 0;
}