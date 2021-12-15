#include "pipeline_output.h"

vector<vector<string>> output; //a 2-D vector to store the output of pipeline
vector<string> subOutput; //input the instruction
vector<int> Occupied ; //vector the keep track of what index in output will be 'stall'

/*
Desc: Start pipelining into output vector
Parm: dynamic array original and size as arguments to get the original instructions before parsing
Output: none
*/
void Action(string *original, int size){
    int index = 0; //index will be used in output vector
    Pipeline temp; //to access to GetFunction in Pipeline class
    
    //loop that will goes through each instruction
    for (int i = 0; i < size; i++){
        int count = 1; //keep trach index of stages in of output
        int result = temp.GetFunction(parsedInstrArr.at(i)); //get the return value after 
        bool flag = false; //mark that we will include stall at next stage if has
        int stage_count = 0; //five stages 

        subOutput.push_back(original[i]); //push back instructions
        output.push_back(subOutput);
        subOutput.clear(); //clear out the vector to new input

        //if result = -100, the instruction is Loop:
        if (int(output.size()) > 1 && result != -100 && count < int(output.at(index - 1).size() )){      

           //loop to know when to start fetching the next instruction, make sure it is not the first instruction
            while (output.at(index - 1)[count] != "ID" ) {
                output.at(index).push_back("");
                count ++;
            }
        }
        //if the previous instruction is Loop, get the one before Loop
        else if (int(output.size()) > 1 && count == int(output.at(index - 1).size() )){
            while (output.at(index - 2)[count] != "ID" ) {
                output.at(index).push_back("");
                count ++;
            }
        }
        //pass the stages if "Loop:"
        if(result == -100)
            stage_count = 5;

        //goes through each stage
        while (stage_count < 5){
            stage_count++;
          
            if (int(Occupied.size()) > 0 && flag == false){
                
                //if at count, there is a value in Occupied that match with count value, push back 'stall'
                for (int j = 0; j < int(Occupied.size()); j++){
                    if (count == Occupied.at(j)){
                        output.at(index).push_back("STALL");
                        count ++;
                    }
                }
            }
            //if stage
             if (stage_count == 1){
                    output.at(index).push_back("IF");
                    count++;
                }

             //id stage
             if (stage_count == 2){
                    output.at(index).push_back("ID");
                    count++;
                }

            //ex stage
             if (stage_count == 3){

                    //floating point adder
                    if (result == -2){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 2; l++){
                            string temp = "ADD" + to_string(l);
                            output.at(index).push_back(temp);
                            count++;
                            
                            //only stall if use same stage at next cycle
                            if (l != 1)
                                Occupied.push_back(count);
                            
                        }
                        flag = true;
                    }
                    
                    //floating point mult
                    else if (result == -10){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 10; l++){
                            string temp = "M" + to_string(l);
                            output.at(index).push_back (temp);
                            count ++;
                            if (l != 1)
                                Occupied.push_back(count);
                            
                        }
                        flag = true;
                    }
                    //floating point div
                    else if (result == -40){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 40; l++){
                            string temp = "DIV" + to_string(l);
                            output.at(index).push_back(temp);
                            count ++;
                            if (l != 1)
                                Occupied.push_back(count);
                            
                        }
                        flag = true;
                    }  
                    else {
                        output.at(index).push_back("EX");
                        count++;
                    }

                }
                //mem stage
                if (stage_count == 4){
                   
                    //memory has a MISS and have to look in main memory data
                    if (result == -3){
                        for (int l = 1; l <= 3; l++){
                            //if the previous instruction is using Mem, stalling this cycle
                            if(count < int(output.at(index - 1).size()) && output.at(index - 1)[count] == "MEM"){
                                output.at(index).push_back("STALL") ;
                                Occupied.push_back(count);
                            }
                            else{
                                output.at(index).push_back("MEM") ;    
                                if (l != 1)
                                    Occupied.push_back(count);                       
                            }

                         count++;
                        }
                        flag = true;                    
                    }
                    else{
                        output.at(index).push_back("MEM");
                        count++;
                    }
                }

                //wb stage
             if (stage_count == 5){
                    output.at(index).push_back("WB");
                    count++;
                }

        }
        //the instruction is branch
        if (result > 0){
            i = result - 1; //minus one so that when it starts new instruction, it will be at desired index
        }
        index++; //keep track of at on instructions when looping          
    }
}

/*
Desc: This function will display output vector and also read from the vector into an exel file
Parm: None
Output: None
*/
void Display(){
    ofstream myfile;
    myfile.open("result.csv", ios::app); //create a file call result.csv
    cout << endl;
        for (int i = 0; i < int(output.size()); i++){
            for (int j = 0; j < int(output[i].size()); j++){
             cout<<output[i][j]<<" "; //display the result
             myfile<<output[i][j]<<","; //read in the file, "," indicate each field in exel
        }
        cout<<endl; 
        myfile <<endl; //go to new line
    }
}

