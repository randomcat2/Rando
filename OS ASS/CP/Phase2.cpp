#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_set>
#include<algorithm>
using namespace std;

struct PCB{
    int TLL;
    int TLC;
    int TTL;
    int TTC;
};

struct OS{
    
    vector<vector<char>> memory;
    ifstream inputfile;
    fstream outputfile;
    string buffer;
    int IC;
    int SI;
    int PI;
    int EM;
    int TTL;
    int TLL;
    int PTBR;
    int prog_location;
    int cnt;
    int TI;
    vector<PCB> jobs;
    vector<char> IR;
    vector<char> R;
    vector<string> instruction_Set;
    bool C;
    unordered_set<int> alloc;

    OS() : memory(300 ,vector<char>(4,' ')), IC(0), IR(4), R(4), C(false), instruction_Set({"GD","PD","CR","SR","LR","BT"}),
    EM(0), PI(0), SI(0), inputfile("input2.txt"), cnt(-1), jobs(10), TI(0) {}
    
    void load();        
    void init();
    void startExecution();
    void executeUserProgram();
    void READ(int);
    void WRITE(int);
    int AddressMap(int,string);
    void endExecution(int,int);
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
    prog_location = 0;
    PI = 0;
    SI = 0;
    EM = 0;
    IC = 0;
    cnt++;
    buffer.clear();
}

void OS :: startExecution(){
    IC = prog_location;
    executeUserProgram();
    outputfile.open("output.txt",ios::app);
    outputfile << endl;
    outputfile.close();
}

void OS :: READ(int realaddress){
    int wordoffset = 0;
    int byteswritten = 0;

    getline(inputfile, buffer);

    if(buffer.substr(0,4) == "$END"){
        EM = 1;
        return;
    }

    for(int i = 0; i < 40; i++){
        if(i >= buffer.size()){
            memory[realaddress][wordoffset] = ' ';
            byteswritten++;
        }
        else{
            memory[realaddress][wordoffset] = buffer[i];
            byteswritten++;
        }

        if(byteswritten % 4 == 0){
            byteswritten = 0;
            wordoffset = 0;
            realaddress++;
        }
        else{
            wordoffset++;
        }
    }
}

void OS :: WRITE(int realaddress){

    outputfile.open("output.txt", ios::app);
    jobs[cnt].TLC++; 
    
    int wordoffset = 0;
    int byteswritten = 0;

    for(int i = 0; i < 40; i++){
        outputfile << (memory[realaddress][wordoffset]);
        byteswritten++;
    
        if(byteswritten % 4 == 0){
            byteswritten = 0;
            wordoffset = 0;
            realaddress++;
        }
        else{
            wordoffset++;
        }
    } 
    outputfile << endl;
    outputfile.close();
}

void OS :: executeUserProgram(){
    
    while(true){
        for(int i = 0; i < 4; i++){
            IR[i] = memory[IC][i];
        }
        jobs[cnt].TTC++;

        if(IR[0] == 'H')
            break;          // Terminate

        string opcode = "";
        opcode += memory[IC][0];
        opcode += memory[IC][1];

        // Error handling-------------------------------------------------------------------------
            // Opcode error
            if(find(instruction_Set.begin(),instruction_Set.end(),opcode) == instruction_Set.end()){
                PI = 1;
                EM = 4;
                break;
            }

            //operand error
            if(isalpha(IR[2]) || isalpha(IR[3]) || IR[0] == '-' || isdigit(IR[1])){
                PI = 2;
                EM = 5;
                break;
            }

            if(EM == 1) {
                break;      // Out of Data error
            }
        //-------------------------------------------------------------------------------------

        //AddressTranslation-------------------------------------------------------------------

            int virtualmem = (IR[2] - 48)*10 + (IR[3] - 48);
            int realAddr = AddressMap(virtualmem, opcode);

            if(PI == 3) {
                EM = 6;
                break;      // Invalid page fault
            }

        //---------------------------------------------------------------------------------------
        
        if(IR[0] == 'G' && IR[1] == 'D'){
            SI = 1;
            READ(realAddr);
            jobs[cnt].TTC++;
        }
        else if(IR[0] == 'P' && IR[1] == 'D'){
            SI = 2;
            WRITE(realAddr);
        }
        else if(IR[0] == 'C' && IR[1] == 'R'){
            bool condition;
            for(int i = 0; i < 4; i++){
                
                if(memory[realAddr][i] != R[i]){
                    condition = true;
                    break;
                }
            }
            (condition ? (C = false) : (C = true));
        }

        else if(IR[0] == 'S' && IR[1] == 'R'){
            for(int i = 0; i < 4; i++){
                memory[realAddr][i] = R[i];                 
            }
            jobs[cnt].TTC++;
        }

        else if(IR[0] == 'L' && IR[1] == 'R'){
            for(int i = 0; i < 4; i++){
                R[i] = memory[realAddr][i]; 
            }
        }

        else if(IR[0] == 'B' && IR[1] == 'T'){
            int memoryaddr = (IR[2] - 48)*10 + (IR[3] - 48);
            if(C)
                IC = realAddr - 1;
        }
        else{
            break;
        }
        IC++;
    }
}

void OS :: load(){
    
    while(!inputfile.eof()){
        init();
        getline(inputfile, buffer);

        if(buffer.substr(0,4) == "$END"){
            continue;
        }

        if(buffer.substr(0,4) == "$AMJ"){

            // creating job card
            TTL = stoi(buffer.substr(8,4));
            TLL = stoi(buffer.substr(12,4));

            PCB card_job;
            card_job.TLC = 0;
            card_job.TTC = 0;
            card_job.TTL = TTL;
            card_job.TLL = TLL;
            jobs[cnt] = card_job;
            
            PTBR = rand() % 30; 
            PTBR *= 10;

            // page table init
            for(int i = 0; i < 10; i++){
                alloc.insert(PTBR + i);
                memory[PTBR + i][0] = '*';
                memory[PTBR + i][1] = '*';
                memory[PTBR + i][2] = '*';
                memory[PTBR + i][3] = '*';
            }

            int firstEntry = rand() % 30; 

            while(alloc.find(firstEntry*10) != alloc.end()){  //alloc.find-->doesn't find no then it returns alloc.end
                firstEntry = rand() % 30;
            }   
            string entry = to_string(firstEntry);

            if(entry.size() == 1){
                memory[PTBR][2] = '0';
                memory[PTBR][3] = entry[1];
            }
            else{
                memory[PTBR][2] = entry[0];
                memory[PTBR][3] = entry[1];
            }

            prog_location = firstEntry*10;
            alloc.insert(prog_location);

            getline(inputfile, buffer);

            int memoryaddr = prog_location;
            int byteswritten = 0;
            int wordoffset = 0;
            //load code in memory
            while(buffer.substr(0,4) != "$DTA"){

                for(int i = 0; i < buffer.size(); i++){
                    alloc.insert(memoryaddr);
                    if(buffer[i] == 'H'){
                        memory[memoryaddr][wordoffset] = buffer[i];
                        memoryaddr++;
                    }
                    else{
                        memory[memoryaddr][wordoffset] = buffer[i];
                        byteswritten++;   
                    }

                    if(byteswritten % 4 == 0){
                        wordoffset = 0;
                        memoryaddr++;
                        byteswritten = 0;
                    }
                    else{
                        wordoffset++;
                    }
                }
                getline(inputfile, buffer);
            }
            //program loaded in memory

            buffer.clear();
            startExecution();
            endExecution(jobs[cnt].TTC, jobs[cnt].TLC);
        }
    }
    inputfile.close();
}

void OS :: endExecution(int TTC, int TLC){
    
    outputfile.open("output.txt", ios::app);

    if(TTC > TTL){
        outputfile << "Time limit exceeded" << endl;
    }
    if(TLC > TLL){
        outputfile << "Line limit exceeded" << endl;
    }

    if(EM == 0){
        outputfile << "Program terminated normally!" << endl;
        outputfile << "\nSI = " << SI << "  TI =" << TI << "  PI =" << PI << endl;
        outputfile << "TTC = " << TTC << "  TLC =" << TLC << endl;
        outputfile << "------------------------------------------------------------------" << endl
            << endl;
        outputfile.close();
        return;
    }
    else if(EM == 1){
        outputfile << "Out of data error...abnormal termination!" << endl;
        outputfile << "\nSI = " << SI << "  TI =" << TI << "  PI =" << PI << endl;
        outputfile << "TTC = " << TTC << "  TLC =" << TLC << endl;
        outputfile << "------------------------------------------------------------------" << endl
            << endl;
        outputfile.close();
        return;
    }
    else if(EM == 4){
        outputfile << "Opcode error...abnormal termination!" << endl;
        outputfile << "\nSI = " << SI << "  TI =" << TI << "  PI =" << PI << endl;
        outputfile << "TTC = " << TTC << "  TLC =" << TLC << endl;
        outputfile << "------------------------------------------------------------------" << endl
            << endl;
        outputfile.close();
        return;
    }
    else if(EM == 5){
        outputfile << "Operand Error...abnormal termination!" << endl;
        outputfile << "\nSI = " << SI << "  TI =" << TI << "  PI =" << PI << endl;
        outputfile << "TTC = " << TTC << "  TLC =" << TLC << endl;
        outputfile << "------------------------------------------------------------------" << endl
            << endl;
        outputfile.close();
        return;
    }
    else if(EM == 6){
        outputfile << "Invalid Page fault...abnormal termination!" << endl;
        outputfile << "\nSI = " << SI << "  TI =" << TI << "  PI =" << PI << endl;
        outputfile << "TTC = " << TTC << "  TLC =" << TLC << endl;
        outputfile << "------------------------------------------------------------------" << endl
            << endl;
        outputfile.close();
        return;
    }
    else{
        return;
    }
};

int OS :: AddressMap(int VA, string opcode){
    
    int RA;
    int PTE = PTBR + (VA / 10);       //page table entry for data

    if(memory[PTE][2] == '*' && memory[PTE][3] == '*'){         //Page fault occured
        
        if(opcode == "PD"){
            PI = 3;
            return -1;
        }

        int data_location = rand() % 30;
        if(alloc.find(data_location*10) == alloc.end()){
            alloc.insert(data_location*10);
        }
        else{
            while(alloc.find(data_location*10) != alloc.end()){
                data_location = rand() % 30;
            }
            alloc.insert(data_location*10);
        }

        string entry = to_string(data_location);
        if(entry.size() == 1){
            memory[PTE][2] = '0';
            memory[PTE][3] = entry[0];
        }
        else{
            memory[PTE][2] = entry[0];
            memory[PTE][3] = entry[1];
        }

        RA = data_location * 10 + VA % 10;
    }
    else{  //This block executes when there is no
    // page fault, meaning the page table entry already contains a valid frame number.
        string translator = "";   //used to collect characters that represent frame no in page table entry
        translator.push_back(memory[PTE][2]);
        translator.push_back(memory[PTE][3]);

        int data_loc = stoi(translator);
        RA = data_loc*10 + VA%10;
    }
    return RA;
}

int main(){
    OS os;
    os.load();
}