#ifndef PIPELINE_H
#define PIPELINE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

#include "instructions.h"

class Pipeline{
    public:
    // int functions
    bool SearchCache(int data);
    int SearchMemory(int data);
    void LoadCache(int data, int index);
    
    // overloaded float functions
    bool SearchCache(float data);
    int SearchMemory(float data);
    void LoadCache(float data, int index);

    void ReturnMem(float data, int index);
    void ReturnMem(int data, int index);

    bool CheckEmpty(int j);
    bool CheckFull();
    int CheckIndex(int index);
    

    int GetFunction(vector<string> instr);
    int StartPipeline(vector<string> instr);

};

#endif

