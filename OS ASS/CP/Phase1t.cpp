#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct OS{
    
    vector<vector<char>> memory;
    ifstream inputfile;
    fstream outputfile;
    string buffer;
    int IC;
    int SI;
    vector<char> IR;
    vector<char> R;
    vector<string> instruction_set;
    bool C;

    OS() : memory(100,vector<char>(4,' ')), IC(0), IR(4), R(4), C(false), inputfile("input.txt"),
            instruction_set({"GD","PD","SR","LR","CR","BT"}) {}
    void load();        
    void init();
    void MOS(int); 
    void TERMINATE(int);
    void startExecution();
    void executeUserProgram();
    void READ(int);
    void WRITE(int);
};

void OS :: init(){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 4; j++){
            memory[i][j] = ' ';
        }
    }

    for(int i = 0; i < 4; i++){
        IR[i] = ' ';
        R[i] = ' ';
    }

    C = false;
    IC = 0;
    buffer.clear(); 
}

void OS :: startExecution(){
    IC = 0;
    executeUserProgram();
    outputfile.open("output.txt", ios::app);
    outputfile << endl << endl;
    outputfile.close();
}

void OS :: READ(int SI){
    

    int memoryaddr = (IR[2] - 48)*10 + (IR[3] - 48);
    int wordoffset = 0;
    int byteswritten = 0;
    getline(inputfile, buffer);

    for(int i = 0; i < 40; i++){
        if(i >= buffer.size()){
            memory[memoryaddr][wordoffset] = ' ';
            byteswritten++;
        }
        else{
            memory[memoryaddr][wordoffset] = buffer[i];
            byteswritten++;
        }

        if(byteswritten % 4 == 0){
            byteswritten = 0;
            wordoffset = 0;
            memoryaddr++;
        }
        else{
            wordoffset++;
        }
    }
}

void OS :: WRITE(int SI){
    outputfile.open("output.txt", ios::app);
    int memoryaddr = (IR[2] - 48) * 10 + (IR[3] - 48);
    int wordoffset = 0;
    int byteswritten = 0;

    for (int i = 0; i < 40; i++) {
        outputfile << memory[memoryaddr][wordoffset];
        byteswritten++;

        if (byteswritten % 4 == 0) {
            byteswritten = 0;
            wordoffset = 0;
            memoryaddr++;
        } else {
            wordoffset++;
        }
    }
    
    outputfile << endl;
    outputfile.close();
}


void OS :: TERMINATE(int SI)
{
    outputfile << "\n\n";
}

void OS :: MOS(int SI)
{
    if(SI==1)
    {
        READ(SI);
    }
    else if(SI==2)
    {
        WRITE(SI);
    }
    else if(SI==3)
    {
        TERMINATE(SI);
    }

} 

void OS :: executeUserProgram(){

    while(true){

        for(int i = 0; i < 4; i++){
            IR[i] = memory[IC][i];
        }
        IC++;

        if(IR[0] == 'H')
            break;          // Terminate
        
        if(IR[0] == 'G' && IR[1] == 'D'){
            SI = 1;
            MOS(SI);
        }
        else if(IR[0] == 'P' && IR[1] == 'D'){
            SI = 2;
            MOS(SI);
        }
        else if(IR[0] == 'C' && IR[1] == 'R'){
            int memoryaddr = (IR[2] - 48)*10 + (IR[3] - 48);
            bool condition;
            for(int i = 0; i < 4; i++){
                
                if(memory[memoryaddr][i] != R[i]){
                    condition = true;
                    break;
                }
            }
            (condition ? (C = false) : (C = true));
        }

        else if(IR[0] == 'S' && IR[1] == 'R'){
            int memoryaddr = (IR[2] - 48)*10 + (IR[3] - 48);
            for(int i = 0; i < 4; i++){
               memory[memoryaddr][i] = R[i];                 
            }
        }

        else if(IR[0] == 'L' && IR[1] == 'R'){
            int memoryaddr = (IR[2] - 48)*10 + (IR[3] - 48);
            for(int i = 0; i < 4; i++){
                R[i] = memory[memoryaddr][i]; 
            }
        }

        else if(IR[0] == 'B' && IR[1] == 'T'){
            int memoryaddr = (IR[2] - 48)*10 + (IR[3] - 48);
            if(C)
                IC = memoryaddr;
        }
        else{
            break;
        }
    }
}

void OS::load() {
    while (!inputfile.eof()) {
        init();
        getline(inputfile, buffer);
        if (buffer.substr(0, 4) == "$AMJ") {
            // Load program into memory
            int memoryaddr = 0;
            int wordoffset = 0;
            while (getline(inputfile, buffer) && buffer.substr(0, 4) != "$DTA") {
                for (char c : buffer) {
                    if (memoryaddr < 100) {
                        memory[memoryaddr][wordoffset] = c;
                        wordoffset = (wordoffset + 1) % 4;
                        if (wordoffset == 0) {
                            memoryaddr++;
                        }
                    }
                }
            }
            startExecution();
            // Print memory contents
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 4; j++) {
                    cout << "Memory Location [" << i << "][" << j << "]: " << memory[i][j] << endl;
                }
            }
        }
    }
}


int main(){
    OS os;
    os.load();
    
}