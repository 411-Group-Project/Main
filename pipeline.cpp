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

    int j = CheckIndex(index);
    if(j != -1){ // index exists
        if(cache[j].datatype == FP){
            cache[j].datatype = INT; // make slot int
            cache[j].regData.integer.data_int = data; // update the data
        }
        else{
            cache[j].regData.integer.data_int = data; // update the data
        }
    }    
    else{
        int i = rand() % CACHE_DIM; // find spot in cache to store data

        if(CheckFull()){ // cache is full
            if(cache[i].datatype == FP){
                float data = cache[i].regData.floatPt.data_fp;
                int idx = cache[i].regData.floatPt.index; 
                ReturnMem(data, idx); // return float back to main memory
            }
            else{
                int data = cache[i].regData.integer.data_int;
                int idx = cache[i].regData.integer.index; 
                ReturnMem(data, idx); // return int back to main memory
            }
        }
        else{
            while(!CheckEmpty(i)){ // makes sure empty spaces are all taken up first
                i = rand() % CACHE_DIM; // gets index to store data
            }
        }

        cache[i].datatype = INT; // sets array spot as int
        cache[i].regData.integer.data_int = data; 
        cache[i].regData.integer.index = index; 
    }
}
void Pipeline::ReturnMem(int data, int index){
    /*
    Desc: sends memory in cache back to main memory
    Param: int data - the data to return
           int index - index of where to return data
    Output: none
    */
    mainMem[index].datatype = INT;
    mainMem[index].regData.integer.data_int = data;
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
           int index - index of data in main memory
    Output: none
    */

    int j = CheckIndex(index);
    if(j != -1){ // index exists
        if(cache[j].datatype == FP){
            cache[j].regData.floatPt.data_fp = data; // update the data
        }
        else{
            cache[j].datatype = FP; // make slot fp
            cache[j].regData.floatPt.data_fp = data; // update the data
        }
    }
    else{
        int i = rand() % CACHE_DIM; // gets index to store data
        if(CheckFull()){ // check cache full
            if(cache[i].datatype == FP){
                float data = cache[i].regData.floatPt.data_fp;
                int idx = cache[i].regData.floatPt.index; 
                ReturnMem(data, idx); // ratuen value at i
            }
            else{
                int data = cache[i].regData.integer.data_int;
                int idx = cache[i].regData.integer.index; 
                ReturnMem(data, idx); // return value at i
            }
        }
        else{
            while(!CheckEmpty(i)){ // makes sure every empty spot taken first
                i = rand() % CACHE_DIM; // gets index to store data
            }
        }

        cache[i].datatype = FP; // sets array spot as float
        cache[i].regData.floatPt.data_fp = data;
        cache[i].regData.floatPt.index = index;
    }
}

void Pipeline::ReturnMem(float data, int index){
    /*
    Desc: sends memory in cache back to main memory
    Param: float data - the data to return
           int index - index of where to return data
    Output: none
    */
    mainMem[index].datatype = FP;
    mainMem[index].regData.floatPt.data_fp = data;
}

bool Pipeline::CheckEmpty(int j){
    /*
    Desc: checks if cache spot is empty
    Param: int j - index of cache to check
    Output: true = empty, false = taken
    */

    if(cache[j].datatype == FP){
        if(cache[j].regData.floatPt.index == -1){ // empty
            return true;
        }
    }
    else{
        if(cache[j].regData.integer.index == -1){ // empty
            return true;
        }
    }
    return false; // not empty index
}

bool Pipeline::CheckFull(){
    /*
    Desc: checks if cache is full
    Param: none
    Output: true = full, false = not full
    */
    for(int i = 0; i < CACHE_DIM; i++){
        if(cache[i].datatype == FP){ // get type
            if(cache[i].regData.floatPt.index == -1){ // empty spot
                return false;
            }
        }
        else{
            if(cache[i].regData.integer.index == -1){ // empty spot
                return false; 
            }
        }
    }
    return true; // full
}

int Pipeline::CheckIndex(int index){
    /*
    Desc: checks if index is already in cache
    Param: int index - the index to check for
    Output: -1 if index is not there, the i in the cache whre index is
    */

    for(int i = 0; i < CACHE_DIM; i++){
        if(cache[i].datatype == FP){ // check type
            if(cache[i].regData.floatPt.index == index){ // indices equal
                return i; // return equal index
            }
        }
        else{
            if(cache[i].regData.integer.index == index){ // indices equal
                return i; // return equal index
            }
        }
    }
    return -1;
}

int Pipeline::GetFunction(vector<string> instr){
    /*
    Desc: calls the different functions depending on instruction
    Param: vector<string> instr - instruction to be executed
    Output: number correspoing to index, hit, miss, or continue 
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
        return CONT;
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
        return CONT;
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
        return CONT;
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
        return CONT;
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
        // Search for hit/miss then loads cachie
        if(SearchCache(data)){
            return HIT;
        }
        LoadCache(data, offset);
        return MISS;
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

        // Search for hit/miss then loads cache
        if(SearchCache(s)){
            return HIT;
        }
        LoadCache(s, offset);
        return MISS;
    }
    else if(instr.at(0) == "LI"){
        int di = GetRegLoc(instr.at(1)); // dest index for reg to load into
        int s = atoi(instr.at(2).c_str()); // the immediate value to store
        IntLoad(di, s);
        return CONT;
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

        // Search for hit/miss then loads cache
        if(SearchCache(data)){
            return HIT;
        }
        LoadCache(data, offset);
        return MISS;
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

        // Search for hit/miss then loads cache
        if(SearchCache(s)){
            return HIT;
        }
        LoadCache(s, offset);
        return MISS;
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
        return CONT;
    }
    else if(instr.at(0) == "ADDI"){
        // finds the index of the int regs to get values from
        int di = GetRegLoc(instr.at(1));
        int si = GetRegLoc(instr.at(2));

        // gets the int immediate
        int t = atoi(instr.at(3).c_str());
        int s = intReg[si]; // gets value from reg

        intReg[di] = IntAdd(s, t);
        return CONT;
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
        return CONT; 
    }
    else if(instr.at(0) == "BEQ"){
        // finds the index of the int regs to get values from
        int si = GetRegLoc(instr.at(1));
        int ti = GetRegLoc(instr.at(2));
        string branch = instr.at(3); // gets branch name 
        
        // gets values from regs
        int s = intReg[si];
        int t = intReg[ti];
        return BranchEqual(s, t, parsedInstrArr.size(), branch); // gets new index to start at   
    }
    else if(instr.at(0) == "BNE"){
        // finds the index of the int regs to get values from
        int si = GetRegLoc(instr.at(1));
        int ti = GetRegLoc(instr.at(2));
        string branch = instr.at(3); // gets branch name
        
        // gets values from regs
        int s = intReg[si];
        int t = intReg[ti];
        return BranchNotEqual(s, t, parsedInstrArr.size(), branch); // gets new index to start at
    }
    else if(instr.at(0) == "J"){
        string branch = instr.at(1); // gets branch name
        return Jump(parsedInstrArr.size(), branch); // gets new index to start at
    }

    throw "Instruction does not exist!";
}





/*

-1 = just continue
-2 = branch DNE
-3 = instruction DNE
-5 = hit
-10 = miss



*/
