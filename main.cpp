#include "file_conversions.h"
//extern vector<string>* arr2; //use it when it needed later
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
    delete []arr;
    return 0;
}