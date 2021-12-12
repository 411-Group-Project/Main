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

    void GetFunction(vector<string> instr, int& index);

    protected:
};

class IntTasks:public Pipeline{
    public:
    int FindVal(int index);

};

class FloatTasks:public Pipeline{
    public:
    float FindVal(int index);

};

#endif

