#include "pipeline_output.h"

//static int starting_index = 0; //keep track of where to start
//static bool if_flag = false, id_flag = false, ex_flag = false, mem_flag = false, wb_flag = false; //check if the stage is currently in
vector<vector<string>> output; //a 2-D vector to store the output of pipeline
vector<bool> Occupied = {false}; //initialize to false
/*void IF_stage(){
    if (if_flag)
        if_flag = false;
    else
        if_flag = true;
}
void ID_stage(){
    if (id_flag)
        id_flag = false;
    else
        id_flag = true;
}
void MEM_stage(){
    if (mem_flag)
        mem_flag = false;
    else
        mem_flag = true;
}
void EX_stage(){
    if (ex_flag)
        ex_flag = false;
    else
        ex_flag = true;
}
void WB_stage(){
    if (wb_flag)
        wb_flag = false;
    else
        wb_flag = true;
}*/

void Action(){
    int j = 0; //index will be used in output vector
    Pipeline temp; 
    //for loop goes through each of the instruction
    for (int i = 0; i < int(original.size()); i++){
        output.at(i).push_back(original[i]);
        int count = 0;
        int result = temp.GetFunction(parsedInstrArr.at(i)); //get the return value after 
        if (int(output.size()) > 0){
            //int previousIndex = int(output.size()) - 1; 
           
           //loop to know when to start fetching the next instruction, make sure it is not the first instruction
           if ((i - 1) != -1){
            while (output.at(i - 1)[count] != "ID" ){
                output.at(i).push_back(NULL);
                count++;
            }
           }

        }

        int stage_count = 0; //five stage

        while (stage_count < 5){
            stage_count++;
            //Stall when the previous instruction is using 
            if (Occupied.at(count) && i != 0){
                output.at(i)[count] = "STALL";
            }
            else{
                //if stage
                if (stage_count == 1){
                    output.at(i)[count] = "IF";
                    Occupied.at(count) = false;
                    count++;
                }
                //id stage
                else if (stage_count == 2){
                    output.at(i)[count] = "ID";
                    Occupied.at(count) = false;
                    count++;
                }
                //ex stage
                else if (stage_count == 3){
                    output.at(i)[count] = "EX";
                    Occupied.at(count) = false;
                    count++;

                    //floating point adder
                    if (result == 2){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 2; l++){
                            output.at(i)[count] = "ADD" + l;
                            if (l == 1){
                                Occupied.at(count) = false;
                                count++;
                            }
                            else{
                                Occupied.at(count) = true;
                                count++;
                            }
                        }
                    }

                    //floating point subtract
                    if (result == -2){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 2; l++){
                            output.at(i)[count] = "SUB" + l;
                            if (l == 1){
                                Occupied.at(count) = false;
                                count++;
                            }
                            else{
                                Occupied.at(count) = true;
                                count++;
                            }
                        }
                    }
                    //floating point mult
                    if (result == 10){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 10; l++){
                            output.at(i)[count] = "MUL" + l;
                            if (l == 1){
                                Occupied.at(count) = false;
                                count++;
                            }
                            else{
                                Occupied.at(count) = true;
                                count++;
                            }
                        }
                    }
                    //floating point div
                    if (result == 40){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 40; l++){
                            output.at(i)[count] = "DIV" + l;
                            if (l == 1){
                                Occupied.at(count) = false;
                                count++;
                            }
                            else{
                                Occupied.at(count) = true;
                                count++;
                            }
                        }
                    }  
                }
                //mem stage
                else if (stage_count == 4){

                    output.at(i)[count] = "MEM";
                    Occupied.at(count) = false;
                    count++;
                    //memory has a MISS and have to look in main memory data
                    if (result == 3){
                        output.at(i)[count + 1] = "MEM";   
                        output.at(i)[count + 2] = "MEM";
                        Occupied.at(count + 1) = true;
                        Occupied.at(count + 2) = true;
                        count = count + 2;
                    }


                }
                //wb stage
                else if (stage_count == 5){
                    output.at(i)[count] = "WB";
                    Occupied.at(count) = false;
                    count++;
                }
                }
            }
        }
}
