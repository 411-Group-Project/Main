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
            i++;
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
    vector<string> parsedInstrArr[arrSize];
    for(int i = 0; i < arrSize; i++){ // size of array for each instruction
        RemoveCommas(instrArr[i]); 
        RemoveColon(instrArr[i]);
        parsedInstrArr[i] = split(instrArr[i], " "); // stores vector and index i of array
    }
}

vector<string> split(string s, string delimiter) {
    /*
    Desc: parses string based on delimiter
    Param: string s - the string to be parsed
           string delimiter - the delimiter to split the string by
    Output: a vector of the parsed string
    */
    size_t posStart = 0; // start of substring
    size_t posEnd, delimLen = delimiter.length(); //end of substring
    string token; // substring before delimiter
    vector<string> res; // vector hold they substrings

    while ((posEnd = s.find(delimiter, posStart)) != string::npos){ // find the delimiter
        token = s.substr(posStart, posEnd - posStart);
        posStart = posEnd + delimLen; // new start posistion after delimter
        res.push_back(token);
    }

    res.push_back(s.substr(posStart)); // last substring
    return res;
}

void RemoveCommas(string& instr){
    /*
    Desc: This function removes the commas in a string and replaces
          them with spaces
    Param: string& instr - the string with the commas
    Output: none
    */
    for(int i = 0; i < instr.size(); i++){ // goes through each index of string
        if(instr[i] == ','){
            instr.erase(instr.begin() + i); // deletes comma
        }
    }
}

void RemoveColon(string& instr){
    /*
    Desc: This function removes the colons in a string 
    Param: string& instr - the string with the colons
    Output: none
    */
    for(int i = 0; i < instr.size(); i++){ // goes through each index of string
        if(instr[i] == ':'){
            instr.erase(instr.begin() + i); // deletes colon
        }
    }
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