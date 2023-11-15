/*File: A2_Task3_B_20220253_20221096_20220878.h
 *Purpose: Assignment 2 OOP
 * Author1: Kirolos Adel Nan             20220253
 * Author2: Abdelrahman Tarek Alsaid     20221096
 * Author3: Al-Hussain Abdo Mohamed      20220878
 * Section: 23
 * Date: 12 Oct 2023
 * */


#ifndef Machine_H
#define Machine_H
#include "Memory.h"
#include "CPU.cpp"
class Machine
{
private:
    void Get_New_Program( ); // it takes a new file from the user 
    void Display_info( ) ;// it prints the register and the memory
    void Load_all_Instructions_toMemory( );
    void Load_all_Instructions_StepBySteo();
    void Reset_Machine( );
    void menu( );
public:
    int choice = 0;
    string name_file ;
    vector<string> lines;
    map<string ,string >lines_step;
    string start_address = "";
    bool step = false;
    void play ();
    Machine();
    CPU cpu;
    Memory meMory;
    
};



#endif
