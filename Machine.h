#ifndef Machine_H
#define Machine_H
#include "Memory.h"
#include "CPU.cpp"
class Machine
{
private:
    void Get_New_Program( ); // it takes a new file from the user 
    void Display_info( ) ;// it prints the register and the memory
    // void Set_Start_Address( ) ;
    // void Load_all_Instructions ( ) ;//  (fetch) it takes all the instructions from the file to our vector of string
    void Load_all_Instructions_toMemory( );
    void Load_all_Instructions_StepBySteo();
    void Reset_Machine( );
    void menu( );
public:
    int choice = 0;
    string name_file ;
    vector<string> lines;
    string start_address = "";
    bool step = false;
    void play ();
    Machine();
    CPU cpu;
    Memory meMory;
    
};



#endif