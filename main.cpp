#include "pipeline_output.h"
//extern vector<string>* arr2; //use it when it needed later

vector<vector<string> > parsedInstrArr;
Array_t cache[CACHE_DIM];
Array_t mainMem[MEM_LOC];
int intReg[REG_SIZE];
float fpReg[REG_SIZE];
int main(int argc, char *argv[]){

    string file;
    if(argv[1]){
        file = argv[1];
    }
    else{
        file = "input.txt";
    }
    int numLines = FileSize(file);
    string *arr = new string[numLines]; 
    ReadFile(numLines, file, arr);
    ParseInstr(arr, numLines);
    SetMemory();
    /*
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
    }*/
    Action();
    delete []arr;
    return 0;
}
