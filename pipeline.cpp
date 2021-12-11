#include "pipeline.h"

bool Pipeline::SearchCache(int data){
    /*
    Desc: checks to see if value being search for is in the cache
    Param: int data - an int value
    Output: true or false if it is in the cache
    */
     
    for(int i = 0; i < CACHE_DIM; i++){
        if(cache[i].datatype == INT){ // checks that array value is an int
            if(cache[i].regData.integer.data_int == data){ // finds the data
                return true; // data in cache
            }
        }
        else{
            if(cache[i].regData.floatPt.data_fp == data){ // finds the data
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
void Pipeline::LoadCache(int data, int index){
    /*
    Desc: stores data in the cache
    Param: int data - int data 
    Output: none
    */
    int i = rand() % CACHE_DIM; // find spot in cache to store data
    cache[i].datatype = INT; // sets array spot as int
    cache[i].regData.integer.data_int = data; 
    cache[i].regData.integer.index = index; 
}
bool Pipeline::SearchCache(float data){
    /*
    Desc: checks to see if value being search for is in the cache
    Param: float data - a float value
    Output: true or false if it is in the cache
    */
    for(int i = 0; i < CACHE_DIM; i++){
        if(cache[i].datatype == FP){ // checks that array value is a float
            if(cache[i].regData.floatPt.data_fp == data){ // finds the data
                return true; // data in cache
            }
        }
        else{
            if(cache[i].regData.integer.data_int == data){ // finds the data
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
void Pipeline::LoadCache(float data, int index){
    /*
    Desc: stores data in the cache
    Param: float data - float data 
    Output: none
    */
    int i = rand() % CACHE_DIM; // gets index to store data
    cache[i].datatype = FP; // sets array spot as float
    cache[i].regData.floatPt.data_fp = data;
    cache[i].regData.floatPt.index = index;
}

void Pipeline::GetFunction(vector<string> instr, int& index){
    /*
    Desc: calls the different functions depending on instruction
    Param: vector<string> instr - instruction to be executed
           int& index - the index of where the current intsruction is in 
           vector of vector
    Output: none
    */
    if(instr.at(0) == "ADD.D"){
        // finds the index of the FP regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        // gets values from FP regs
        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPAdd(s, t); // adds/stores values in dest reg
    }
    else if(instr.at(0) == "SUB.D"){
        // finds the index of the FP regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        // gets value from fp regs
        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPSub(s, t); // fp subtraction
    }
    else if(instr.at(0) == "MUL.D"){
        // finds the index of the FP regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        // gets value from fp regs
        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPMult(s, t); // fp multiplication
    }
    else if(instr.at(0) == "DIV.D"){
        // finds the index of the FP regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));
        
        // gets values from fp regs
        float s = fpReg[si];
        float t = fpReg[ti];
        
        fpReg[di] = FPDiv(s, t); // fp division
    }
    else if(instr.at(0) == "L.D"){
        int offsetVals[3]; // offset values
        int offset;
        int di = GetRegLoc(instr.at(1)); // dest index to load to
        int data; // value in main mem

        // gets offset and turns into index
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

        // get data from main mem
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
        int offsetVals[3]; // holds offset values
        int offset;
        int si = GetRegLoc(instr.at(1));
        int s = intReg[si]; // reg value to store in main mem

        // gets offset and turns into index
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
        offset = offset%MEM_LOC; // index for main mem
        
        FPStore(offset, s);
    }
    else if(instr.at(0) == "LI"){
        int di = GetRegLoc(instr.at(1)); // dest index for reg to load into
        int s = atoi(instr.at(2).c_str()); // the immediate value to store
        IntLoad(di, s);
    }
    else if(instr.at(0) == "LW"){
        int offsetVals[3]; // holds offset value
        int offset; 
        int di = GetRegLoc(instr.at(1)); // dest index for reg
        int data; // data from main mem

        // gets offset and turns into index
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

        // gets data from main memory
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
        int offsetVals[3]; // array to hold offset values
        int offset; // holds offset value

        int si = GetRegLoc(instr.at(1));
        int s = intReg[si]; // value from reg

        // gets offset and gets values from it to make index 
        GetOffset(instr, offsetVals);
        if(offsetVals[1] == '$'){ // int reg
            int d = intReg[offsetVals[2]];
            offset = offsetVals[0] + d;
        }
        else if(offsetVals[1] == 'F'){ // fp reg
            float d = fpReg[offsetVals[2]];
            offset = offsetVals[0] + d;
        }
        else{ // immediate
            int d = offsetVals[2];
            offset = offsetVals[0] + d;
        }

        offset = offset%MEM_LOC; // get index for mainMem address
        
        IntStore(offset, s);
    }
    else if(instr.at(0) == "ADD"){
        // finds the index of the int regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        // gets values from regs
        int s = intReg[si];
        int t = intReg[ti];

        intReg[di] = IntAdd(s, t);
    }
    else if(instr.at(0) == "ADDI"){
        // finds the index of the int regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));

        // gets the int immediate
        int t = atoi(instr.at(3).c_str());
        int s = intReg[si]; // gets value from reg

        intReg[di] = IntAdd(s, t);

    }
    else if(instr.at(0) == "SUB"){
        // finds the index of the int regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));
        int ti = GetRegLoc(instr.at(3));

        // gets values from reg
        int s = intReg[si];
        int t = intReg[ti];

        intReg[di] = IntSub(s, t); 
    }
    else if(instr.at(0) == "BEQ"){
        // finds the index of the int regs to get values from
        int si = GetRegLoc(instr.at(1));
        int ti = GetRegLoc(instr.at(2));
        string branch = instr.at(3); // gets branch name 
        
        // gets values from regs
        int s = intReg[si];
        int t = intReg[ti];
        index = BranchEqual(s, t, parsedInstrArr.size(), branch); // gets new index to start at
        
    }
    else if(instr.at(0) == "BNE"){
        // finds the index of the int regs to get values from
        int si = GetRegLoc(instr.at(1));
        int ti = GetRegLoc(instr.at(2));
        string branch = instr.at(3); // gets branch name
        
        // gets values from regs
        int s = intReg[si];
        int t = intReg[ti];
        index = BranchNotEqual(s, t, parsedInstrArr.size(), branch); // gets new index to start at
    }
    else if(instr.at(0) == "J"){
        string branch = instr.at(1); // gets branch name
        index = Jump(parsedInstrArr.size(), branch); // gets new index to start at
    }

    
}

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





