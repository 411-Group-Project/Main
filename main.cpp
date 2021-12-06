#include "file_conversions.h"
extern vector<string>* arr2;
int main(int argc, char *argv[]){
    string file;
    if(argv[1]){
        file = argv[1];
    }
    else{
        file = "input.txt";
    }
    int numLines = FileSize(file);
    string arr[numLines]; 
    ReadFile(numLines, file, arr);
    vector<string> arr2[numLines]; 
    ParseInstr(arr, numLines);

    return 0;
}