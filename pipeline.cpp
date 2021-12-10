#include "pipeline.h"

bool Pipeline::SearchCache(int data){
    /*
    Desc: checks to see if value being search for is in the cache
    Param: int data - an int value
    Output: true or false if it is in the cache
    */
     
    for(int i = 0; i < CACHE_DIM2; i++){
        if(cache[1][i].datatype == INT){ // checks that array value is an int
            if(cache[1][i].regData.integer.data_int == data){ // finds the data
                return true; // data in cache
            }
        }
        else{
            if(cache[1][i].regData.floatPt.data_fp == data){ // finds the data
                return true; // data in cache
            }
        }
    }
    return false; // data not in cache
}
int Pipeline::SearchMemory(int data){
    /*
    Desc: looks through main memory for value
    Param: int data - int data to be found
    Output: index the memory is at
    */
    for(int i = 0; i < MEM_LOC; i++){
        if(mainMem[i].datatype == INT){
            if(mainMem[i].regData.integer.data_int == data){ // finds data in main memory
                return i; // index where memory is
            }
        }
        else{
            if(mainMem[i].regData.floatPt.data_fp == data){ // finds data in main memory
                return i; // index where memory is
            }
        }
    }
    return -1; // data not in main memory
}
void Pipeline::LoadCache(int data, int index = 0){
    /*
    Desc: stores data in the cache
    Param: int data - int data 
    Output: none
    */
    int i = rand() % CACHE_DIM2; // find spot in cache to store data
    cache[1][i].datatype = INT; // sets array spot as int
    cache[1][i].regData.integer.data_int = data; 
    cache[1][i].regData.integer.index = index; 
}
bool Pipeline::SearchCache(float data){
    /*
    Desc: checks to see if value being search for is in the cache
    Param: float data - a float value
    Output: true or false if it is in the cache
    */
    for(int i = 0; i < CACHE_DIM2; i++){
        if(cache[1][i].datatype == FP){ // checks that array value is a float
            if(cache[1][i].regData.floatPt.data_fp == data){ // finds the data
                return true; // data in cache
            }
        }
        else{
            if(cache[1][i].regData.integer.data_int == data){ // finds the data
                return true; // data in cache
            }
        }
    }
    return false; // data not in cache
}
int Pipeline::SearchMemory(float data){
    /*
    Desc: looks through main memory for value
    Param: float data - float data to be found
    Output: index the memory is at
    */
    for(int i = 0; i < MEM_LOC; i++){
        if(mainMem[i].datatype == FP){ // array index spot is float
            if(mainMem[i].regData.floatPt.data_fp == data){ // finds data in main memory
                return i; // index where memory is
            }
        }
        else{ // array index spot is int
            if(mainMem[i].regData.integer.data_int == data){ // finds data in main memory
                return i; // index where memory is
            }
        }
    }
    return -1; // data not in main memory
}
void Pipeline::LoadCache(float data, int index = 0){
    /*
    Desc: stores data in the cache
    Param: float data - float data 
    Output: none
    */
    int i = rand() % CACHE_DIM2; // gets index to store data
    cache[1][i].datatype = FP; // sets array spot as float
    cache[1][i].regData.floatPt.data_fp = data;
    cache[0][i].regData.floatPt.index = index;
}

void Pipeline::GetFunction(vector<string> instr){
    if(instr.at(0) == "ADD.D"){
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPAdd(s, t);
    }
    else if(instr.at(0) == "SUB.D"){
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPSub(s, t);
    }
    else if(instr.at(0) == "MUL.D"){
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPMult(s, t);
    }
    else if(instr.at(0) == "DIV.D"){
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));
        
        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPDiv(s, t);
    }
    else if(instr.at(0) == "L.D"){
        int offsetVals[3]; 
        int offset;
        int di = GetRegLoc(instr.at(1));
        int data; 
        GetOffset(instr, offsetVals);
        if(offsetVals[1] == '$'){
            int s = intReg[offsetVals[2]];
            offset = offsetVals[0] + s;
            
        }
        else if(offsetVals[1] == 'F'){
            float s = fpReg[offsetVals[2]];
            offset = offsetVals[0] + s;
        }
        else{
            int s = offsetVals[2];
            offset = offsetVals[0] + s;
        }
        offset = offset%MEM_LOC;
        if(mainMem[offset].datatype == FP){
            data = mainMem[offset].regData.floatPt.data_fp;
        }
        else{
            data = mainMem[offset].regData.integer.data_int;
        }
        FPLoad(di, data);
    }
    else if(instr.at(0) == "S.D"){
        int offsetVals[3]; 
        int offset;
        int si = GetRegLoc(instr.at(1));
        int s = intReg[si];
        int data; 
        GetOffset(instr, offsetVals);
        if(offsetVals[1] == '$'){
            int d = intReg[offsetVals[2]];
            offset = offsetVals[0] + d;
        }
        else if(offsetVals[1] == 'F'){
            float d = fpReg[offsetVals[2]];
            offset = offsetVals[0] + d;
        }
        else{
            int d = offsetVals[2];
            offset = offsetVals[0] + d;
        }
        offset = offset%MEM_LOC;
        
        FPLoad(offset, s);
    }
    else if(instr.at(0) == "LI"){
        int di = GetRegLoc(instr.at(1));
        int s = atoi(instr.at(2).c_str());
        IntLoad(di, s);
    }
    else if(instr.at(0) == "LW"){
        int offsetVals[3]; 
        int offset;
        int di = GetRegLoc(instr.at(1));
        int data; 
        GetOffset(instr, offsetVals);
        if(offsetVals[1] == '$'){
            int s = intReg[offsetVals[2]];
            offset = offsetVals[0] + s;
            
        }
        else if(offsetVals[1] == 'F'){
            float s = fpReg[offsetVals[2]];
            offset = offsetVals[0] + s;
        }
        else{
            int s = offsetVals[2];
            offset = offsetVals[0] + s;
        }
        offset = offset%MEM_LOC;
        if(mainMem[offset].datatype == FP){
            data = mainMem[offset].regData.floatPt.data_fp;
        }
        else{
            data = mainMem[offset].regData.integer.data_int;
        }
        IntLoad(di, data);
    }
    else if(instr.at(0) == "SW"){
        int offsetVals[3]; 
        int offset;
        int si = GetRegLoc(instr.at(1));
        int s = intReg[si];
        int data; 
        GetOffset(instr, offsetVals);
        if(offsetVals[1] == '$'){
            int d = intReg[offsetVals[2]];
            offset = offsetVals[0] + d;
        }
        else if(offsetVals[1] == 'F'){
            float d = fpReg[offsetVals[2]];
            offset = offsetVals[0] + d;
        }
        else{
            int d = offsetVals[2];
            offset = offsetVals[0] + d;
        }
        offset = offset%MEM_LOC;
        
        IntLoad(offset, s);
    }
    else if(instr.at(0) == "ADD"){
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        int s = intReg[si];
        int t = intReg[ti];

        intReg[di] = IntAdd(s, t);
    }
    else if(instr.at(0) == "ADDI"){
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));

        int t = atoi(instr.at(3).c_str());
        int s = intReg[si];

        intReg[di] = IntAdd(s, t);

    }
    else if(instr.at(0) == "SUB"){
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        int s = intReg[si];
        int t = intReg[ti];

        intReg[di] = IntSub(s, t);
    }
    else if(instr.at(0) == "BEQ"){
        
    }
    else if(instr.at(0) == "BNE"){

    }
    else if(instr.at(0) == "J"){

    }

    
}


const string FP_ADD_INSTR[2] = {"ADD.D", "SUB.D"};
const string FP_MULT_INSTR[1] = {"MUL.D"};
const string FP_DIV_INSTR[1] = {"DIV.D"};
const string INT_UNIT_INSTR[11] = {"L.D", "S.D", "LI", "LW", "SW", 
                                    "ADD", "ADDI", "SUB", "BEQ", "BNE", "J"};


int IntTasks::FindVal(int index){
    /*
    Desc: gets value from certain index in memory
    Param: int index - the index to get the memory from
    Output: the value at the index
    */
    
    if(mainMem[index].datatype == INT){
        return mainMem[index].regData.integer.data_int;
    }
    return (int)mainMem[index].regData.floatPt.data_fp;
    
}

float FloatTasks::FindVal(int index){
    /*
    Desc: gets value from certain index in memory
    Param: int index - the index to get the memory from
    Output: the value at the index
    */
   if(mainMem[index].datatype == INT){
        return (float)mainMem[index].regData.integer.data_int;
    }
    return mainMem[index].regData.floatPt.data_fp;
}





