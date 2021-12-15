#include "pipeline_output.h"

vector<vector<string> > parsedInstrArr;
vector<vector<string> > pipelineVect;
Array_t cache[CACHE_DIM];
Array_t mainMem[MEM_LOC];
int intReg[REG_SIZE];

int main(int argc, char *argv[]){

    string file;
    if(argv[1]){ // get file from command line
        file = argv[1];
    }
    else{
        file = "input2.txt";
    }

    // get everything from the files and set up memory
    int numLines = FileSize(file);
    string *arr = new string[numLines]; 
    ReadFile(numLines, file, arr); //Read file
    ParseInstr(arr, numLines); //Start to parsing instruction
    SetMemory(); //Set the Memory

    Action(arr, numLines); //Call Action to start piplining
    Display(); //Display the result and read it in an exel file name result.csv

    // print integer registers
    cout << "\nInteger Register" << endl;
    cout << "| ";
    for(int i = 0; i < REG_SIZE; i++){
        cout << i << ": " << intReg[i] <<  " | "; 
    }

    // print float register
    cout << "\n\nFloating Point Register" << endl;
    cout << "| ";
    for(int i = 0; i < REG_SIZE; i++){
        cout << i << ": " << fpReg[i] <<  " | "; 
    }

    // print main memory
    cout << "\n\nMain Memory" << endl;
    cout << "| ";
    for(int i = 0; i < MEM_LOC; i++){
        if(mainMem[i].datatype == FP){
            cout << i << ": " << mainMem[i].regData.floatPt.data_fp <<  " | "; 
        }
        else{
            cout << i << ": " << mainMem[i].regData.integer.data_int <<  " | "; 
        }
    }
    
    delete []arr; 
    return 0;
}
