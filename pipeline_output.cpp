#include "pipeline_output.h"

//static int starting_index = 0; //keep track of where to start
//static bool if_flag = false, id_flag = false, ex_flag = false, mem_flag = false, wb_flag = false; //check if the stage is currently in
vector<vector<string>> output; //a 2-D vector to store the output of pipeline
vector<string> subOutput; 
vector<int> Occupied ; //vector the keep track of what index in output will be 'stall'

void Action(string *original, int size){
    int index = 0; //index will be used in output vector
    Pipeline temp; 
    //for loop goes through each of the instruction
    
    for (int i = 0; i < size; i++){
       // cout<<"before pushing in sub"<<endl;
        int count = 1; //keep trach index of sub-vector of output
        subOutput.push_back(original[i]);
        cout<<subOutput.at(0)<<endl;
        output.push_back(subOutput);
        subOutput.clear(); //clear out the vector to new input
        int result = temp.GetFunction(parsedInstrArr.at(i)); //get the return value after 
        bool flag = false; //mark that we will include stall at next stage if has
        int stage_count = 0; //five stage

        cout<<"i: " << i <<endl;
        cout<<"result: "<<result<<endl;
        //if result = -100, the instruction is Loop:
        if (int(output.size()) > 1 && result != -100 && count < int(output.at(index - 1).size() )){      
            //cout<<"size: "<< int(output.at(i - 1).size())<<endl;
           //loop to know when to start fetching the next instruction, make sure it is not the first instruction
            while (output.at(index - 1)[count] != "ID" ) {
               // cout<<"count in while: "<<count<<endl;
                output.at(index).push_back("");
                count ++;
            }
        }
        //if the previous instruction is Loop, get the one before Loop
        else if (int(output.size()) > 1 && count == int(output.at(index - 1).size() )){
            while (output.at(index - 2)[count] != "ID" ) {
               // cout<<"count in while: "<<count<<endl;
                output.at(index).push_back("");
                count ++;
            }
        }
        if(result == -100)
            stage_count = 5;
        while (stage_count < 5){
            stage_count++;
            cout << "count: " <<count<<endl;
            for (int j = 0; j < int (Occupied.size()); j++){
                cout<<Occupied.at(j)<<" ";
            }
            if (int(Occupied.size()) > 0 && flag == false){
                for (int j = 0; j < int(Occupied.size()); j++){
                    if (count == Occupied.at(j)){
                        output.at(index).push_back("STALL");
                       // cout<<"\noutput at stall: "<<output[i][count]<<endl;
                        //cout<<"at i:"<<i<<endl;
                        count ++;
                    }
                }
            }
           // else{
                //if stage
             if (stage_count == 1){
                    output.at(index).push_back("IF");
                    count++;
                }
                //id stage
             if (stage_count == 2){
                    output.at(index).push_back("ID");
                    //Occupied.at(count + 1) = false;
                   //Occupied.push_back(false);
                    count++;
                }
                //ex stage
             if (stage_count == 3){

                    //floating point adder
                    if (result == -2){
                        count--; //override the previous input ("EX" input)
                        for (int l = 1; l <= 2; l++){
                            string temp = "ADD" + to_string(l);
                           // cout <<"temp: "<<temp<<endl;
                            output.at(index).push_back(temp);
                            /*if (l == 1){
                                Occupied.push_back(true);
                                count++;
                            }
                            else{
                                Occupied.push_back(false);
                                count++;
                            }*/
                            count++;
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
                            /*if (l == 10){
                                Occupied.push_back();
                                count++;
                            }
                            else{
                                Occupied.push_back(true);
                                count++;
                            }*/
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
            cout <<"at branch"<<result<<endl;
        }
        index++;           
    }
}

void Display(){
   // cout<<endl<<endl;
    /*for (int i = 0; i < int(output.size()); i++){
        for (int j = 0; j < int(output[i].size()); j++){
            cout<<output[i][j]<<" ";
        }
        cout <<endl;
    }*/
    cout<<output[8][11]<<endl;
    //cout<<output[9][15]<<endl;
    ofstream myfile;
    myfile.open("result.csv", ios::app);
    cout << endl;
        for (int i = 0; i < int(output.size()); i++){
            for (int j = 0; j < int(output[i].size()); j++){
             cout<<output[i][j]<<" ";
             myfile<<output[i][j]<<",";
        }
        cout<<endl;
        myfile <<endl;
    }
}
void Exel(){
    ofstream myfile;
    myfile.open("result.csv", ios::app);
        for (int i = 0; i < int(output.size()); i++){
            for (int j = 0; j < int(output[i].size()); j++){
             myfile<<output[i][j]<<"\t";
        }
        cout <<endl;
    }

}
