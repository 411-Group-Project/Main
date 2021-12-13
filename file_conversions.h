#ifndef STRING_CONV_H
#define STRING_CONV_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

// cycles for instructions
const int INT_UNIT = 1;
const int FP_ADDER = 2;
const int FP_MULT = 10;
const int FP_DIV = 40;

const int MEM_LOC = 19; // use this to loop through memory
const int REG_SIZE = 32;
const int CACHE_DIM = 4;

// instructions for each specific type
const string FP_ADD_INSTR[2] = {"ADD.D", "SUB.D"};
const string FP_MULT_INSTR[1] = {"MUL.D"};
const string FP_DIV_INSTR[1] = {"DIV.D"};
const string INT_UNIT_INSTR[11] = {"L.D", "S.D", "LI", "LW", "SW", 
                                    "ADD", "ADDI", "SUB", "BEQ", "BNE", "J"};

typedef struct Array_t Array_t;
typedef enum dataType{INT,FP} dataType_t;
enum functOutVals{CONT=-1,HIT=-2, MISS=-3};

extern vector<vector<string> > parsedInstrArr;
extern Array_t cache[CACHE_DIM];
extern Array_t mainMem[MEM_LOC];
extern int intReg[REG_SIZE];
extern float fpReg[REG_SIZE];

typedef struct Integer{
    int index;
    int data_int;
} Int_t;

typedef struct FP{
    int index;
    float data_fp;
} FP_t;

typedef union number{
    // union of integer and floating point types for the main
    // memory and cache arrays
    Int_t integer;
    FP_t floatPt;
} num_t;

struct Array_t {
    num_t regData; // union of the types of data
    dataType_t datatype; // integer or floating point
};


int FileSize(string file);
void ReadFile(int numLine, string file, string* instrArr);
void ParseInstr(string* instrArr, int arrSize);
//vector<string> split (string s, string delimiter);
vector<string> Split(string& instr);
//void RemoveColon(string& instr);
int* GetOffset(vector<string> instr, int offsetArray[]);
void OffsetArray(string offsetString, int offsetArr[]);
int GetRegLoc(string reg);
void SetMemory();


#endif
