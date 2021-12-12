#include "instructions.h"
/*
NOTE TO SELF

You want to only pass in the source and target into the function
and return the operated value because you have to check cache for 
diffrent values first, rather than just eailsy pull from a certain
register.

if the conditions return -1, the condition failed
if the condition return -2, throw exception

*/

float FPAdd(float source, float target){
    /*
    Desc: does floating point addition
    Param: float source - first number to add
         : float target - second number to add
    Output: sum of floats
    */
    return source + target;
}
float FPSub(float source, float target){
    /*
    Desc: does floating point subtraction
    Param: float source - number to subtract from
         : float target - number to subtract
    Output: difference of floats
    */
   return source - target;
}
int IntAdd(int source, int target){
    /*
    Desc: does integer addition
    Param: int source - first number to add
         : int target - second number to add
    Output: sum of ints
    */
   return source + target;
}
int IntSub(int source, int target){
    /*
    Desc: does integer subtraction
    Param: int source - number to subtract from
         : int target - number to subtract
    Output: difference of ints
    */
   return source - target;
}
float FPMult(float source, float target){
    /*
    Desc: does floating point multiplication
    Param: float source - first number to multiply
         : float target - second number to multiply
    Output:
    */
   return source * target;
}
float FPDiv(float source, float target){
    /*
    Desc: does floating point division
    Param: float source - number to divide from
         : float target - number to divide
    Output:
    */
   return source / target;
}
void FPLoad(int dest, float source){
    /*
    Desc: loads floating point number in register
    Param: int dest - the index of the register to load into
           float source - the number to load
    Output: none
    */
    fpReg[dest] = source;
}
void FPStore(int dest, float source){
    /*
    Desc: stores floating point number in register
    Param: int dest - the index of the register to store into
           float source - the number to store
    Output: none
    */
   mainMem[dest].datatype = FP;
   mainMem[dest].regData.floatPt.data_fp = source;
}
void IntLoad(int dest, int source){
    /*
    Desc: loads integer number in register
    Param: int dest - the index of the register to load into
           int source - the number to load
    Output: none
    */
   intReg[dest] = source;
}
void IntStore(int dest, int source){
    /*
    Desc: stores integer number in register
    Param: int dest - the index of the register to store into
           int source - the number to store
    Output: none
    */
   mainMem[dest].datatype = INT;
   mainMem[dest].regData.integer.data_int = source;
}
int BranchEqual(int source, int target, int size, string branch){
    /*
    Desc: finds the branch to return/go to based on if equal
    Param: int source - the first number to compare
           int target - the second number to compare
           int size - size of the array of vectors
           string branch - the branch to go to if condition is met
    Output: index of the branch or loop instruction or -1 if not found
    */
    if(source == target){ // values equal, instruction satisfied
        for(int i = 0; i < size; i++){
            if(parsedInstrArr[i].at(0) == branch){ // finds branch to go to
                return i; // return index
            }
        }
        return -2; // branch does not exist
    }

    return -1; // continue
}
int BranchNotEqual(int source, int target, int size, string branch){
    /*
    Desc: finds the branch to return/ go to based on if not equal
    Param: int source - the first number to compare
           int target - the second number to compare
           int size - size of the array of vectors
           string branch - the branch to go to if condition is met
    Output: index of the branch or loop instruction or -1 if not found
    */
    if(source != target){ // values not equal, instruction satisfied
        for(int i = 0; i < size; i++){
            if(parsedInstrArr[i].at(0) == branch){ // finds branch to go to
                return i; // returns index
            }
        }
        return -2; // branch doesn't exist
    }
    
    return -1; // continue 
}
int Jump(int size, string branch){
    /*
    Desc: finds the index to go to
    Param: int size - size of the array of vectors of instructions
           string branch - the branch to jump to
    Output: index to to go to or -1 if not found
    */

    for(int i = 0; i < size; i++){
        if(parsedInstrArr[i].at(0) == branch){ // find branch to go to
            return i; // returns index
        }
    }
    return -2; // branch doesn't exist
}