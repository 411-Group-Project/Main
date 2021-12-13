#include "file_conversions.h"

int FileSize(string file){
    /*
    Desc: This function will determine how many lines are in the
          text file
    Param: none
    Output: number of lines in the file
    */
    string line; // holds line of the file
    int count = 0; // number of lines in file
    ifstream myfile(file);
    if (myfile.is_open()){
        while(getline (myfile,line)){ // reads line from file
            count++;
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file"; 
    }
    return count;
}

void ReadFile(int numLine, string file, string* instrArr){
    /*
    Desc: reads in every line from text file and stores each line 
          in an array
    Param: int numLine - number of lines in the file
           string file - ttext file to read from
           string* instrArr - arr to hold each line from text file
    Output: none
    */
    string line; // holds line of the file
    int i = 0; // index for array
    ifstream myfile(file);
    if (myfile.is_open()){
        while(getline (myfile,line)){ // reads line from file
            instrArr[i] = line;
            original.push_back(line); //store the original data
            i++;
        }
        for (int i = 0; i < numLine; i++){
            cout << instrArr[i]<<endl;
        }
        myfile.close();
    }
    else{ 
        cout << "Unable to open file" << endl; 
    }
}

void ParseInstr(string* instrArr, int arrSize){
    /*
    Desc: This function parses splits each instruction into its parts
    Param: string* instrArr - array of instructions read from text file
           int arrSize - size of the instrArr
           vector<string>** parsedInstrArr - array of vectors
    Output: none
    */
   
    for(int i = 0; i < arrSize; i++){ // size of array for each instruction
       parsedInstrArr.push_back(Split(instrArr[i])); 
       // RemoveColon(instrArr[i]);
       // parsedInstrArr[i] = split(instrArr[i], " "); // stores vector and index i of array

    }
    //this is for testing to see if parsedInstrArr contains correct values
    cout <<"vector: "<<endl;
    for (unsigned int i = 0; i < parsedInstrArr.size(); i++) {
        for(unsigned int j = 0; j < parsedInstrArr[i].size(); j++){
            cout <<parsedInstrArr[i][j] << endl;
        }
        cout << endl;
    }
}

vector<string> Split(string& instr){
    /*
    Desc: This function removes the commas in a string and replaces
          them with spaces
    Param: string& instr - the string with the commas
    Output: none
    */
   string delimiter = " ";
   size_t posStart = 0; // start of substring
   size_t posEnd, delimLen = delimiter.length(); //end of substring
   string token; // substring before delimiter
   vector<string> res; // vector hold the substrings

    for(int i = 0; i < instr.size(); i++){ // goes through each index of string
        if(instr[i] == ','){
            instr.erase(instr.begin() + i); // deletes comma
        }
        if (instr[i] == ':'){
            instr.erase(instr.begin() + i); // deletes colon
            res.push_back(instr);
            return res;
        }
    }
     while ((posEnd = instr.find(delimiter, posStart)) != string::npos){ // find the delimiter
        token = instr.substr(posStart, posEnd - posStart);
        posStart = posEnd + delimLen; // new start posistion after delimter
        res.push_back(token);
    }

    res.push_back(instr.substr(posStart)); // last substring
    return res;
}


int* GetOffset(vector<string> instr, int offsetArray[]){
    /*
    Desc: Finds offset values
    Param: vector<string> instr - vector of strings with offset
    Output: NULL or array of the offset values
    */
   size_t found; 
    for(int i = 0; i < instr.size(); i++){ // goes through each part of instruction to check for offset
        found = instr.at(i).find('(');
        if(found != string::npos){ // the character is found
            // offset values put in array
            OffsetArray(instr.at(i), offsetArray);
            return offsetArray;
        }
    }
    return NULL;
}

void OffsetArray(string offsetString, int offsetArr[]){
    /*
    Desc: makes an array with the offset values
    Param: string offsetSTring - string with offset
           int offsetArr[] - array to hold offset data
    Output: none
    */
    
    size_t startPos = 0; // index for start of substring
    size_t charPos = offsetString.find('('); // position char is found at
    string offset = offsetString.substr(startPos, charPos); // first substring to go in array
    string address; // third substring to go in array
    startPos = charPos+1;
    if(offsetString[startPos] == '$'){ // check if next character after ( is $
        offsetArr[1] = '$'; // secong subtring to go in array
        startPos+=1;
    }
    else if(offsetString[startPos] == 'F'){ // check if next character after ( is F
        offsetArr[1] = 'F';  // secong subtring to go in array
        startPos+=1;
    }
    else{ // not from a reg but from main memory
        offsetArr[1] = '?'; // secong subtring to go in array
    }
    offsetArr[0] = atoi(offset.c_str()); // converts string to int
    charPos = offsetString.find(')');
    address = offsetString.substr(startPos, charPos-startPos); // gets address substring
    offsetArr[2] = atoi(address.c_str()); // converts string to int
}

int GetRegLoc(string reg){
    /*
    Desc: Finds register location
    Param: string reg - string of register
    Output: register index
    */

   return atoi(reg.substr(1).c_str());
}

void SetMemory(){

    // set up int and fp regs
    for(int i = 0; i < REG_SIZE; i++){
        intReg[i] = 0;
        fpReg[i] = 0;
    }
    
    // initializes the cache
    for(int i = 0; i < CACHE_DIM; i++){
        cache[i].datatype = INT;
        cache[i].regData.integer.index = -1;
        cache[i].regData.integer.data_int = -1;
    }

    // initializes main memory
    for(int i = 0; i < MEM_LOC; i++){
        mainMem[i].datatype = INT;
        mainMem[i].regData.integer.index = i;
    }
    mainMem[0].regData.integer.data_int = 45;
    mainMem[1].regData.integer.data_int = 12;
    mainMem[2].regData.integer.data_int = 0;
    mainMem[3].regData.integer.data_int = 92;
    mainMem[4].regData.integer.data_int = 10;
    mainMem[5].regData.integer.data_int = 135;
    mainMem[6].regData.integer.data_int = 254;
    mainMem[7].regData.integer.data_int = 127;
    mainMem[8].regData.integer.data_int = 18;
    mainMem[9].regData.integer.data_int = 4;
    mainMem[10].regData.integer.data_int = 55;
    mainMem[11].regData.integer.data_int = 8;
    mainMem[12].regData.integer.data_int = 2;
    mainMem[13].regData.integer.data_int = 98;
    mainMem[14].regData.integer.data_int = 13;
    mainMem[15].regData.integer.data_int = 5;
    mainMem[16].regData.integer.data_int = 233;
    mainMem[17].regData.integer.data_int = 158;
    mainMem[18].regData.integer.data_int = 167;
}

