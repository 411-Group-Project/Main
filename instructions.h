#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

float FPAdd(float source, float target); 
float FPSub(float source, float target); 
int IntAdd(int source, int target);
int IntSub(int source, int target); 
float FPMult(float source, float target); 
float FPDiv(float source, float target); 
void IntLoad(int dest, int source);
void IntStore(int dest, int source);
void FPLoad(int dest, float source);
void FPStore(int dest, float source);
int BranchEqual(int source, int target, int size, string loop);
int BranchNotEqual(int source, int target, int size, string loop); 
int Jump(int size, string loop);

#endif