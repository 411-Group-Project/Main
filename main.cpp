#include "pipeline_output.h"
//extern vector<string>* arr2; //use it when it needed later

vector<vector<string> > parsedInstrArr;
vector<vector<string> > pipelineVect;
Array_t cache[CACHE_DIM];
Array_t mainMem[MEM_LOC];
int intReg[REG_SIZE];
vector<string> original; 
//float fpReg[REG_SIZE];
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

<<<<<<< HEAD
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
=======
    // start pipeline
    Pipeline pip;
    int newIndex;
    for(int i = 0; i < parsedInstrArr.size(); i++){
        if(parsedInstrArr.at(i).size() > 1){ // makes sure labels are executed
            try{
                newIndex = pip.GetFunction(parsedInstrArr.at(i));
            }catch(const char* error){
                cout << error << endl;
            }
            if(newIndex > CONT){ //condition or jump needs to happen
                i = newIndex;
            }
            else if(newIndex == MISS){
                cout << "Add some stalls" << endl;
            }
        }
    }

    // organinze pipeline
    vector<vector<string> > newPipelineVector;
    for (int i = 0; i < pipelineVect.size(); i++){
        int startPos;
        vector<string> j = pipelineVect[i];
        startPos = pip.StartPipeline(j);
        j.erase(j.begin() + startPos);
        
        int temp = i;
        while(temp > 0){
            j.erase(j.begin());
            temp--;
        }
        newPipelineVector.push_back(j);
    }
     
    //print pipeline 
    cout << "Pipeline" << endl;
    for (int i = 0; i < newPipelineVector.size(); i++){
        cout << "[ ";

        for (auto j : newPipelineVector[i]){
            cout << j << " ";
        }    
        cout << "]" << endl;
    }

    cout << "| index: data |" << endl;

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
>>>>>>> main
    return 0;
}
