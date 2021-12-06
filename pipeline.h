#ifndef PIPELINE_H
#define PIPELINE_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

#include "instructions.h"
#include "file_conversions.h"

class Pipeline{
    public:
    // int functions
    bool SearchCache(int data);
    int SearchMemory(int data);
    void LoadCache(int data, int index = 0);
    // overloaded float functions
    bool SearchCache(float data);
    int SearchMemory(float data);
    void LoadCache(float data, int index = 0);

    

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







template <typename T>
bool SearchCache(T data){
    /*
    Desc: checks to see if value being search for is in the cache
    Param: T data - an int or float value
    Output: true or false if it is in the cache
    */
    for(int i = 0; i < CACHE_DIM2; i++){
        if(cache[1][i] == data){ // finds the data
            return true;
        }
    }
    return false; // data not in cache
} 

template <typename T>
int SearchMemory(T data){
    /*
    Desc: looks through main memory for value
    Param: T data - float or int data to be found
    Output: index the memory is at
    */
    for(int i = 0; i < MEM_LOC; i++){
        if(mainMem[i] == data){ // finds data in main memory
            return i; // index where memory is
        }
    }
    return -1; // data not in main memory
    
}

template <typename T>
void LoadCache(T data){
    /*
    Desc: stores data in the cache
    Param: T data - float or int data 
    Output: none
    */
    int i = rand() % 4;
    m_cache[i] = data;
}

template <typename T>
T FindVal(int index){
    /*
    Desc: gets value from certain index in memory
    Param: int index - the index to get the memory from
    Output: the value at the index
    */
    if()

} 



#endif

